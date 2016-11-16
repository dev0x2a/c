#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "typedef.h"

u8 bittab[8] = {
  1,2,4,8,16,32,64,128
};

int ptab[9] = {
  2,3,5,7,11,13,17,19,23
};

int pwr(int b, uint e);
int witness(u64 a, u64 n);
int primality(u64 n, u64 trials);
u64 bpwr(u64 p, const u64 q, const u64 a);
u64 msb(u64 u);

int main(int argc, char *argv[])
{
  u64 n, k, r, x, d;

  n = atoi(argv[1]);
  if (n == 2) {
    puts("2 is prime");
    exit(0);
  }

  if (!(n&1) || n%2==0 || (signed)n<=1) {
    printf("%lld not prime\n");
    exit(0);
  }
  k = 100000;
  primality(n, k);

#if 0
  /*
   * write n-1 as (2^r)*d, with d odd
   *  by factoring powers 2 from n-1
   */
    /*
    int w = 0;
    while ((n-1)%2 == 0) {
      (n-1) /= 2;
      ++w;
    }*/

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
#endif

  exit(0);
}

int pwr(int b, uint e)
{
  int i, r = 1; 
  for (i=0; i<e; ++i)
    r *= b;
  return(r);
}

int primality(u64 n, u64 trials)
{
  u64 a;
  int i;
  srand(time(NULL));

  for (i=0; i<trials; ++i) {
    a = rand()%(n-1)+1;
    if (witness(a, n)) {
      printf("%llu not prime\n", n);
      exit(1);
    }
  }
  printf("%llu is probably prime\n", n);
  exit(0);
}

int witness(u64 a, u64 n)
{
  u64 u, t, x, w, i;
  int mask;

  u = n-1;
  t = 0;
  while (u&1 == 0) {
    u >>= 1;
    t++;
  }

  x = bpwr(u, a, n);
  for (i=0; i<t; ++i) {
    w = x;
    x = (w*w)%n;
    if (x==1 && w!=1 && w!=n-1)
      return(1);
  }
  return(x != 1);
}

u64 msb(u64 u)
{
  u |= u>>bittab[0];
  u |= u>>bittab[1];
  u |= u>>bittab[2];
  u |= u>>bittab[3];
  u |= u>>bittab[4];
  u |= u>>bittab[5];
  
  return(u&~(u>>1));
}

u64 bpwr(u64 p, const u64 q, const u64 a)
{
  u64 r = 1;
  u64 mask = msb(p);
  while (mask) {
    if (mask&p)
      r = (r*q)%a;
    mask >>= 1;
  }
  return(r);
}

#if 0
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

