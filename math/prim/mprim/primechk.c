#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "typedef.h"

#define PGRM "Prime Check"

int main(int argc, char *argv[])
{ 
  if (argc != 2) {
    fprintf(stderr, "%s <num> to check if prime\n", argv[0]);
    exit(-1);
  }
  /*int offset[8]={1,7,11,13,17,19,23,29};*/
  int del[8] = {6,4,2,4,2,4,6,2};
  int i, prime = 1, inc = 0;
  long int div, max;
  u64 N = atoi(argv[1]);
  
  if ((signed)N<=1 || N==2) {
    N==2 ? puts("2 is prime") : puts("try n>1 (1 not prime)");
    exit(0);
  }
  if (N==3 || N==5) {
    N==3 ? puts("3 is prime") : puts("5 is prime");
    exit(0);
  }

  while (!(N&1)) {
    if (prime)
      printf("not prime %ld = 2", N);
    ++inc;
    N >>= 1;
    prime = 0;
  }
  if (inc > 1)
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
  if (inc > 1)
    printf("^%d", inc);
  inc = 0;
  while (!(N%5)) {
    if (prime)
      printf("not prime %ld = 5", N);
    else if (inc == 0)
      printf("*5");
    ++inc;
    N /= 5;
    prime = 0;
  }
  if (inc > 1)
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
    exit(0);
  }

  max = (u64)sqrt(N);
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
      exit(0);
    }
    div += del[++i];
    if (i >= 8)
      i = 0;
  }
  if (prime)
    printf("%ld is prime\n", N);
  else { 
    if (N != 1)
      printf("*%ld\n", N);
    else 
      putchar('\n');
  }
  exit(0);
}

