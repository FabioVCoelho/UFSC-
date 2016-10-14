#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NRA 8                 /* number of rows in matrix A */
#define NCA 8                 /* number of columns in matrix A */
#define NCB 8                 /* number of columns in matrix B */

int main (int argc, char *argv[])
{
  int i, j, k;

  /* matrix A to be multiplied */
  double **a = (double **) malloc(sizeof(double *) * NRA);
  #pragma omp parallel for
  for (i = 0; i < NRA; i ++)
    a[i] = (double *) malloc(sizeof(double) * NCA);

  /* matrix B to be multiplied */
  double **b = (double **) malloc(sizeof(double *) * NCA);
  #pragma omp parallel for
  for (i = 0; i < NCA; i ++)
    b[i] = (double *) malloc(sizeof(double) * NCB);

  /* result matrix C */
  double **c = (double **) malloc(sizeof(double *) * NRA);
  #pragma omp parallel for
  for (i = 0; i < NRA; i ++)
    c[i] = (double *) malloc(sizeof(double) * NCB);

  /*** Initialize matrices ***/
  #pragma omp parallel for private(i,j)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++)
      a[i][j]= i+j;

  #pragma omp parallel for private(i,j)
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++)
      b[i][j]= i*j;

  #pragma omp parallel for private(i,j)
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++)
      c[i][j]= 0;

  /*** Do the matrix-matrix multiplication ***/
  #pragma omp parallel for private(i,j,k)
   for (i=0; i<NRA; i++)
      for(j=0; j<NCB; j++)
        for (k=0; k<NCA; k++)
          c[i][j] += a[i][k] * b[k][j];

  #pragma omp parallel for
  for (i = 0; i < NRA; i ++)
    free(a[i]);
  free(a);

  #pragma omp parallel for
  for (i = 0; i < NCA; i ++)
    free(b[i]);
  free(b);

  #pragma omp parallel for
  for (i = 0; i < NRA; i ++)
    free(c[i]);
  free(c);

  return 0;
}
