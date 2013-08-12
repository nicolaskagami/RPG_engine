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
#include <errno.h>
#define MAX_NAME            20
#define MAX_PASS            15
#define MAX_CLIENTS         10
#define BUFF_SIZE           128
#define MAX_REQUEST         10
#define MAX_REG_USERS       20

typedef struct  
{   
    int	thread_num;       
    int	connectionfd;  
}   THREAD_INFO;

typedef struct
{
    char username[MAX_NAME];
    char password[MAX_PASS];
}   USER;

typedef struct
{
    char request[BUFF_SIZE];
}   REQ;

pthread_t req_master;
pthread_t client_handler[MAX_CLIENTS];
int number_clients = 0;

pthread_mutex_t text_monitor;
pthread_mutex_t req_monitor;
pthread_mutex_t user_reg_monitor;

USER user_list[MAX_REG_USERS];
int number_reg_users = 0;
REQ requests[MAX_REQUEST];
int number_requests = 0;

void list_users();
int add_user(char username[MAX_NAME], char password[MAX_PASS]);
int remove_user(char username[MAX_NAME]);
void add_request(char request[BUFF_SIZE]);
void * request_master();
void * client_receiver(void * arg);

int main(int argc, char**argv)
{
    int listenfd;           //Listener Connection identifier
    int connfd;             //Client Handler Connection identifier
    int rc;                 //Control variable
    int i;                  //Control variable
    int mode = 1;           //Non-blocking mode on
    int errornumber;
    int iferror;
    struct ifreq *maccer;   //for getting MAC ADDRESS
    char macp[19];          //for getting MAC ADDRESS
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);;
    THREAD_INFO thrinfo[MAX_CLIENTS];			//Thread Information structure
    rc = pthread_create( &req_master, NULL, request_master,NULL); //Birth request master

    listenfd = socket(AF_INET,SOCK_STREAM,0); //Making Listen Socket
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(32000);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    listen(listenfd,MAX_CLIENTS);	//End making Listen Socket


    while(1)
    {	
        connfd = accept(listenfd,(struct sockaddr *) &cliaddr, &clilen);

        pthread_mutex_lock(&text_monitor);
        iferror = ioctl(connfd, SIOCGIFHWADDR, maccer);
        if(iferror != -1)
        {
            sprintf(macp, "%02x:%02x:%02x:%02x:%02x:%02x", 
            (unsigned char)maccer->ifr_hwaddr.sa_data[0],
            (unsigned char)maccer->ifr_hwaddr.sa_data[1],
            (unsigned char)maccer->ifr_hwaddr.sa_data[2],
            (unsigned char)maccer->ifr_hwaddr.sa_data[3],
            (unsigned char)maccer->ifr_hwaddr.sa_data[4],
            (unsigned char)maccer->ifr_hwaddr.sa_data[5]);
        } 
        else
        {
            printf("Could not get MAC: error number:%d\n",errno);
        }
        printf("Connection Acquired: = %d\n",connfd);
        printf("    Thread Number: %i\n",number_clients);
        printf("    Client: %s::%hu\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));

        if(iferror != -1)
        {
            printf("	MAC: %s\n",macp);
        }
        thrinfo[number_clients].thread_num = number_clients;
        thrinfo[number_clients].connectionfd = connfd;
        pthread_mutex_unlock(&text_monitor);	
        rc = pthread_create( &client_handler[number_clients], NULL, client_receiver,&thrinfo[number_clients]);
        number_clients++;
    }
}
int add_user(char username[MAX_NAME], char password[MAX_PASS])
{
    int return_code = 0;
    pthread_mutex_lock(&user_reg_monitor);
        if(number_reg_users<MAX_REG_USERS)
        {
            strcpy(user_list[number_reg_users].username,username);
            strcpy(user_list[number_reg_users].password,password);
            number_reg_users++;
        }
        else
        {
            printf("Maximum number of registered users reached\nCan't register %s",username);
            return_code = 1;
        }
    pthread_mutex_unlock(&user_reg_monitor);
    return return_code;
}
int remove_user(char username[MAX_NAME])
{
    int i;
    int found = 0;
    for(i=0;i<number_reg_users;i++)
    {
        if((!strcmp(username,user_list[i].username)||found))
        {
            found = 1;
            if(i<MAX_REG_USERS)
            {
                user_list[i] = user_list[i+1];
            }
        }
    }
    return found;
}
void list_users()
{
    int i;
    printf("Users:\n");
    for(i=0;i<number_reg_users;i++)
    {
        printf("%d: %s",i,user_list[i].username);
    }
}
void * request_master()
{
    while(1)
    {
    pthread_mutex_lock(&req_monitor);
        while(number_requests>0)
        {
            number_requests--;
            if(!strcmp("List Users",requests[number_requests].request))
            {
                list_users();
            }
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
                printf("%d:",thread_number);
                printf("%s",mesg);
            pthread_mutex_unlock(&text_monitor);
            add_request(mesg);
        }
    }
    close(connfd);
}
