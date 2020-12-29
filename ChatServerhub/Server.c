/*
* This is a file server that looks for a particuar file given the path.
* If present, sends the contents of the file to the client.
* Otherwise, terminates the connection after sending an error message.
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

void servfunc (int sockfd1, int sockfd2)
{
	char buf[BUFSIZE];
	int cnt;

    //recieve the first message from client 2
    cnt = recv(sockfd2, buf, BUFSIZE, 0);
    if (cnt==0)
    {
        printf ("Client 2 disconnected");
        exit(0);
    }
    write (1, buf, cnt);
    printf ("2\n");
    bzero(buf, BUFSIZE);
	while (cnt = recv(sockfd1, buf, BUFSIZE, 0))
    {
        //recieve data from client 1
        //send it to client 2
        send (sockfd2, buf, cnt,0);
        write (1, buf, cnt);
        printf ("1\n");
        bzero(buf, BUFSIZE);
        if (cnt = read (sockfd2, buf, BUFSIZE))
            send (sockfd1, buf, cnt,0);
        else
        {
            printf ("Client 2 disconnected");
            close(sockfd1);
            close( sockfd2);
        }
        write (1, buf, cnt);
        printf ("2\n");
        bzero(buf, BUFSIZE);
        
    }
    printf ("Client 1 disconnected");

	
}

int main ()
{
	//Variable
	struct sockaddr_in serv;
	int listenfd, acceptfd1, acceptfd2, fval;
	
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
		acceptfd1 = accept (listenfd, NULL, NULL);
		if (acceptfd1 == -1)
		{
			printf ("Error accepting !!\n");
			exit(0);
		}
		printf ("Accepted from client 1\n");

        acceptfd2 = accept (listenfd, NULL, NULL);
		if (acceptfd2 == -1)
		{
			printf ("Error accepting !!\n");
			exit(0);
		}
		printf ("Accepted from client 2\n");

        servfunc(acceptfd1, acceptfd2);

	}
	
	return 0;
}
