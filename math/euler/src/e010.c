#include <stdio.h>
#include <math.h>

#define MAX 2000000
int isprime(int n);

int main(void)
{
  int i;
  unsigned long long r, s=0;

  for (i=1; i<MAX; ++i) {
    r=isprime(i);
    if (r==1)
      s+=i;
  }
  printf("%llu ", s);
  return(0);
}

int isprime(int n)
{
  int i;
  if (n<=1)
    return(0);
  if (n==2 || n==3)
    return(1);
  for (i=3; i*i<=n; i+=2) {
    if (n%i==0)
      return(0);
  }
  return(1);
}

