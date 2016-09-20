#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int sieve(int min, int max);

int main() 
{
  int long n = 1000000;
  sieve(1, n);
  return 0;
}


int sieve(int min, int max)
{
  int count = 0;
  int set = max + 1;
  int* ints = malloc(sizeof(int) * set);

  for (int i = 0; i < set; i++) ints[i] = i + 1;
  for (int p = 2; p < set; p++) {
    if (ints[p] != 0) {
      for (int m = 2 * p; m < set; m += p) ints[m] = 0;
    }
  }
  for (int i = min; i < set; ++i) {
    if (ints[i] != 0) {
      if (count < 10002) {
        ++count;
        printf("%d:\t",count);
        printf("%d\t\t", i);
      }
    }
  }
  printf("\n\nnumber of primes:\t%d\n", count);
  return 0;
}

