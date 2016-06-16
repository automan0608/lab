
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (!strcmp(argv[1],"1"))   {   printf("in 1 position\n");  sleep(100);     }

    size_t size = 300*1024;

    char *result = (char*)malloc(size);
    if (NULL != result)
    {
        printf("malloc success\n");
    }
    else
    {
        printf("malloc fail\n");
    }

    if (!strcmp(argv[1],"2"))   {   printf("in 2 position\n");  sleep(100);     }

    memset(result, 0, size);

    if (!strcmp(argv[1],"3"))   {   printf("in 3 position\n");  sleep(100);     }
    
    free(result);

    if (!strcmp(argv[1],"4"))   {   printf("in 4 position\n");  sleep(100);     }
}
