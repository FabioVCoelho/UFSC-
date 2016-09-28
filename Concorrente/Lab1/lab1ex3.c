#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void  ChildProcess(void); 
void ParentProcess(void);

int main(int argc, char const *argv[])
{
	pid_t pid;
	for(int i = 0; i < 2; i++)	{
		pid = fork();
		if (pid == 0)	{
			for (int j = 0; j < 2; j++)	{
				pid_t pid2 = fork();
				if (pid2 == 0)	{
					printf("Processo %d filho de %d: criado.\n", getpid(), getppid());
					break;
				}
			}
			break;
		} else	{
			printf("Processo pai %d: criou %d.\n", getpid(), pid);
		}
	}

	while ((pid = wait(NULL)) > 0)	{}
	return 0;
}
