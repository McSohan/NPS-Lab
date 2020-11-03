/*
* Connection oriented Concurrent echo server.
*/

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define PORT 5000
#define IP INADDR_ANY
#define BACKLOG 5

void servfunc (int sockfd)
{
	char buf[BUFSIZE];
	int cnt;
    bzero(buf, BUFSIZE);
	cnt = recv(sockfd, buf, BUFSIZE, 0);
    if (cnt<0)
    {
        printf ("Error recieving the message");
    }
    if (cnt>0)
    {
        send (sockfd, buf, cnt, 0);
        bzero(buf, BUFSIZE);
    }
    printf ("sent\n");
	
}

int main ()
{
	//Variable
	struct sockaddr_in serv;
	int listenfd, acceptfd, fval;
	
	//Set the required data
	bzero (&serv, sizeof (serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons (PORT);
	serv.sin_addr.s_addr = htons(IP);
	//create a concurrent server 
	
	//create socket
	listenfd = socket (AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		printf ("Unable to create socket!!\n");
		exit(0);
	}
	//bind to the socket 
	if (bind (listenfd, (struct sockaddr *)&serv,sizeof(serv)) == -1)
	{
		printf ("Bind error\n");
		exit(0);
	}
	//call listen on the created socket
	if (listen(listenfd, BACKLOG) < 0)
	{
		printf ("Unable to call listen\n");
		exit(0);
	}
	printf ("Listen called\n");

	
	//concurrent server part
	while (1)
	{
		acceptfd = accept (listenfd, NULL, NULL);
		if (acceptfd == -1)
		{
			printf ("Error accepting !!\n");
			exit(0);
		}
		printf ("Accepted\n");

		//otherwise create a concurrent server
		fval = fork();
		if (fval == 0)
		{
			close (listenfd);
			//close the listen file descriptor in the child
			
			//perform server operation
			servfunc(acceptfd);
			
			close (acceptfd);
			//close the accepted file descriptor
			exit(0);
		}
		close (acceptfd);
	}
	
	return 0;
}
