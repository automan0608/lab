
#include <stdio.h>
#include <signal.h>
#include <sys/select.h>

typedef void Sigfunc(int);

Sigfunc *signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
//    sigfillset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM) 
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }
    else
    {
        act.sa_flags |= SA_RESTART;
    }

    if (sigaction(signo, &act, &oact) < 0 )
        return (SIG_ERR);

    printf("sigaction set success!\n");
    return (oact.sa_handler);
}

void sigquit_handler(int signo)
{
    printf("in sigquit handler, will sleep 10 seconds\n");
#if 1
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
