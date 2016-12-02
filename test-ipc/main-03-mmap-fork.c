
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/mman.h>
#include <semaphore.h>

#define SHARELEN 1024

int main()
{
    int fd;
    void *shm;
    size_t shmlen;
    pid_t pid;
    sem_t *semshd;
    int *numshd;
    int result;
    int second;

    shmlen = sizeof(sem_t) + sizeof(int);

    // mmap
#if 0
    fd = open("/dev/zero", O_CREAT);
    if (0 > fd)
    {
        printf("open /dev/zero error\n");
        exit(-1);
    }
    printf("open /dev/zero success\n");

    ftruncate(fd, shmlen);
    shm = mmap(NULL, shmlen, PROT_WRITE| PROT_READ, 
                        MAP_SHARED, fd, 0);
    close(fd);
#else
    shm = mmap(NULL, shmlen, PROT_WRITE | PROT_READ, 
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
#endif

    if (NULL == shm)
    {
        printf("mmap error\n");
        exit(-1);
    }
    printf("mmap success\n");

    // memset
    memset(shm, 0, shmlen);
    printf("memset success\n");

    semshd = (sem_t *)shm;
    numshd = (int *)(shm + sizeof(sem_t));

    // sem_init
    result = sem_init(semshd, 1, 1);
    if (0 != result)
    {
        printf("sem init error\n");
        exit(-1);
    }
    printf("sem init success\n");

    // fork
    if (0 > (pid = fork()))
    {
        printf("fork error\n");
        exit(-1);
    }
    else if (0 == pid)
    {
        printf("child process start\n");

        while (1)
        {
            sem_wait(semshd);

            printf("child process, num:%d\n", *numshd);
        }
    }

    printf("parent process start\n");

    while (1)
    {
        printf("parent process, num++\n");

        // plus 1 to make sure sleep not 0 second.
        second = random()%5 + 1;
        sleep(second);

        (*numshd)++;
        sem_post(semshd);
    }

    // munmap
    result = munmap(shm, shmlen);
}

