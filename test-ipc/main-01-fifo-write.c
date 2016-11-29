
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <limits.h>

#define PATH "/tmp/fifotmp"

#define MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int main()
{
    printf("PIPE_BUF is %ld\n", pathconf(PATH, _PC_PIPE_BUF));
    printf("OPEN_MAX is %ld\n", sysconf(_SC_OPEN_MAX));

    int re = mkfifo(PATH, MODE);
    if (0 != re)
    {
        printf("mkfifo error ! \n");
        exit(-1);
    }

    printf("mkfifo success\n");

    int fd = open(PATH, O_WRONLY, 0);
    if (0 >= fd)
    {
        printf("open fifo error ! \n");
        exit(-1);
    }

    printf("open success, fd:%d\n", fd);

    char buf[1024] = {0};
    while (1)
    {
        read(STDIN_FILENO, buf, sizeof(buf));
        write(fd, buf, strlen(buf));

        memset(buf, 0, sizeof(buf));
    }
}
