#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "typedef.h"

u8 bittab2[] = {
  1,2,4,8,16,32,64,128
};

int ptab[9] = {
  2,3,5,7,11,13,17,19,23
};

int pwr(int b, uint e);

int main(int argc, char *argv[])
{
  unsigned long long n, k, r, a, x, d;
  int i, j;

  n = atoi(argv[1]);

  if (!(n&1)) {
    printf("%d not prime\n");
    exit(0);
  }
  k = 100;
  d = 1;
  r = 1;


  /*
   * write n-1 as (2^r)*d, with d odd
   *  by factoring powers 2 from n-1
   */
  srand(time(NULL));

  for (i=0; i<=k; ++i) {
    a = rand()%((n-2)-2+1)+2;
    d+=2;
    ++r;

    x = pwr(a, d)%n;
    if (x==1 || x==n-1) {
      continue;
    }
    for (j=0; j<=r-1; ++j) {
      x = (x*x)%n;
      if (x == 1) { /* loc A */
        puts("composite (A)");
      }
      if (x == n-1) {
        continue;
      }
    /* loc B */
    puts("composite (B)");
    }
    /* loc C */
    puts("prob prime (C)");
  }


  exit(0);
}

int pwr(int b, uint e)
{
  int i, r = 1; 
  for (i=0; i<e; ++i)
    r *= b;
  return(r);
}

#if 0
u64 pr_bpwr(u64 n, u64 e)
{
  u64 r = 1;
  while (e > 0) {
    if ((e&1) != 0)
      r *= n;
    n *= n;
    e >>= 1;
  }
  return(r);
}

int pr_modular(int b, uint e, uint m)
{
  int i,
      z = sizeof(int)*8,
      r = 1,
      p=b%m;

  for (i=0; i<z; ++i) {
    int lbit = 0x00000001&(e>>i);
    if (lbit)
      r = (r*p)%m;
  }
  return(r);
}
#endif

