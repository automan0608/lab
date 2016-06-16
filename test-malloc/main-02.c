
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


#define FRAG_NUM  10000

static memsize = 0;

int main(int argc, char *argv[])
{
    if (!strcmp(argv[1],"1"))   {   printf("in 1 position\n");  sleep(1000);     }

#if 0
    mallopt(M_TRIM_THRESHOLD, 4);
#endif
    
    int SIZE_LIMIT = atoi(argv[2]);
    
    int i = 0;
    size_t size[FRAG_NUM] = {0};
    
    srand(time(NULL));

    char *result[FRAG_NUM] = {NULL};
    for (i = 0; i < FRAG_NUM; i++)
    {
        size[i] = rand() % SIZE_LIMIT;
        result[i] = (char *)malloc(size[i]);
        if (NULL != result[i])
        {
            memset(result[i], 0, size[i]);

            memsize += size[i];
            printf("malloc  %dth success, memsize: %d\n", i + 1, memsize);
        }
        else
        {
            printf("malloc  %dth fail\n", i + 1);
        }
    }

    if (!strcmp(argv[1],"2"))   {   printf("in 2 position\n");  sleep(1000);     }

#if 0
    for (i = 0; i < FRAG_NUM; i++)
    {
        memset(result[i], 0, size[i]);
    }
    printf("memset all success\n");
#endif

    if (!strcmp(argv[1],"3"))   {   printf("in 3 position\n");  sleep(1000);     }
    
    for (i = 0; i < FRAG_NUM; i++)
    {
        free(result[i]);
        memsize -= size[i];
        printf("free %dth success, memsize: %d\n", i + 1, memsize);
    }
    printf("free all success\n");

    if (!strcmp(argv[1],"4"))   {   printf("in 4 position\n");  sleep(1000);     }

    malloc_trim(0);

    printf("malloc trim 0 success\n");

    if (!strcmp(argv[1],"5"))   {   printf("in 5 position\n");  sleep(1000);     }
}
