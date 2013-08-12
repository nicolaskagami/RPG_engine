//Nicolas Silveira Kagami
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netdb.h> 					//Required for MAC
#include <net/if.h> 				//Required for MAC
#define MAX_NAME 						20
#define MAX_PASS 						15
#define MAX_CLIENTS 				5
#define BUFF_SIZE						128
#define MAX_REQUEST					10

typedef struct  
{   
	int	thread_num;       
	int	connectionfd;  
}	THREAD_INFO;

typedef struct
{
	char username[MAX_NAME];
	char password[MAX_PASS];
} USER;

typedef struct
{
	int STR;
	int DEX;
	int CON;
	int WIS;
	int CHA;
}	ATTR;

typedef struct
{
	int AC;
	int HP;
	int DR;
	int crit;
}	BODY_PART;

typedef struct
{
	BODY_PART left_arm;
	BODY_PART right_arm;
	BODY_PART left_leg;
	BODY_PART right_leg;
	BODY_PART torso;
	BODY_PART head;
}	ANTHRO_BODY;

typedef struct
{
	ATTR attributes;
	ANTHRO_BODY body;
	int exp;
	int gp;
}	CHARACTER;

typedef struct
{
	char request[BUFF_SIZE];
} REQ;

pthread_t req_master;
pthread_t client_handler[MAX_CLIENTS];
int number_clients = 0;
pthread_mutex_t text_monitor;
pthread_mutex_t req_monitor;

REQ requests[MAX_REQUEST];
int number_requests = 0;

void add_request(char request[BUFF_SIZE]);
void * request_master();
void * client_receiver(void * arg);

int main(int argc, char**argv)
{
		int listenfd;			//Listener Connection identifier																											
		int connfd;				//Client Handler Connection identifier
		int rc;						//Control variable
		int i;						//Control variable
		int mode = 1;			//Non-blocking mode on
		struct ifreq *maccer; //for getting MAC ADDRESS
		char macp[19]; //for getting MAC ADDRESS
		struct sockaddr_in servaddr;
		struct sockaddr_in cliaddr;
		socklen_t clilen = sizeof(cliaddr);;
		THREAD_INFO thrinfo[MAX_CLIENTS];			//Thread Information structure

		rc = pthread_create( &req_master, NULL, request_master,NULL); //Birth request master

		listenfd = socket(AF_INET,SOCK_STREAM,0); //Making Listen Socket
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		servaddr.sin_port = htons(33000);
		bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
		listen(listenfd,MAX_CLIENTS);	//End making Listen Socket
		while(1)
		{	
			connfd = accept(listenfd,(struct sockaddr *) &cliaddr, &clilen);
			pthread_mutex_lock(&text_monitor);
			ioctl(connfd, SIOCGIFHWADDR, maccer);
			sprintf(macp, " %02x:%02x:%02x:%02x:%02x:%02x", 
    	(unsigned char)maccer->ifr_hwaddr.sa_data[0],
    	(unsigned char)maccer->ifr_hwaddr.sa_data[1],
    	(unsigned char)maccer->ifr_hwaddr.sa_data[2],
    	(unsigned char)maccer->ifr_hwaddr.sa_data[3],
    	(unsigned char)maccer->ifr_hwaddr.sa_data[4],
    	(unsigned char)maccer->ifr_hwaddr.sa_data[5]);
			printf("Connection Acquired: = %d\n",connfd);
			printf("	Thread Number: %i\n",number_clients);
			printf("	Client: %s::%hu\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
			printf("	MAC: %s\n",macp);
			thrinfo[number_clients].thread_num = number_clients;
			thrinfo[number_clients].connectionfd = connfd;
			pthread_mutex_unlock(&text_monitor);	
			rc = pthread_create( &client_handler[number_clients], NULL, client_receiver,&thrinfo[number_clients]);
			number_clients++;
		}
}

void * request_master()
{
	while(1)
	{
		pthread_mutex_lock(&req_monitor);
		while(number_requests)
		{
			number_requests--;
			printf("Treated: %s\n", requests[number_requests].request);
		}
		pthread_mutex_unlock(&req_monitor);
		usleep(10000);
	}
}
void add_request(char req[BUFF_SIZE])
{
	pthread_mutex_lock(&req_monitor);
	strcpy(requests[number_requests].request,req);
	number_requests++;
	pthread_mutex_unlock(&req_monitor);
}
void * client_receiver(void * arg)
{
	THREAD_INFO *thrinfo = arg;
	int connfd = thrinfo->connectionfd;
	int thread_number = thrinfo->thread_num;
	printf("Thread Number: %i\n",thread_number);
	printf("Connection Number: %i\n",connfd);
	
	struct sockaddr_in cliaddr;
	socklen_t clilen;
	char mesg[BUFF_SIZE];		
	int n;
	while(1)
	{
		n = recvfrom(connfd, mesg, BUFF_SIZE,0,(struct sockaddr *) &cliaddr, &clilen);
		if(n > 0)
		{
				pthread_mutex_lock(&text_monitor);
				sendto(connfd, mesg, n, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
				mesg[n] = 0;
				printf("Received the following:\n");
			 	printf("%s",mesg);
				pthread_mutex_unlock(&text_monitor);
				add_request(mesg);
		}
	}
	close(connfd);
}

