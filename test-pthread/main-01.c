
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

void *func(void *arg)
{
    printf("in thread func, will pause\n");
    while(1)
    {
        pause();
    }
}

void sigint_handle(int signo)
{
    printf("receive sigint, signo:%d\n", signo);
    
    pthread_t tid;
    int result = pthread_create(&tid, NULL, func, NULL);
    if (0 == result)
    {
        printf("create thread success!!\n");
    }
    else
    {
        printf("create thread error !!!!!!\n");
    }
}

int main()
{
    printf("press ctrl+C to create a thread\n");

    signal(SIGINT, sigint_handle);

    while(1)
    {
        pause();
    }
}
