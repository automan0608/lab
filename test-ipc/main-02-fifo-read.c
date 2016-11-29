
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PATH "/tmp/fifotmp"

#define MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int main()
{
    int re = open(PATH, O_RDONLY);
    if (0 >= re)
    {
        printf("open fifo error ! \n");
        exit(-1);
    }

    char buf[1024] = {0};
    while (1)
    {
        read(re, buf, sizeof(buf));
//        fputs(buf, stdout);
        write(STDOUT_FILENO, buf, sizeof(buf));

        memset(buf, 0, sizeof(buf));
    }
}
