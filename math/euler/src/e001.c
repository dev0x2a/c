#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("%s <n> (sum (mod 3,5) in [1..n-1])\n", argv[0]);
    return(-1);
  }
  unsigned long long i, n=atoi(argv[1]), s=0;

  printf("\nfind multiples of 3 & 5 in range [1,%d], w/ summation\n", n-1);
  for (i=1; i<n; ++i) {
    if (i%3==0 || i%5==0) {
      printf("%llu ",i);
      s += i;         
    }
  }
  printf("\n-> %llu\n", s);
  return(0);
}

