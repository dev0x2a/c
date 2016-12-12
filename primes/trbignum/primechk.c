/* copyright (c) 2016 Stevenand Ryan Keleti */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>

struct bignum_st {
  unsigned size;
  unsigned char sign;
  unsigned char tab[BUFSIZ];
  uintmax_t nn; /* temporary... */
  size_t *ptr;
};
struct bignum_st in;
FILE *out;
#define USEPUTCHAR 1

int main(int argc, char *argv[])
{ 
  if (argc < 2) {
    fprintf(stderr, "%s <num> to check if prime\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  out = stdout;
  /*int offset[8]={1,7,11,13,17,19,23,29};*/
  int del[8] = {6,4,2,4,2,4,6,2};
  unsigned i=1, prime=1, inc=0;
  uintmax_t div, max;
  in.sign = 0;
  in.nn = strtoll(argv[1], (char**)NULL, 10);
#define nn in.nn
/* this doesn't actually do anthing because truncation... *//*
  if (nn > UINTMAX_MAX) {
    fprintf(stderr, "%s: input exceeds uintmax_t type\n", argv[0]);
    exit(EXIT_FAILURE);
  }*/
  if ((signed)nn<1) {
    fprintf(stderr, "%s: err: input < 1\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (nn == 1) {
    fprintf(out, "1 not prime\n");
    exit(EXIT_SUCCESS);
  }
  if (nn==2 || nn==3 || nn==5) {
    fprintf(out, "2, 3, 5 are prime..\n");
    exit(EXIT_SUCCESS);
  }

  while (!(nn & 1)) {
    if (prime)
      fprintf(out, "not prime %ld = 2", nn);
    ++inc;
    nn >>= 1;
    prime = 0;
  }
  if (inc > 1)
    fprintf(out, "^%d", inc);
  inc = 0;
  while (!(nn % 3)) {
    if (prime)
      fprintf(out, "not prime %ld = 3", nn);
    else if (inc == 0)
      fprintf(out, "*3");
    ++inc;
    nn /= 3;
    prime = 0;
  }
  if (inc > 1)
    fprintf(out, "^%d", inc);
  inc = 0;
  while (!(nn % 5)) {
    if (prime)
      fprintf(out, "not prime %ld = 5", nn);
    else if (inc == 0)
      fprintf(out, "*5");
    ++inc;
    nn /= 5;
    prime = 0;
  }
  if (inc > 1)
    fprintf(out, "^%d", inc);
  if (nn <= 31) {
    if (prime)
      fprintf(out, "%ld is prime\n", nn);
    else { 
      if (nn != 1)
        fprintf(out, "*%ld\n", nn);
      else {
#if USEPUTCHAR
        putchar('\n');
#else
        fprintf(out, "\n");
#endif
      }
    }
    exit(EXIT_SUCCESS);
  }

  max = (uintmax_t)sqrt(nn);
  for (div=7,i=1; div<=max; ) {
    inc = 0;
    while (!(nn % div)) {
      if (prime)
        fprintf(out, "not prime %ld = %ld", nn,div);
      else if (inc == 0)
        fprintf(out, "*%ld", div);
      ++inc;
      nn /= div;
      max = (uintmax_t)sqrt(nn);
      prime = 0;
    }
    if (inc > 1)
      fprintf(out, "^%d", inc);
    if (nn == 1) {
#if USEPUTCHAR
      putchar('\n');
#else
      fprintf(out, "\n");
#endif
      exit(EXIT_SUCCESS);
    }
    div += del[++i];
    if (i >= 8)
      i = 0;
  }
  if (prime)
    fprintf(out, "%ld is prime\n", nn);
  else { 
    if (nn != 1)
      fprintf(out, "*%ld\n", nn);
    else {
#if USEPUTCHAR
      putchar('\n');
#else
      fprintf(out, "\n");
#endif
    }
  }
  exit(EXIT_SUCCESS);
}

