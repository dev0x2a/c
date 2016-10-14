#ifndef EULER_H
#define EULER_H
/*
 * euler.h
 * ryan keleti (c) 2016
 *
 * a header file for project euler,
 * primarily to save useful functions
 *
 * prefix all functions or non-local variables with eul_
 */

int
eul_pwr(int b, unsigned int e)
{
  int r = 1; 
  for (int i=0; i<e; ++i) r *= b;
  return r;
}

long long
eul_power(long long n, long long e)
{
  long long r = 1;
  while (e > 0) {
    if ((e&1)!=0) r *= n;
    n *= n;
    e >>= 1;
  }
  return r;
}

int
eul_modular(int b, unsigned int e, unsigned int m)
{
  int i;
  int r = 1;
  int p = b%m;
  for (i=0; i<sizeof(int)*8; ++i) {
    int lbit = 0x00000001&(e>>i);
    if (lbit) r = (r*p)%m;
  }
  return r;
}

int
eul_gcd(int a, int b)
{
  while (a != b) {
    if (a > b) a -= b;
    else b -= a;
  }
  return a;
}

int
eul_lcm(int x, int y)
{
  return (x/gcd(x,y)*y);
}

int
eul_isprime(int n)
{
  if (n<2) return 0;
  if (n==2) return 1;
  if (n%2==0) return 0;
  for (int i=3; i<=sqrt(n); i+=2) 
    if (n%i==0)
      return 0;
  return 1;
}

/*  eul_is_prime: slightly different than eul_isprime */
int
eul_is_prime(int n)
{
  if (n==1) return 0;
  if (n==2) return 1;
  for (int i=2; i*i<=n; ++i) 
    if (n%i == 0) return 0;
  return 1;
}

int
eul_cprimes(int n)
{
  int c = 0;
  for (int i=2; i<n; ++i) 
    if (isprime(i)) ++c;
  return c;
}

int
eul_primefac(unsigned long int n)
{
  while (n%2==0) {
    printf("%2d\t", 2);
    n /= 2;
  }
  for (int i=3; i<=sqrt(n); i+=2) {
    while (n%i==0) {
      printf("%2d ", i);
      n /= i;
    }
  }
  if (n>2) printf("%2ld\t", n);
  return 0;
}

int
eul_sieve(int min, int max)
{
  int i,j,k;
  int set = ++max;
  int *nums = malloc(sizeof(int)*set);

  for (i=0; i<set; ++i) nums[i] = i + 1;
  for (j=2; j<set; ++j) 
    if (nums[j] != 0) 
      for (k=2*j; k<set; k+=j) 
        nums[k] = 0;
  for (i=min; i<set; ++i)
    if (nums[i] != 0) printf("%2d ", i);
  free(nums);
  return 0;
}
#endif

