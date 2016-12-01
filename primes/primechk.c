/* copyright (c) 2016 Stevenand Ryan Keleti */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

int main(int argc, char *argv[])
{ 
  if (argc < 2) {
    fprintf(stderr, "%s <num> to check if prime\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  /*int offset[8]={1,7,11,13,17,19,23,29};*/
  int del[8] = {6,4,2,4,2,4,6,2};
  int i, prime=1, inc=0;
  uintmax_t div, max;
  uintmax_t nn = atoi(argv[1]);

  if (nn > UINTMAX_MAX) {
    fprintf(stderr, "%s: input exceeds uintmax_t type\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((signed)nn<=1 || nn==2) {
    nn==2 ? puts("2 is prime") : puts("n<=1 not prime");
    exit(EXIT_SUCCESS);
  }
  if (nn==3 || nn==5) {
    nn==3 ? puts("3 is prime") : puts("5 is prime");
    exit(EXIT_SUCCESS);
  }

  while (!(nn & 1)) {
    if (prime)
      printf("not prime %ld = 2", nn);
    ++inc;
    nn >>= 1;
    prime = 0;
  }
  if (inc > 1)
    printf("^%d", inc);
  inc = 0;
  while (!(nn % 3)) {
    if (prime)
      printf("not prime %ld = 3", nn);
    else if (inc == 0)
      printf("*3");
    ++inc;
    nn /= 3;
    prime = 0;
  }
  if (inc > 1)
    printf("^%d", inc);
  inc = 0;
  while (!(nn % 5)) {
    if (prime)
      printf("not prime %ld = 5", nn);
    else if (inc == 0)
      printf("*5");
    ++inc;
    nn /= 5;
    prime = 0;
  }
  if (inc > 1)
    printf("^%d", inc);
  if (nn <= 31) {
    if (prime)
      printf("%ld is prime\n", nn);
    else { 
      if (nn != 1)
        printf("*%ld\n", nn);
      else
        putchar('\n');
    }
    exit(0);
  }

  max = (uintmax_t)sqrt(nn);
  for (div=7,i=1; div<=max; ) {
    inc = 0;
    while (!(nn % div)) {
      if (prime)
        printf("not prime %ld = %ld", nn,div);
      else if (inc == 0)
        printf("*%ld", div);
      ++inc;
      nn /= div;
      max = (uintmax_t)sqrt(nn);
      prime = 0;
    }
    if (inc > 1)
      printf("^%d", inc);
    if (nn == 1) {
      putchar('\n');
      exit(EXIT_SUCCESS);
    }
    div += del[++i];
    if (i >= 8)
      i = 0;
  }
  if (prime)
    printf("%ld is prime\n", nn);
  else { 
    if (nn != 1)
      printf("*%ld\n", nn);
    else 
      putchar('\n');
  }
  exit(EXIT_SUCCESS);
}

