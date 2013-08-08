
/* Sample TCP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   char sendline[128];
   char recvline[128];

   if (argc != 2)
   {
      printf("usage:  client <IP address>\n");
      return(1);
   }

   sockfd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(argv[1]);
   servaddr.sin_port=htons(32000);

   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

   while (fgets(sendline, 128 ,stdin) != NULL)
   {
      sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
      n=recvfrom(sockfd,recvline,128,0,NULL,NULL);
      recvline[n]=0;
      fputs(recvline,stdout);
   }
}
