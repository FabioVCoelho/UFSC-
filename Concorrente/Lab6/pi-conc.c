#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

unsigned int compute_pi(unsigned int, unsigned int);

int main(int argc, char **argv){
  unsigned int pontos;
  unsigned int pontos_no_circulo;
  unsigned int i;
  int size,rank;
  int pontoTotal = 0;
  
  if(argc != 2){
    printf("Uso:\n");
    printf("\t%s <numero de pontos a serem sorteados>\n", argv[0]);
    return 1;
  }

  pontos = atoi(argv[1]);
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int pontosParaCadaProcesso = pontos / (size - 1);
  int j;
  if(rank==0) {
    for(j = 1;j<size;j++) {
    MPI_Send(NULL,0,MPI_INT,j,0,MPI_COMM_WORLD);
    }
    for(j = 1;j<size;j++) {
    int pontosAcertados;
    MPI_Recv(&pontosAcertados,1,MPI_INT,j,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    pontoTotal += pontosAcertados;
    printf("Pi = %.040f\n", ((double)pontoTotal/(double)pontos)*4);
    }
  } else  {
    MPI_Recv(NULL,0,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    unsigned int oi = compute_pi(rank,pontosParaCadaProcesso);
    MPI_Send(&oi,1,MPI_INT,0,0,MPI_COMM_WORLD);
  }
  // retorna quantos pontos sorteados cairam dentro do circulo
  // aqui estamos considerando uma semente para o gerador de 
  // numeros aleatorios fixa = 0
  // calcula a aproximacao de Pi baseado nos pontos sorteados
  MPI_Finalize();
  return 0;
}

unsigned int compute_pi(unsigned int seed, unsigned int pontos){
  unsigned int i;
  unsigned int pontos_no_circulo;
  double x, y;

  srand(seed);
  pontos_no_circulo = 0;
  
  for(i=0; i<pontos; i++){
  	// sorteia um ponto: coordenadas x e y dentro do quadrado
  	// consideramos que R = 1, então x e y pertencem ao intervalo [0; 1]
    x = (double)rand()/(double)(RAND_MAX);
    y = (double)rand()/(double)(RAND_MAX);      
    
    // verifica se o ponto sorteado encontra-se dentro do circulo
    // um ponto (x, y) esta dentro do circulo se: x^2 + y^2 < R^2
    // nesse caso, consideramos R = 1
    if( (x*x + y*y) < 1 ){
      pontos_no_circulo++;
    }      
  }
  
  return pontos_no_circulo;
}
