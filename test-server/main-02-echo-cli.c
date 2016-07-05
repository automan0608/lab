
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include <signal.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#define PORT 6000
#define MAXLINE 1024
#define IP "127.0.0.1"

pthread_t tid;

typedef void Sigfunc(int);

Sigfunc *signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
//    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) 
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }
    else
    {
#if 0
        act.sa_flags |= SA_RESTART;
        printf("set syscall restart success\n");
#else 
        printf("set syscall not restart success\n");
#endif
    }

    if (sigaction(signo, &act, &oact) < 0 )
        return (SIG_ERR);

    printf("sigaction set success!\n");
    return (oact.sa_handler);
}

void sigint_handler(signo)
{
    printf("receive sigint\n");
    return;
}

void *func_pthread(void *arg)
{
    int connfd = (int)arg;
    int n = 0;
    char buf[MAXLINE];

    while(1)
    {
        printf("child thread:%d will read() \n", (int)pthread_self());
        n = read(connfd, buf, MAXLINE);
        printf("child thread read() return:%d\n", (int)n);
        raise(SIGINT);
        if (0 < n)
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
             {
        	     printf("errno EINTR\n");
             }
        	 printf("read error\n");
        	 exit(-1);
        }
    }
}

void func_echo(int connfd)
{
	ssize_t n;
	char buf[MAXLINE] = {0};
//	char *buf;

    int result = pthread_create(&tid, NULL, func_pthread, (void *)connfd);
    if (0 > result)
    {
        printf("thread create error!\n");
        exit(-1);
    }

	while (1)
	{
//        buf = readline(NULL);
        read(fileno(stdin), buf, MAXLINE);
        write(connfd, buf, strlen(buf));
again:
        printf("parent thread will read() \n");
        n = read(connfd, buf, MAXLINE);
        printf("parent thread read() return:%d\n", (int)n);
        if (0 < n)
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
            {
 	   	        printf("errno EINTR\n");
            //    goto again;
                continue;
            }

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

    signal(SIGINT, sigint_handler);

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
