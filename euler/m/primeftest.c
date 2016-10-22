#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main (int argc, char *argv[])
{
  int offset[8] = {1,7,11,13,17,19,23,29};
  int del[8] = {6,4,2,4,2,4,6,2};
  int primen[20] = {2,3,5,7,11, 13,17,19,23,29, 31,37,41,43,47, 53,59,61,67,71}; 
  unsigned long int pprime=1;
  unsigned long int num=0;
  unsigned long int div,max;
  int prime,i,j,inc; 

  pprime=210;
  for (j=4; j<16; ++j) {
    pprime*=primen[j];
    num=pprime-primen[j+1]*primen[j+2];
    prime=1;
    inc=0;
    while (!(num&0x01)) {
      if (prime) printf("not prime %lu = 2",num);
      ++inc;
      num>>=1;
      prime=0;
    }
    if (inc>1) printf("^%d", inc);
    inc=0;
    while (!(num%3)) {
      if (prime) printf("not prime %lu = 3",num);
      else if (inc==0) printf("*3");
      ++inc;
      num/=3;
      prime=0;
    }
    if (inc>1) printf("^%d", inc);
    inc=0;
    while (!(num%5)) {
      if (prime) printf("not prime %lu = 5",num);
      else if (inc==0) printf("*5");
      ++inc;
      num/=5;
      prime=0;
    }
    if (inc>1) printf("^%d", inc);
    if (num<=31) {
      if (prime) printf("%lu is prime\n",num);
      else { 
        if (num!=1) printf("*%lu\n",num);
        else printf("\n");
      }
      continue;
    }
    max=sqrt(num);
    for (div=7, i=1; div<=max;) {
      inc=0;
      while (!(num%div)) {
        if (prime) printf("not prime %lu = %lu",num,div);
        else if (inc==0) printf("*%lu",div);
        ++inc;
        num/=div;
        max=sqrt(num);
        prime=0;
      }
      if (inc>1) printf("^%d", inc);
      if (num==1) {
        printf("\n");
        return(0);
      }
      div+=del[++i];
      if (i>=8) i=0;
    }
    if (prime) printf("%lu is prime\n",num);
    else {
      if (num!=1) printf("*%lu\n",num);
      else printf("\n");
    }
  }
  return(0);
}

