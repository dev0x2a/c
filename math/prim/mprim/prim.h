#ifndef PRIM_H
#define PRIM_H

#include "prutil.h"


/*
int pr_bin(int);
int pr_cprimes(int)
int pr_gcd(int, int);
int pr_lcm(int, int);
int pr_atoi(const char*);
int pr_modular(int, uint, uint);
u64 pr_bpwr(u64, u64);
*/

u64 pr_bpwr(u64 x, u64 n)
{
  u64 r = 1, y = x;
  while (n > 1) {
    if (n&1)
      r *= y;
    n = (int)(n/2);
    y *= y;
  }
  r *= y
  return(r);
}

#if 0
int pr_pwr(int b, uint e)
{
  int i, r = 1; 
  for (i=0; i<e; ++i)
    r *= b;
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

int pr_gcd(int a, int b)
{
  while (a != b) {
    if (a > b)
      a -= b;
    else
      b -= a;
  }
  return(a);
}

int pr_lcm(int x, int y)
{
  return(x/pr_gcd(x,y)*y);
}

int pr_isprime(int n)
{
  int i;
  if (n <= 1)
    return(0);
  if (n == 2)
    return(1);
  for (i=3; i*i<=n; i+=2) 
    if (n%i == 0)
      return(0);
  return(1);
}

int pr_cprimes(int n)
{
  int i, c = 0;
  for (i=2; i<n; ++i) 
    if (pr_isprime(i))
      ++c;
  return(c);
}

int pr_bin(int n)
{
  int u, i;
  if (n > 255)
    u = 31;
  else
    u = 7;
  for (i=u; i>=0; --i) {
    if ((n>>i)&1)
      putchar('1');
    else
      putchar('0');
  }
  putchar('\n');
  return(0);
}
#endif
#endif /* PRIM_H */
