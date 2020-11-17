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

void servfunc (int sockfd)
{
	char buf[BUFSIZE];
	int cnt,  fd;
	cnt = recv(sockfd, buf, BUFSIZE, 0);
	if ( cnt < 0)
	{
		printf ("Error \n");
		return ;
	}
	else if (cnt == 0)
	{
		printf ("No request found!!\n");
		return ;
	}
	//write the name of the command requested
	write (1, buf, cnt);
    buf[cnt-1] = '\0';
    system ("rm temp");
    strcat(buf, " > temp");
    printf ("%s\n", buf);
    system(buf);
    system ("chmod a+r temp");
	printf ("\n");
	fd = open("temp", O_RDONLY);//open the file in read only mode
	if (fd ==-1)
	{
		snprintf (buf, BUFSIZE, "Error\n");
		send (sockfd, buf, strlen(buf), 0);
		return;
	}
	//start reading from the file and sending it to the client 
	bzero(buf, BUFSIZE);
	while (cnt = read (fd, buf, BUFSIZE))
	{
		//send the contents of the file
		send (sockfd, buf, cnt, 0);
		//clear the buffer
		bzero(buf, BUFSIZE);
	}
	printf ("Result sent\n");
	close (fd);
	//close the file descriptor
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