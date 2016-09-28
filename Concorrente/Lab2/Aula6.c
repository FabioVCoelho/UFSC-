#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *PrintHelloSequencia(void *arg)	{
	long int val = (long int) arg;
	pthread_t tid = pthread_self();
	printf("Thread %u: Com (Join no For) arg = %ld \n", (unsigned int)tid, val);
	pthread_exit(NULL);
}

void *PrintHello(void *arg)	{
	long int val = (long int) arg;
	pthread_t tid = pthread_self();
	printf("Thread %u: Com (2 for) arg = %ld \n", (unsigned int)tid, val);
	pthread_exit(NULL);
}

int main (int argc, char *argv[])	{
	pthread_t thread;
	char *p;
	long conv = strtol(argv[1], &p, 10);
	long int i = 0;
	for(i = 0; i < conv; i++)	{
		pthread_create(&thread, NULL, PrintHelloSequencia, (void *)i);
		pthread_join(thread, NULL);
	}
	for(i = 0; i < conv; i++)	{
		pthread_create(&thread, NULL, PrintHello, (void *)i);
	}
		for(i = 0; i < conv; i++)	{
		pthread_join(thread, NULL);
	}
	pthread_exit(NULL);

}
