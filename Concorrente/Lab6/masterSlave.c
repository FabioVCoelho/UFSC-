#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
	int i,size,rank;
	MPI_Status st;
	MPI_Init(&argc, &argv); // inicializao ambiente MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0)	{
		for(i = 1; i < size; i++)	{
			MPI_Send(NULL,0,MPI_INT,i,0,MPI_COMM_WORLD);
			printf("Sending from %d \n", rank);
		}
		for(i = 1; i < size; i++)	{
			int rankRecebido;
			MPI_Recv(&rankRecebido,1,MPI_INT,i,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
			printf("receiving from %d \n", rankRecebido);
		}
	} else {
			MPI_Recv(NULL,0,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
			MPI_Send(&rank,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}

