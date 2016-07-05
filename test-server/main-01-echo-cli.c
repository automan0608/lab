
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

void func_echo(int connfd)
{
	size_t n;
	char buf[MAXLINE] = {0};
//	char *buf;

	while (1)
	{
//        buf = readline(NULL);
        read(fileno(stdin), buf, MAXLINE);
        write(connfd, buf, strlen(buf));
again:
		if (0 < (n = read(connfd, buf, MAXLINE)))
		{
            buf[n] = '\0';
            write(fileno(stdout), buf, strlen(buf));
            memset(buf,0,MAXLINE);
		}
		else if (0 == n)
		{
			close(connfd);
			break;
		}
		else
		{
			if (errno == EINTR)
				goto again;
			printf("read error\n");
			exit(-1);
		}
	}
}

int main()
{
    struct sockaddr_in servaddr;
    int result=0 , sockfd=0;
    unsigned char buf[sizeof(struct in_addr)];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 >= sockfd)
    {
        printf("socket syscall error!\n");
        return -1;
    }

    result = inet_pton(AF_INET, IP, &servaddr.sin_addr.s_addr);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
//    servaddr.sin_addr.s_addr = buf;
    servaddr.sin_port = htons(PORT);

    result = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (0 > result)
    {
        printf("connect syscall error!\n");
        return -1;
    }

    func_echo(sockfd);
}
