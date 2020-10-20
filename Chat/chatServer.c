/*
* Server responds to the message that is sent by the client
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
	while (cnt = recv(sockfd, buf, BUFSIZE, 0))
    	{
        	write (1, buf, cnt);
        	printf ("\n");
        	bzero(buf, BUFSIZE);
        	if (cnt = read (1, buf, BUFSIZE));
            		send (sockfd, buf, cnt,0);
    	}
	
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
			//close the listen socket descriptor in the child
			
			//perform server operation
			servfunc(acceptfd);
			
			close (acceptfd);
			//close the accepted socket descriptor
			exit(0);
		}
		close (acceptfd);
	}
	
	return 0;
}
