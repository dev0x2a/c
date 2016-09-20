/*
 * functions.h
 * c header for some useful functions
 *
 * -- ryan keleti
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#endif

int power(int base, unsigned int exp)
{
  int i, res = 1; 
  for (i = 0; i < exp; i++) res *= base;
  return res;
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

int println(void)
{
  printf("\n");
  return 0;
}

int isprime(int n)
{
  if (n < 2) return 0;
  if (n == 2) return 1;
  if (n % 2 == 0) return 0;
  for (int i = 3; i <= sqrt(n); i += 2) if (n % i == 0) return 0;
  return 1;
}

int countprimes(int max)
{
  int count = 0;
  for (int i = 2; i < max; i++) if (isprime(i)) count++;
  return count;
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

int sieve(int min, int max, int counter)
{
  int func, count = 0;
  int set = max + 1;
  int* ints = malloc(sizeof(int) * set);

  for (int i = 0; i < set; i++) ints[i] = i + 1;
  for (int p = 2; p < set; p++) {
    if (ints[p] != 0) {
      for (int m = 2 * p; m < set; m += p) ints[m] = 0;
    }
  }
  if (counter == 0) func = 1;
  else if (counter > 0) func = 2;

  switch(func)
  {
    case 1: for (int i = min; i < set; ++i) {
              if (ints[i] != 0) printf("%d\t\t", i);
            }
            break;
    case 2: for (int i = min; i < set; ++i) {
              if (ints[i] != 0) {
                if (count < counter) {
                  ++count;
                  printf("%d:\t",count);
                  printf("%d\t\t", i);
                  printf("\nprimes:\t%d\n", count);
                }
              }
            }
            break;
    default: return (-1);
  }
  return 0;
}

int collatz(int long num)
{
  while (num != 1) {
    printf("%ld ",num);
    if  (num&0x01) num = 3 * num + 1;
    else num /= 2;
  }
  printf("1\n");
  return 0;
}

