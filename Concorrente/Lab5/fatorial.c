#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
  int n;
  long int res;
  int i;
  n = atoi(argv[1]);
  res = 1;
  #pragma omp parallel reduction(*:res)
  #pragma omp for
  for(i = 2; i <= n; i++){
    res *= i;
  }
  return 0;
}

