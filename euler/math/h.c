/*
 * h.c
 * compute the n-th partial sum of the harmonic series
 */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  int i, n;
  float S;

  if (argc != 2) {
    fprintf(stderr, "%s <num>\n", argv[0]);
    return(-1);
  }
  n = atol(argv[1]);
  i = 0;
  S = 0;

  do {
    i += 1;
    S += 1.0/i;
  } while (i < n);

  printf("H(%d) = %f\n", n, S);
  return 0;
}

