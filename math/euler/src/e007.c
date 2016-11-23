#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sieve(int min, int max);

int main(void) 
{
  long n=1000000;
  sieve(1, n);
  return(0);
}

int sieve(int min, int max)
{
  int i, p, m, c=0, s=max+1;
  int *a=malloc(sizeof(int)*s);
  
  for (i=0; i<s; ++i)
    a[i]=i+1;
  for (p=2; p<s; ++p) {
    if (a[p]!=0) {
      for (m=2*p; m<set; m+=p)
        a[m]=0;
    }
  }
  for (i=min; i<set; ++i) {
    if (a[i]!=0) {
      if (c<10002) {
        ++c;
        printf("%d:\t", c);
        printf("%d\t\t", i);
      }
    }
  }
  printf("\nnum primes = %d\n", c);
  free(a);
  return(0);
}
