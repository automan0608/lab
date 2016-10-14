
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
#define IP "127.0.0.1"


int main()
{
    struct sockaddr_in servaddr;
    int result=0 , sockfd=0;
    unsigned char buff[MAXLINE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 >= sockfd)
    {
        printf("socket syscall error!\n");
        return -1;
    }

    result = inet_pton(AF_INET, IP, &servaddr.sin_addr.s_addr);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);


    while (read(fileno(stdin), buff, MAXLINE) > 0)
    {
	    printf("will send to svr: %s\n", buff);
	    sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

	    memset(buff, 0, MAXLINE);
    }
}
