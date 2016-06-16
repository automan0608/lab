
#include <stdio.h>
#include <stdlib.h>

static int sum;
static int i;
static int times ;

int main(int argc, char *argv[])
{
    if(2 != argc)
    {   printf("input error!\n");}

    if(!strcmp(argv[1], "1")) { printf("at postion 1\n"); sleep(1000); }

    times = atoi(argv[2]);

    for (i = 0; i < times; i++)
    {
        sum += i;
    }
    
    printf("calc sum 1 - %d complete, result:%d\n", times, sum);
}
