
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#define PORT 6000
#define MAXLINE 1024
//#define IP "127.0.0.1"
#define IP "192.168.0.1"


int main()
{
    struct sockaddr_in servaddr;
    int result=0 , sockfd=0;
    unsigned char buff[MAXLINE];
    const int on = 1;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 >= sockfd)
    {
        printf("socket syscall error!\n");
        return -1;
    }

    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));

    result = inet_pton(AF_INET, IP, &servaddr.sin_addr.s_addr);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);


    while (read(fileno(stdin), buff, MAXLINE) > 0)
    {
	    printf("will broadcast: %s\n", buff);
	    sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

	    memset(buff, 0, MAXLINE);
    }
}
