/*
* UDP echo Client
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUFSIZE 1024
#define PORT 5000
#define IP "127.0.0.1"
int main (int argc, char* argv[])
{
	//declare the variables
	struct sockaddr_in serv;
	char buf[BUFSIZE];
	int sockfd, cnt;
	//verify the arguments 
	if (argc != 2)
	{
		printf ("Format: ./a.out <serverIP> \n");
		exit(0);
	}
	//initialize the structures
	bzero (&serv, sizeof (serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	if (inet_pton(AF_INET,IP,(void* )&serv.sin_addr) == 0)
	{
		printf ("Invalid address\n");
		exit(0);
	}
	//establish connection
	sockfd = socket (AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		printf ("Unable to create socket!!\n");
		exit(0);
	}
	printf ("Socket created: %d\n", sockfd);
	
	//send the message
    printf ("Enter message:\n");
    bzero (buf, BUFSIZE);
    fgets (buf, BUFSIZE, stdin);
	cnt = sendto (sockfd, buf, strlen(buf), 0, (struct sockaddr*)&serv, sizeof (serv));
    if (cnt<0)
    {
        printf ("Unable to send\n");
        exit(0);
    }
	bzero (buf, BUFSIZE);
	cnt = recvfrom (sockfd, buf, BUFSIZE, 0, NULL, NULL);
    if (cnt<0)
        printf ("Error recieving");
    if (cnt>0)
		write (1, buf, cnt);
	
	//writing part to be added - right now printed to the console 
	close (sockfd);
	//close the connection
	
	return 0;
}
