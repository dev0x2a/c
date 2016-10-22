#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * original s.keleti
 * modified by ryan keleti on 10.01.2016
 */

int
main (int argc, char *argv[])
{
  //int offset[8] = {1,7,11,13,17,19,23,29};
  int s[6] = {0,1,2,3,5,-1};
  int del[8] = {6,4,2,4,2,4,6,2};
  long int N=0;
  long int div, max;
  int prime=1;
  int i,inc; 

  if (argc!=2) {
    printf("%s <num> to check if prime\n", argv[0]);
    return(-1);
  }

  N=atol(argv[1]);
  if (N==s[0]||N==s[1]||N==s[5]) {
    printf("%ld not prime\n", N);
    return(0);
  }

  if (N==s[2]||N==s[3]||N==s[4]) {
    printf("%ld is prime\n", N);
    return(0);
  }

  inc=0;
  while (!(N&0x01)) {
    if (prime) 
      printf("not prime %ld = 2", N);
    ++inc;
    N>>=1;
    prime=0;
  }

  if (inc>1) 
    printf("^%d", inc);

  inc=0;
  while (!(N%3)) {
    if (prime) 
      printf("not prime %ld = 3", N);
    else if (inc==0) 
      printf("*3");
    ++inc;
    N/=3;
    prime=0;
  }

  if (inc>1) 
    printf("^%d", inc);

  inc=0;
  while (!(N%5)) {
    if (prime) 
      printf("not prime %ld = 5", N);
    else if (inc==0) 
      printf("*5");
    ++inc;
    N/=5;
    prime=0;
  }

  if (inc>1) 
    printf("^%d", inc);
  if (N<=31) {
    if (prime) 
      printf("%ld is prime\n", N);
    else { 
      if (N!=1) 
        printf("*%ld\n", N);
      else 
        printf("\n");
    }
    return(0);
  }

  max=sqrt(N);
  for (div=7, i=1; div<=max; ) {
    inc=0;
    while (!(N%div)) {
      if (prime)
        printf("%ld not prime %ld = %ld", N,N,div);
      else if (inc==0) 
        printf("*%ld", div);
      ++inc;
      N/=div;
      max=sqrt(N);
      prime=0;
    }
    if (inc>1) 
      printf("^%d", inc);
    if (N==1) {
      printf("\n");
      return(0);
    }
    div+=del[++i];
    if (i>=8) 
      i=0;
  }

  if (prime) 
    printf("%ld is prime\n", N);
  else { 
    if (N!=1) 
      printf("*%ld\n", N);
    else 
      printf("\n");
  }
  return(0);
}

