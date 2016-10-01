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
  long int num = 0;
  long int div, max;
  int prime = 1;
  int i, inc; 

  num = atol(argv[1]);

  if (argc != 2) {
    fprintf(stderr, "%s <num> to check if prime\n", argv[0]);
    return(-1);
  }

  if (num == s[0] || num == s[1] || num == s[5]) {
    fprintf(stdout, "%ld not prime\n", num);
    return(0);
  }

  if (num == s[2] || num == s[3] || num == s[4]) {
    fprintf(stdout, "%ld is prime\n", num);
    return(0);
  }

  inc = 0;
  while (!(num&0x01)) {
    if (prime) 
      fprintf(stdout, "not prime %ld = 2", num);
    ++inc;
    num >>= 1;
    prime = 0;
  }

  if (inc > 1) 
    fprintf(stdout, "^%d", inc);

  inc = 0;
  while (!(num%3)) {
    if (prime) 
      fprintf(stdout, "not prime %ld = 3", num);
    else if (inc == 0) 
      fprintf(stdout, "*3");
    ++inc;
    num /= 3;
    prime = 0;
  }

  if (inc > 1) 
    fprintf(stdout, "^%d", inc);

  inc = 0;
  while (!(num%5)) {
    if (prime) 
      fprintf(stdout, "not prime %ld = 5", num);
    else if (inc == 0) 
      fprintf(stdout, "*5");
    ++inc;
    num /= 5;
    prime = 0;
  }

  if (inc > 1) 
    fprintf(stdout, "^%d", inc);
  if (num <= 31) {
    if (prime) 
      fprintf(stdout, "%ld is prime\n", num);
    else { 
      if (num != 1) 
        fprintf(stdout, "*%ld\n", num);
      else 
        fprintf(stdout, "\n");
    }
    return(0);
  }

  max = sqrt(num);
  for (div=7, i=1; div<=max; ) {
    inc = 0;
    while (!(num%div)) {
      if (prime)
        fprintf(stdout, "%ld not prime %ld = %ld", num, num, div);
      else if (inc == 0) 
        fprintf(stdout, "*%ld", div);
      ++inc;
      num /= div;
      max = sqrt(num);
      prime = 0;
    }
    if (inc > 1) 
      fprintf(stdout, "^%d", inc);
    if (num == 1) {
      fprintf(stdout, "\n");
      return(0);
    }
    div += del[++i];
    if (i >= 8) 
      i = 0;
  }

  if (prime) 
    fprintf(stdout, "%ld is prime\n", num);
  else { 
    if (num != 1) 
      fprintf(stdout, "*%ld\n", num);
    else 
      fprintf(stdout, "\n");
  }
  return(0);
}

