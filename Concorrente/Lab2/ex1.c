#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 5;

void *PrintID(void *arg)	{
	pthread_t tid = pthread_self();
	printf("Nova Thread Criada. TID = %u! \n", (unsigned int)tid);
}

int main(int argc, char const *argv[])
{
	pthread_t thread;
	for(int i = 0; i < MAX_THREADS; i++)	{
		pthread_create(&thread, NULL, PrintID, (void *)123);
	}
	for(int i = 0; i < MAX_THREADS; i++)	{
	pthread_join(thread,NULL);
	}
	pthread_exit(NULL);	
	return 0;
}