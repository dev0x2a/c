#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{ 
  if (argc != 2) {
    fprintf(stderr, "%s <num> to check if prime\n", argv[0]);
    return(-1);
  }
  /*int offset[8]={1,7,11,13,17,19,23,29};*/
  int del[8] = {6,4,2,4,2,4,6,2};
  int prime = 1,inc = 0;
  unsigned long long N = atoi(argv[1]);
  
  if ((signed)N < 1) {
    N==0 ? puts("0 is not prime") : puts("unsigned values only");
    return(-1);
  }
  if (N==1 || N==2 ) {
    N==1 ? puts("1 is not prime") : puts("2 is prime");
    return(0);
  }
  if (N==3 || N==5) {
    N==3 ? puts("3 is prime") : puts("5 is prime");
    return(0);
  }
  while (!(N&1)) {
    if (prime)
      printf("not prime %ld = 2", N);
    ++inc;
    N >>= 1;
    prime = 0;
  }
  if(inc > 1)
    printf("^%d", inc);
  inc = 0;
  while (!(N%3)) {
    if (prime)
      printf("not prime %ld = 3", N);
    else if (inc == 0)
      printf("*3");
    ++inc;
    N /= 3;
    prime = 0;
  }
  if (inc>1)
    printf("^%d", inc);
  inc = 0;
  while (!(N%5)) {
    if (prime)
      printf("not prime %ld = 5", N);
    else if (inc==0)
      printf("*5");
    ++inc;
    N /= 5;
    prime = 0;
  }
  if (inc>1)
    printf("^%d", inc);
  if (N <= 31) {
    if (prime)
      printf("%ld is prime\n", N);
    else { 
      if (N != 1)
        printf("*%ld\n", N);
      else
        putchar('\n');
    }
    return(0);
  }
  long int div, max;
  int i;
  max = (unsigned long long)sqrt(N);
  for (div=7,i=1; div<=max; ) {
    inc = 0;
    while (!(N%div)) {
      if (prime)
        printf("not prime %ld = %ld", N,div);
      else if (inc == 0)
        printf("*%ld", div);
      ++inc;
      N /= div;
      max = sqrt(N);
      prime = 0;
    }
    if (inc > 1)
      printf("^%d", inc);
    if (N == 1) {
      putchar('\n');
      return(0);
    }
    div += del[++i];
    if (i >= 8)
      i=0;
  }
  if (prime)
    printf("%ld is prime\n", N);
  else { 
    if (N != 1)
      printf("*%ld\n", N);
    else 
      putchar('\n');
  }
  return(0);
}

