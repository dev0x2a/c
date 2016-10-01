#include <stdio.h>
#include <math.h>

#define MAX 2000000

int is_prime(int n);

int
main(void)
{
  int i;
  unsigned long long r, sum;
  sum = 0;

  for (i=1; i<MAX; ++i) {
    r = is_prime(i);
    if (r == 1) 
      sum += i;
  }
  printf("%llu ", sum);
  return 0;
}

int is_prime(int n)
{
  int i;
  if (n == 1) 
    return 0;
  if (n == 2) 
    return 1;
  for (i=2; i*i<=n; ++i) {
    if (n%i == 0) 
      return 0;
  }
  return 1;
}

