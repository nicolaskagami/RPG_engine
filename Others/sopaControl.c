#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "echo_socket"

int main(void)
{
	int s, t, len;
	struct sockaddr_un remote;
	char command[30];
	usleep(100000);
	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}

	printf("Trying to connect...\n");

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(s, (struct sockaddr *)&remote, len) == -1) 
	{
		perror("connect");
		exit(1);
	}
	int exec = 0;
	printf("Connected.\n");
	while(strcmp(command,"end"))
	{
		printf(">");
		gets(command);

		if(exec)
		{
			printf("Partition:");
			exec = 0;
		}
		if(!strcmp(command,"help"))
		{
			printf("Commands:\n");
			printf("  pause\n  resume\n execute/load\n  show memory\n  end\n show interrupt\n");
		}

		if(!strcmp(command,"execute"))
		{
			printf("Disk:");
			exec = 1;
		}
		if(!strcmp(command,"load"))
		{
			printf("Disk:");
			exec = 1;
		}
		if(!strcmp(command,"kill"))
		{
			printf("PID:");
		}		

		if (send(s, command, 100, 0) == -1) 
		{
			perror("send");
			exit(1);
		}
		else
		{
			if(!strcmp(command,"pause"))
			{
				printf("SOPA: paused\n");
			}
			if(!strcmp(command,"resume"))
			{
				printf("SOPA: resumed\n");
			}
		}
	}
	
	close(s);
	return 0;
}



