
#include <pthread.h>
#include <stdio.h>

int maxNum;
int iter;
int sum;

int main(int argc, char *argv[])
{
    int result;

    if (3 != argc) { printf("usage: ./a.out <stop-posion> <iteration num>\n"); return -1;}

    maxNum = atoi(argv[2]);
    iter = 0;

    if (!strcmp(argv[1],"1"))   {   printf("in 1 position\n");  sleep(100);     }

    printf("will start calc\n");
    while (1)
    {
        iter++;
        sum += iter;
        if(maxNum < iter)
        {
            printf("sum of 1 - %d is %d\n", maxNum, sum);
            break;
            return 0;
        }
    }
    
    if (!strcmp(argv[1],"2"))   {   printf("in 2 position\n");  sleep(100);     }
    return 0;

}
