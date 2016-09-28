#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	fork();

	return	printf("%s\n", "Novo processo criado! ");
	return 0;
}
