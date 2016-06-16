
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_b = PTHREAD_MUTEX_INITIALIZER;
int notify_a = 0;
int notify_b = 0;

void *func(void *arg)
{
	pthread_mutex_lock(&lock_b);
	printf("func thread get lock_b, wanna get lock_a! \n");
	notify_b = 1;
	while (!notify_a)
		usleep(50);

	pthread_mutex_lock(&lock_a);
	printf("func thread get lock_a & lock_b! \n");
	pthread_mutex_unlock(&lock_a);
	pthread_mutex_unlock(&lock_b);
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	int result = 0;

	if(2 != argc) { printf("usage: ./a.out <stop-positon>\n"); return;}

	if(!strcmp(argv[1], "1")) { printf("stop at position 1"); sleep(1000); }

	pthread_mutex_init(&lock_a, NULL);
	pthread_mutex_init(&lock_b, NULL);
	
	result = pthread_create(&tid, NULL, func, NULL);
	if (0 != result)
	{
		printf("create thread error!\n");
	}
	printf("create thread success!\n");


	pthread_mutex_lock(&lock_a);
	printf("func thread get lock_b, wanna get lock_a! \n");

	notify_a = 1;
	while (!notify_b)
		usleep(50);

	pthread_mutex_lock(&lock_b);
	printf("main thread get lock_a & lock_b! \n");
	pthread_mutex_unlock(&lock_b);
	pthread_mutex_unlock(&lock_a);
}
