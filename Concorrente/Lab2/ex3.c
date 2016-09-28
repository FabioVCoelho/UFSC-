#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int contador_global = 0;
pthread_mutex_t mutex;

void *PrintID(void *arg)	{
	pthread_t tid = pthread_self();
	pthread_mutex_lock(&mutex);
	/* Área Crítica, é executado isto em cada thread criada. */
	for(int i = 0; i < 100; i++)	{
		contador_global++;
	}
	printf("Nova Thread Criada. TID = %u! \n", (unsigned int)tid);
	printf("Valor do contador_global: %i\n", contador_global);
	/* Fim da área crítica. */
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
	if (argc != 2)	{
		printf("Insira o número de threads que deseja criar após a chamada do programa.");
		return 1;
	}
	int MAX_THREADS = atoi(argv[1]);

	pthread_t thread[MAX_THREADS];

	pthread_mutex_init(&mutex, NULL);
	
	for(int i = 0; i < MAX_THREADS; i++)	{
		pthread_create(&thread[i], NULL, PrintID, (void *)0);
	}
	for(int j = 0; j < MAX_THREADS; j++)	{
	pthread_join(thread[j],NULL);
	}
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);	
	return 0;
}