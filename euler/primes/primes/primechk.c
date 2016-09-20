#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[])
{
  int offset[8] = {1,7,11,13,17,19,23,29};
  int del[8] = {6,4,2,4,2,4,6,2};
  long int num = 0;
  long int div, max;
  int prime = 1, i, inc; 

  if (argc != 2) {
    printf("%s <num> to check if prime\n", argv[0]);
    return (-1);
  }
  num = atol(argv[1]);
  inc = 0;
  while (!(num&0x01)) {
    if (prime) printf("not prime %ld = 2",num);
    inc++;
    num >>= 1;
    prime = 0;
  }
  if (inc>1) printf("^%d", inc);
  inc = 0;
  while (!(num%3)) {
    if (prime) printf("not prime %ld = 3",num);
    else if (inc==0) printf("*3");
    inc++;
    num /= 3;
    prime = 0;
  }
  if (inc>1) printf("^%d", inc);
  inc = 0;
  while (!(num%5)) {
    if (prime) printf("not prime %ld = 5",num);
    else if (inc==0) printf("*5");
    inc++;
    num /= 5;
    prime = 0;
  }
  if (inc>1) printf("^%d", inc);
  if (num <= 31) {
    if (prime) printf("%ld is prime\n",num);
    else { 
      if (num!=1) printf("*%ld\n",num);
      else printf("\n");
    }
    return(0);
  }

  max = sqrt(num);
  for (div=7, i=1; div<=max;) {
    inc = 0;
    while (!(num%div)) {
      if (prime) printf("not prime %ld = %ld",num,div);
      else if (inc==0) printf("*%ld",div);
      inc++;
      num /= div;
      max = sqrt(num);
      prime = 0;
    }
    if (inc>1) printf("^%d", inc);
    if (num==1) {
      printf("\n");
      return(0);
    }
    div += del[i++];
    if (i>=8) i=0;
  }

  if (prime) printf("%ld is prime\n",num);
  else { 
    if (num!=1) printf("*%ld\n",num);
    else printf("\n");
  }

  return 0;
}
