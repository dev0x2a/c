#ifndef PRIM_H
#define PRIM_H

#include "prutil.h"
#include "typedef.h"

#define PRAND_MAX 2147483647

#ifndef min
#define min(a,b) ((a<b)?a:b)
#endif

#ifndef max
#define max(a,b) ((a>b)?a:b)
#endif

typedef struct decprime {
  int p;
  int e;
  int pe;
} decprime_t;



int pr_atoi(const char*);
int pr_rand(void);
void pr_srand(uint);
int pr_bin(int);
u64 pr_bpwr(u64, u64);
int pr_modular(int, uint, uint);
int pr_gcd(int, int);
int pr_lcm(int, int);
int pr_cprimes(int)
int pr_sieve(int, int)

u8 pr_bittab2[] = {
  1,2,4,8,16,32,64,128
};

int pr_pwr(int b, uint e)
{
  int i, r = 1; 
  for (i=0; i<e; ++i)
    r *= b;
  return(r);
}

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

int pr_sieve(int min, int max)
{
  int i, j, k;
  int set = ++max;
  int *nums = malloc(sizeof(int)*set);
  for (i=0; i<set; ++i)
    nums[i] = ++i;
  for (j=2; j<set; ++j) 
    if (nums[j] != 0) 
      for (k=2*j; k<set; k+=j)
        nums[k] = 0;
  for (i=min; i<set; ++i)
    if (nums[i] != 0)
      printf("%2d ", i);
  free(nums);
  return(0);
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

#endif /* PRIM_H */
