#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

#define PORT 4000

int alive = 1;

void *printReceived(void *arg) {
    int n, sockfd = * ( (int *) arg );
    char buffer[256];
    
    // Print.
	while(alive) {
	    // Clean. 
	    bzero(buffer, 256);

	    // Read from the socket.
        n = read(sockfd, buffer, 256);
        if (n < 0) fprintf(stderr,"ERROR reading from socket\n");
        
	    if (strstr(buffer, "/TERMINATE")) { alive = 0; exit(0); }
        else fprintf(stderr,"%s\n",buffer);
    }
}

int main(int argc, char *argv[])
{
    int sockfd, n, len;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	
    char buffer[256];
    if (argc < 2) {
		fprintf(stderr,"usage %s hostname\n", argv[0]);
		exit(0);
    }
	
	server = gethostbyname(argv[1]);
	if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
        printf("ERROR opening socket\n");
    
	serv_addr.sin_family = AF_INET;     
	serv_addr.sin_port = htons(PORT);    
	serv_addr.sin_addr = *((struct in_addr *)server->h_addr);
	bzero(&(serv_addr.sin_zero), 8);     
	
    
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        printf("ERROR connecting\n");

    // Login
    printf("Username: ");
    bzero(buffer, 256);
    fgets(buffer, 256, stdin);    
    len = strlen(buffer);
    buffer[len-1] = '\0';
	/* write in the socket */
	n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) printf("ERROR writing to socket\n");
    
    // Listen for incoming messages.
    pthread_t *readThread = malloc(sizeof(pthread_t));
    pthread_create(readThread, NULL, printReceived, &sockfd);
    
    // Send messages.
    while(alive) {
        bzero(buffer, 256);
        fgets(buffer, 256, stdin);
        len = strlen(buffer);
        buffer[len-1] = '\0';
        
	    /* write in the socket */
	    n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) printf("ERROR writing to socket\n");
    }
    
	close(sockfd);
    return 0;
}
