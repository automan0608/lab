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

static int partition(int sortnum[], int num, int start, int end)
{
    int val = sortnum[start];

    while (start < end)
    {
        printf("."); fflush(stdout);
        while (sortnum[start] < val)
            start++;
        while (sortnum[end] > val)
            end--;

        int tmp = sortnum[start];
        sortnum[start] = sortnum[end];
        sortnum[end] = tmp;
    }

    printNums(sortnum, num);
    return start;
}

static int fastsort(int sortnum[], int num, int start, int end)
{
    printf("in fastsort, start:%d, end:%d\n", start, end);

    int pos = partition(sortnum, num, start, end);

    printf("pos:%d\n", pos);

    if (pos > start)
        fastsort(sortnum, num, start, pos - 1);

    if (pos < end)
        fastsort(sortnum, num, pos + 1, end);
}

// *** sort
static void mysort(int *sortnum, int num)
{
    printf("in mysort\n");

    if (NULL == sortnum)
    {
        printf("parameter error\n");
        exit(-1);
    }

    fastsort(sortnum, num, 0, num - 1);

}

