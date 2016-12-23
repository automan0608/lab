#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void printNums(int *sortnum, int num);
static void mysort(int *sortnum, int num);

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

// insert sort
static void mysort(int *sortnum, int num)
{
    printf("in mysort, sortnum:%p, num:%d\n", sortnum, num);

    int i = 0, j = 0;

    for (i = 0; i < num; ++i)
    {
        for (j = 0; j < num - i -1; ++j)
        {
            if (sortnum[j] > sortnum[j + 1])
            {
                int tmp = sortnum[j];
                sortnum[j] = sortnum[j + 1];
                sortnum[j + 1] = tmp;
            }
        }
    }
    printNums(sortnum, num);
    printf("out mysort\n");
}
