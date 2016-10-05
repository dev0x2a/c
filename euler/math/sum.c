/*
 * sum.c
 * sum n terms of the harmonic series
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
  S = 0.0;

  for (i=1; i<=n; ++i)
    S += 1.0/i;

  printf("H(%d) = %f\n", n, S);
  return 0;
}

