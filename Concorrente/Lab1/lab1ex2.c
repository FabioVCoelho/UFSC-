#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void  ChildProcess(void); 
void ParentProcess(void);

int main(int argc, char const *argv[])
{
	pid_t pid;
	for(int i = 0; i < 4; i++)	{
		pid = fork();
		if (pid == 0)	{
			printf("Processo filho %d: criado.\n", getpid());
			break;
		} else	{
			printf("Processo pai %d: criou %d.\n", getpid(), pid);
		}
	}
	return 0;
}
