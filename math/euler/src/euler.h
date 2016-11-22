#ifndef EULER_H
#define EULER_H

#include "typedef.h"

/*
 * euler.h
 * ryan keleti (c) 2016
 *
 * prefix global/external vars or functions with eul_
 */

u64 eul_power(u64 n, u64 e)
{
  u64 r=1;
  while (e>0) {
    if ((e&1)!=0)
      r*=n;
    n*=n;
    e>>=1;
  }
  return r;
}

int eul_gcd(int a, int b)
{
  while (a!=b) {
    if (a>b) a-=b;
    else b-=a;
  }
  return a;
}

int eul_lcm(int a,int b)
{
  return(a/gcd(a,b)*b);
}

int eul_isprime(int n)
{
  int i;
  if (n<=1) return 0;
  if (n==2) return 1;
  for (i=3; i*i<=n; i+=2) 
    if (n%i==0) return 0;
  return 1;
}


u64 eul_bpwr(u64 x, u64 n)
{
  u64 r=1, y=x;
  while (n>1) {
    if (n&1)
      r *= y;
    n = (int)(n/2);
    y *= y;
  }
  r *= y
  return r;
}

int eul_pwr(int b, uint e)
{
  int i, r=1; 
  for (i=0; i<e; ++i)
    r *= b;
  return r;
}

int eul_modular(int b, uint e, uint m)
{
  int i, r=1, p=b%m,
      z=sizeof(int)*8;

  for (i=0; i<z; ++i) {
    int lbit = 0x00000001&(e>>i);
    if (lbit)
      r = (r*p)%m;
  }
  return r;
}

void eul_bin(int n)
{
  int u=7, i;
  if (n > 255)
    u = 31;
  for (i=u; i>=0; --i) {
    if ((n>>i)&1)
      putchar('1');
    else
      putchar('0');
  }
  putchar('\n');
}

#endif /* EULER_H */
