
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

static pthread_attr_t thread_attr;

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
    int result = pthread_create(&tid, &thread_attr, func, NULL);
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
    int result = pthread_attr_init(&thread_attr);
    if (0 != result)
    {
        printf("thread attr init error!\n");
    }

    size_t stacksize = 100;
    result = pthread_attr_getstacksize(&thread_attr, &stacksize);
    if (0 == result)
    {
        printf("stack size is %d B | %d kB | %d mB \n\n", 
                 stacksize, stacksize/1024, stacksize/1024/1024);
    }
    else
    {
        printf("get stack size error! \n");
    }
    
    stacksize = 2 * 1024 * 1024;
    result = pthread_attr_setstacksize(&thread_attr, stacksize);
    if (0 == result)
    {
        printf("set stack size %d B | %d kB | %d mB sucess!!\n\n", 
                 stacksize, stacksize/1024, stacksize/1024/1024);
    }
    else
    {
        printf("set stack size error!!\n\n");
    }


    printf("press ctrl+C to create a thread\n");

    signal(SIGINT, sigint_handle);

    while(1)
    {
        pause();
    }
}
