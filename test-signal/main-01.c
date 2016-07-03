
#include <stdio.h>
#include <signal.h>
#include <sys/select.h>

void sigquit_handler(int signo)
{
    printf("in sigquit handler, will sleep 10 seconds\n");
#if 0
    sleep(10);
    printf("sigquit sleep end\n");
#else
    struct timeval tv={10, 0};
    select(1, NULL, NULL, NULL, &tv);
    printf("sigquit select end\n");
#endif
}

void sigint_handler(int signo)
{
    printf("in sigint handler\n");
#if 1
    sleep(3);
    printf("sigint sleep end\n");
#endif
}

int main()
{
    signal(SIGQUIT, sigquit_handler);
    signal(SIGINT, sigint_handler);

    while(1)
	pause();
}
