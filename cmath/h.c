#include <stdio.h>

int main(void)
{
  /*
   * compute sum 1 + 1/2 + ... + 1/n
   *
   * 1: i <- 0
   * 2: S <- 0
   * 3: i <- i+1
   * 4: S <- S+1/i
   * 5: if i<n, then goto line 3
   * 6: stop
   */
  /* compute the n-th partial sum of the harmonic series */
  int i, n;
  float S;

  printf("enter n ");
  scanf("%d", &n);

  i = 0;
  S = 0;
  do {
    i += 1;
    S += 1.0/i;
  } while (i < n);

  printf("H(%d) = %f\n", n,S);
  return 0;
}

