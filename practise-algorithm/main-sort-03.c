#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void printNums(int *sortnum, int num);
static void mysort(int *sortnum, int num);
static void mysortWithInterval(int *sortnum, int interval, int num);

int main(int argc, char const *argv[])
{

    printf("argc:%d\n", argc);
    if (2 != argc)
    {
        printf("Usage: ./a.out num\n");
        exit(-1);
    }

    int num;
    int *sortnum;
    int i;

    num = atoi(argv[1]);
    printf("there are %d nums will be random generate and be sort\n", num);

    sortnum = (int *)malloc(num * sizeof(int));
    memset(sortnum, 0, num * sizeof(int));

    srandom(time(NULL));
    for (i = 0; i < num; ++i)
    {
        sortnum[i] = random() % 100;
    }

    printNums(sortnum, num);

    mysort(sortnum, num);

    printNums(sortnum, num);

    return 0;
}

static void printNums(int *sortnum, int num)
{
    int i;

    for (i = 0; i < num; ++i)
    {
        printf("sortnum[%d] = %d\n", i, sortnum[i]);
    }
}

// *** sort
static void mysort(int *sortnum, int num)
{
    printf("in mysort\n");

    int interval;

}

static void mysortWithInterval(int *sortnum, int interval, int num)
{
    printf("in mysortWithInterval, interval:%d, num:%d\n", interval, num);
}

