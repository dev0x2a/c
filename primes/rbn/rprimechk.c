/* copyright (c) 2016 Steven and Ryan Keleti */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include "rbn.c"

#define COMN \
  fprintf(stderr, "please try bigger primes..\n"\
                  "just in case:\n"\
                  "\t1 is _not_ prime\n"\
                  "\t2,3,5,7,11, etc.. _are_ prime.."\
                  "\tprogram doesn't check for them..\n")
/*struct bignum_st {
  unsigned size;
  unsigned char sign;
  unsigned char tab[BUFSIZ];
  uintmax_t nn; / * temporary... * /
  size_t *ptr;
};struct bignum_st in; */

int main(int argc, char *argv[])
{
  COMN;
  return 0;
#if !1 
  if (argc < 2) {
    fprintf(stderr, "%s <num> to check if prime\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  FILE *out;
  /*int offset[8]={1,7,11,13,17,19,23,29};*/
  int del[8] = {6,4,2,4,2,4,6,2};
  unsigned j ,i=1, prime=1, inc=0;
  rnd div, max;
  out = stdout;
  rni nn;
  nn.s = 0;
  //nn.dp[] = strtoll(argv[1], (char**)NULL, 10);
  for (j=0; j; --j) {
    nn.dp[j] = argv[1][j];
  }
//#define nn nn.dp[]
/* this doesn't actually do anthing because truncation... *//*
  if (nn > UINTMAX_MAX) {
    fprintf(stderr, "%s: input exceeds uintmax_t type\n", argv[0]);
    exit(EXIT_FAILURE);}*/
  if (nn.s == RNEG) {
    fprintf(stderr, "%s: err: input < 0\n", argv[0]);
    COMN;
    exit(EXIT_FAILURE);
  }
  while (!(isodd(&nn))) {
    if (prime) {
      fprintf(out, "not prime ");
      rn_printf(nn, 10, out);
      fprintf(out, " = 2");
    }
    ++inc;
    /*nn >>= 1;*/
    //FIXME XXX XXX XXX TODO
    rn_lsbd(&nn, 1);
    prime = 0;
  }
  if (inc > 1)
    fprintf(out, "^%d", inc);
  inc = 0;
  while (!(rn_modd(&nn, 3))) {
    if (prime) {
      fprintf(out, "not prime ");
      rn_printf(nn, 10, out);
      fprintf(out, " = 3");
    } else if (inc == 0)
      fprintf(out, "*3");
    ++inc;
    /*nn /= 3;*/
    //FIXME FIXME TODO XXX
    rn_divd(&nn, 3, &nn);
    prime = 0;
  }
  if (inc > 1)
    fprintf(out, "^%d", inc);
  inc = 0;
  while (!(rn_modd(&nn, 5))) {
    if (prime) {
      fprintf(out, "not prime ");
      rn_printf(nn, 10, out);
      fprintf(out, " = 5");
    } else if (inc == 0)
      fprintf(out, "*5");
    ++inc;
    /*nn /= 5;*/
    //FIXME
    rn_divd(&nn, 5, &nn);
    prime = 0;
  }
  if (inc > 1)
    fprintf(out, "^%d", inc);
  //FIXME FIXME FIXME XXX XXX TODO
  if (rn_cmpd(&nn, 31)==0) { /*nn <= 31*/
    if (prime) {
      rn_printf(nn, 10, out);
      fprintf(out, " is prime\n");
    }
    else { 
      if (nn != 1) {
        fprintf(out, "*");
        rn_printf(nn, 10, out);
      } else {
        fprintf(out, "\n");
      }
    }
    exit(EXIT_SUCCESS);
  }
  max = (rnd)sqrt(nn);
  for (div=7,i=1; div<=max; ) {
    inc = 0;
    while (!(rn_modd(nn, div))) {
      if (prime) {
        fprintf(out, "not prime ");
        rn_printf(nn, 10, out);
        fprintf(out, " = %ld", div);
      } else if (inc == 0)
        fprintf(out, "*%ld", div);
      ++inc;
      /*nn /= div;*/
      //FIXME
      rn_divd(&nn, div, &nn);
      //FIXME
      max = (rnd)sqrt(nn);
      prime = 0;
    }
    if (inc > 1)
      fprintf(out, "^%d", inc);
    if (rn_cmpd(&nn, 1) == 1) { /*nn==1 FIXME*/
      fprintf(out, "\n");
      exit(EXIT_SUCCESS);
    }
    div += del[++i];
    if (i >= 8)
      i = 0;
  }
  if (prime) {
    rn_printf(nn, 10, out);
    fprintf(out, " is prime\n", nn);
  } else { 
    if (rn_cmpd(nn,1)==0) {/* nn != 1 FIXME*/
      fprintf(out, "*", nn);
      rn_printf(nn, 10, out);
    } else {
      fprintf(out, "\n");
    }
  }
  exit(EXIT_SUCCESS);
#endif
}

