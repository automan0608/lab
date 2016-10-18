
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#define PORT 6000
#define MAXLINE 1024

int main()
{
    struct sockaddr_in servaddr;
    int result=0 , listenfd=0;
    const int on = 1;

    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (0 >= listenfd)
    {
        printf("socket syscall error!\n");
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    result = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (0 > result)
    {
        printf("bind syscall error!\n");
        return -1;
    }

    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    
    char buff[MAXLINE] = {0};

    while(1)
    {
	printf("wait to receive\n");

	memset(buff, 0, MAXLINE);
	int n = recvfrom(listenfd, buff, MAXLINE, 0, (struct sockaddr *)&cliaddr, &clilen);

	printf("pid:%d, recv buf is : %s\n", getpid(), buff);

    }
}
