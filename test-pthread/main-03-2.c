
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t tid;

int maxNum;
int iter;
int sum;

void *func(void *arg)
{
    (char *)arg;

    while (1)
    {
        pthread_mutex_lock(&lock);
 
        iter++;
        sum += iter;
        if(maxNum < iter)
        {
            printf("sum of 1 - %d is %d\n", maxNum, sum);

            pthread_mutex_unlock(&lock);
            break;
        }
 
        pthread_mutex_unlock(&lock);
    }

    if (!strcmp(arg,"2"))   {   printf("in 2 position\n");  sleep(100);     }
}

int main(int argc, char *argv[])
{
    int result;

    if (3 != argc) { printf("usage: ./a.out <stop-posion> <iteration num>\n"); return -1;}

    maxNum = atoi(argv[2]);
    iter = 0;

    if (!strcmp(argv[1],"1"))   {   printf("in 1 position\n");  sleep(100);     }

    result = pthread_create(&tid, NULL, func, &argv[1]);
    if (0 != result)
    {
        printf("create thread error!\n");
    }
    printf("create thread success!\n");

    while (1)
    {
        pthread_mutex_lock(&lock);
 
        iter++;
        sum += iter;
        if(maxNum < iter)
        {
            printf("sum of 1 - %d is %d\n", maxNum, sum);

            pthread_mutex_unlock(&lock);
            break;
        }
 
        pthread_mutex_unlock(&lock);
    }
    if (!strcmp(argv[1],"2"))   {   printf("in 2 position\n");  sleep(100);     }

}
