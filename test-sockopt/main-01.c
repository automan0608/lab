#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{

    int sockfd, n;
    struct sockaddr_in addr;

    if (sockfd = socket(AF_INET,SOCK_STREAM, 0), sockfd < 0)
    {
        printf("socket call error\n");
        exit(1);
    }

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(50443);
    if (inet_pton(AF_INET,"172.29.88.115", &addr.sin_addr) <= 0)
    {
        printf("inet_pton call error\n");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("connect call error\n");
        exit(1);
    }

    int rcvbuflen = 0;
    int sndbuflen = 0;
    int rcvoptlen = sizeof(rcvbuflen);
    int sndoptlen = sizeof(sndbuflen);

    if (getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcvbuflen, &rcvoptlen) < 0)
    {
        printf("getsockopt call error\n");
        exit(1);
    }

    if (getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sndbuflen, &sndoptlen) < 0)
    {
        printf("getsockopt call error\n");
        exit(1);
    }

    close(sockfd);

    printf("recv buffer size : %d\n", rcvbuflen);
    printf("send buffer size : %d\n", sndbuflen);
    
}
