
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
//#define IP "192.168.0.11"

//char *ip = "192.168.0.11";
char *ip = "172.31.1.164";

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

    result = inet_pton(AF_INET, ip, &servaddr.sin_addr.s_addr);

    printf("set servaddr 0x%02x%02x%02x%02x\n", 
		    ((unsigned char *)&servaddr.sin_addr.s_addr)[0],
		    ((unsigned char *)&servaddr.sin_addr.s_addr)[1],
		    ((unsigned char *)&servaddr.sin_addr.s_addr)[2],
		    ((unsigned char *)&servaddr.sin_addr.s_addr)[3]
		    );

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
