#include <stdio.h>

/* sum n terms of the harmonic series */

int main(void)
{
  int i, n;
  float S;

  n = 100;
  S = 0.0;

  for (i=1; i<=n; ++i)
    S += 1.0/i;

  printf("H(%d) = %f\n", n,S);
  return 0;
}

