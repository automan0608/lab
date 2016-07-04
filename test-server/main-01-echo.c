
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 6000

void sigchld_handler(int signo)
{
    printf("receive sigchld:%d\n", signo);
    return;
}

int main()
{
    struct sockaddr_in sa;
    int result=0 , fd=0;

    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (0 >= fd)
    {
        printf("socket syscall error!\n");
        return -1;
    }

    bzero(sa, sizeof(sockaddr_in);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(PORT);

    result = bind(fd, (struct sockaddr*)&sa, sizeof(sa));
    if (0 >= result)
    {
        printf("bind syscall error!\n");
        return -1;
    }

    result = listen(fd, 100);
    if (0 >= result)
    {
        printf("listen syscall error!\n");
        return -1;
    }

    while(1)
    {
        struct sockaddr_in cliaddr;
        int clifd;

        re = accept(fd, (struct sockaddr_in*)&cliaddr, sizeof(cliaddr));
    }


}
