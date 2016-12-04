#ifndef MPRIMES_H
#define MPRIMES_H
/*
 * mprimes.h
 * c header for some useful primes functions
 * ryan keleti (c) 2016
 *
 * yes, the variable names are meaningless. this is a personal header.
 */

int pwr(int b, unsigned int e)
{
  int i, r = 1; 
  for (i=0; i<e; ++i) r *= b;
  return r;
}

int gcd(int a, int b)
{
  while (a != b) {
    if (a > b) a -= b;
    else b -= a;
  }
  return a;
}

int lcm(int x, int y)
{
  return (x/gcd(x,y)*y);
}

int isprime(int n)
{
  if (n < 2) return 0;
  if (n == 2) return 1;
  if (n%2 == 0) return 0;
  for (int i=3; i<=sqrt(n); i+=2) if (n%i == 0) return 0;
  return 1;
}

/*  is_prime: slightly different than isprime */
int is_prime(int n)
{
  if (n == 1) return 0;
  if (n == 2) return 1;
  for (int i=2; i*i<=n; ++i) if (n%i == 0) return 0;
  return 1;
}

int cprimes(int n)
{
  int c = 0;
  for (int i=2; i<n; ++i) if (isprime(i)) ++c;
  return c;
}

int primefac(unsigned long int n)
{
  while (n%2 == 0) {
    printf("%2d\t", 2);
    n /= 2;
  }
  for (int i=3; i<=sqrt(n); i+=2) {
    while (n%i == 0) {
      printf("%2d ", i);
      n /= i;
    }
  }
  if (n > 2) printf("%2ld\t", n);
  return 0;
}

int sieve(int min, int max)
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

