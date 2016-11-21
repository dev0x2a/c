/*
 * h.c
 * compute the n-th partial sum of the harmonic series
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("%s <n>-th partial sum of the harmonic series\n",argv[0]);
    return(-1);
  }

  int i, n;
  float S;
  
  n = atol(argv[1]);
  i = 0;
  S = 0;
  
  do {
    i += 1;
    S += 1.0/i;
  } while (i < n);

  printf("H(%d) = %f\n", n,S);
  return(0);
}

