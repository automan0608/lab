
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

#if 1
void sigchld_handler(int signo)
{
	printf("receive sigchld:%d\n", signo);
	
	pid_t pid;
	int stat;

	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	
	return;
}
#endif

void func_echo(int connfd)
{
	size_t n;
	char buf[MAXLINE];

	while (1)
	{
again:
		if (0 < (n = read(connfd, buf, MAXLINE)))
		{
            /* sleep for 3 seconds */
            sleep(3);
			write(connfd, buf, n);
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
    int result=0 , listenfd=0;

    signal(SIGCHLD, sigchld_handler);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 >= listenfd)
    {
        printf("socket syscall error!\n");
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    result = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (0 > result)
    {
        printf("bind syscall error!\n");
        return -1;
    }

    result = listen(listenfd, 100);
    if (0 > result)
    {
        printf("listen syscall error!\n");
        return -1;
    }

    while(1)
    {
        struct sockaddr_in cliaddr;
        int connfd;
	socklen_t clilen = sizeof(cliaddr);

	printf("waiting for connection\n");
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
	if (0 >= connfd)
	{
		if (EINTR == errno)
			continue;

		printf("accept error\n");
		exit(-1);
	}
	
	if (0 == (result = fork()))
	{
		close(listenfd);
		func_echo(connfd);
		return 0;
	}
	else if (0 > result)
	{
		printf("fork error!\n");
		return -1;
	}
	else
	{
		close(connfd);
	}
    }
}
