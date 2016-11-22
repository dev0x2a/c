#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("%s <num> (summation, mod 3,5 in [1..num-1])\n", argv[0]);
    return(-1);
  }
  int i, n, s;
  n = atoi(argv[1]);
  s = 0;

  printf("\nfind multiples of 3 & 5 in range [1,%d], w/ summation\n",n-1);
  for (i=1; i<n; ++i) {
    if (i%3==0 || i%5==0) {
      printf("%d ",i);
      s += i;         
    }
  }
  printf("sum = %d\n",s);
  return(0);
}

