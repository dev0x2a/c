#ifndef PRIM_H
#define PRIM_H


#include "prutil.h"

#define PRAND_MAX 2147483647


int pr_atoi(const char*);
int pr_rand(void);
void pr_srand(unsigned int);


static unsigned long int anext = 1;


int pr_atoi(const char s[])
{
  int i, n;

  n = 0;
  for (i=0; s[i]>='0' && s[i]<='9'; ++i) {
    n = 10*n+(s[i]-'0');
  }
  return n;
}

int pr_rand(void)
{
  anext = anext*1103515245+12345;

  return((unsigned)(anext/65536)%32768);
}

void pr_srand(unsigned int seed)
{
  anext = seed;
}

unsigned char pr_bittab[] = {
  1,2,4,8,16,32,64,128
};

int pr_pwr(int b, unsigned int e)
{
  int i, r = 1; 
  for (i=0; i<e; ++i)
    r *= b;
  return(r);
}

unsigned long long pr_power(unsigned long long n, unsigned long long e)
{
  unsigned long long r = 1;
  while (e > 0) {
    if ((e&1) != 0)
      r *= n;
    n *= n;
    e >>= 1;
  }
  return(r);
}

int pr_modular(int b, unsigned int e, unsigned int m)
{
  int i, r = 1, p = b%m;
  for (i=0; i<sizeof(int)*8; ++i) {
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
      a-=b;
    else
      b -= a;
  }
  return(a);
}

int pr_lcm(int x, int y)
{
  return(x/gcd(x,y)*y);
}

int pr_isprime(int n)
{
  int i;
  if (n <= 1)
    return(0);
  if (n == 2)
    return(1);
  for (i=2; (i*i)<=n; ++i) 
    if (n%i == 0)
      return(0);
  return(1);
}

#ifdef MATH_H
int pr_is_prime(int n)
{
  int i;
  if (n < 2)
    return(0);
  if (n == 2)
    return(1);
  if (n%2 == 0)
    return(0);
  for (i=3; i<=sqrt(n); i+=2) 
    if (n%i == 0)
      return(0);
  return(1);
}
#endif

int pr_cprimes(int n)
{
  int i, c = 0;
  for (i=2; i<n; ++i) 
    if (isprime(i))
      ++c;
  return(c);
}

int pr_primefac(unsigned long int n)
{
  int i;
  while (n%2 == 0) {
    printf("%2d\t", 2);
    n /= 2;
  }
  for (i=3; i<=sqrt(n); i+=2) {
    while (n%i == 0) {
      printf("%2d ", i);
      n /= i;
    }
  }
  if (n>2) printf("%2ld\t",n);
  return(0);
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
  int k, u, i;
  if (n > 255)
    u = 31;
  else
    u = 7;
  for (i=u; i>=0; --i) {
    k = n>>i;
    if (k&1)
      putchar('1');
    else
      putchar('0');
  }
  putchar('\n');
  return(0);
}

#endif /* PRIM_H */

