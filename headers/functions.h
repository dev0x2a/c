#if 0
/*
 * functions.h
 * c header for some useful functions
 *
 * yes, the variable names are meaningless. this is a personal header.
 */
#endif

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#endif

#define AUTHORS \
  ("Ryan Keleti")

int power(int b, unsigned int e)
{
  int i, r = 1; 
  for (i = 0; i < e; i++) r *= b;
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
  return (x / gcd(x,y) * y);
}

unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}

int isprime(int n)
{
  if (n < 2) return 0;
  if (n == 2) return 1;
  if (n % 2 == 0) return 0;
  for (int i = 3; i <= sqrt(n); i += 2) if (n % i == 0) return 0;
  return 1;
}

int is_prime(int n)
{
  int i;
  if (n == 1) return 0;
  if (n == 2) return 1;
  for (i = 2; i*i<=n; i++) {
    if (n%i == 0) return 0;
  }
  return 1;
}

int countprimes(int n)
{
  int c = 0;
  for (int i = 2; i < n; i++) if (isprime(i)) c++;
  return c;
}

int primefac(unsigned long int n)
{
  while (n % 2 == 0) {
    printf("%d\t", 2);
    n /= 2;
  }
  for (int i = 3; i <= sqrt(n); i += 2) {
    while (n % i == 0) {
      printf("%d\t", i);
      n /= i;
    }
  }
  if (n > 2) printf("%ld\t", n);
  return 0;
}

int sieve(int min, int max, int z)
{
  int i, p, m, v, c = 0;
  int set = max + 1;
  int* ints = malloc(sizeof(int) * set);
  unsigned long int sum = 0;

  for (i = 0; i < set; i++) ints[i] = i + 1;
  for (p = 2; p < set; p++) 
    if (ints[p] != 0) 
      for (m = 2*p; m < set; m += p) ints[m] = 0;
    
  if (z == 0) v = 1;
  else if (z > 0) v = 2;
  else if (z < 0) v = 3;

  switch(v) {
    case 1: for (i = min; i < set; ++i)
              if (ints[i] != 0) printf("%d\t\t", i);
            break;
    case 2: for (i = min; i < set; ++i)
              if (ints[i] != 0) if (c < z) {++c; printf("primes:\t%d\n",c);}
            break;
    case 3: for (i = min; i < set; ++i)
              if (ints[i] != 0) sum += i;
            printf("%ld ", sum);
            break;
    default: return (-1);
  }
  return 0;
}

int collatz(int long n)
{
  while (n != 1) {
    printf("%ld ",n);
    if  (n&0x01) n = 3*n + 1;
    else n /= 2;
  }
  printf("1\n");
  return 0;
}

