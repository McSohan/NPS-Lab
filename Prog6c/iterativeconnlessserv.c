/*
* UDP echo server
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

void servfunc (int sockfd, struct sockaddr_in *client, int *len)
{
	char buf[BUFSIZE];
	int cnt;
    bzero(buf, BUFSIZE);
	cnt = recvfrom(sockfd, buf, BUFSIZE, 0, (struct sockaddr*)client, (socklen_t*)len);
    if (cnt<0)
    {
        printf ("Error recieving the message");
    }
    if (cnt>0)
    {
        sendto (sockfd, buf, cnt, 0, (struct sockaddr*)client, *len);
    }
    printf ("sent\n");
	
}

int main ()
{
	//Variable
	struct sockaddr_in serv;
	int sockfd, fval;
	
	//Set the required data
	bzero (&serv, sizeof (serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons (PORT);
	serv.sin_addr.s_addr = htons(IP);
	//create a concurrent server 
	
	//create socket
	sockfd= socket (AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf ("Unable to create socket!!\n");
		exit(0);
	}
	//bind to the socket 
	if (bind (sockfd, (struct sockaddr *)&serv,sizeof(serv)) == -1)
	{
		printf ("Bind error\n");
		exit(0);
	}

    struct sockaddr_in client;
    int len;

	//iteratively serve all the requests
    while (1)
    {
        len = sizeof (client);
        bzero (&client, len);
        servfunc(sockfd, &client, &len);
    }
	
	
	return 0;
}
