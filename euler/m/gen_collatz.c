/*
 * collatz.c
 *  counts steps in collatz seq
 *  for an interval [1,num]
 *  and gives the average
 * (c) copyright 2016 Ryan Keleti
 */
#include <stdio.h>
#include <stdlib.h>

int gen(int N);

int 
main(int argc, char *argv[]) 
{
  if (argc!=2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  unsigned long long N;
  double s;
  int i;

  N = atoi(argv[1]);
  if ((signed)N<1) {
    printf("%s: input < 1\n", argv[0]);
    return(-1);
  }
  printf("\n");
  s=0;
  for (i=1; i<=N; ++i) {
    s += gen(i);
  }
  s /= i;
  printf("avg = %f\n", s);
  //printf("1");
  return(0);
}

int
gen(int N)
{
  int k;
  int c=0;
  int tmp=N;
  while (N!=1) {
    if (N&1) {
      N=(((N<<1)+N)+1)>>1;
      c+=2;
    } else {
      N>>=1;
      ++c;
    }
  }
  for (int i=31; i>=0; --i) {
    k=c>>i;
    if (k&1)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
  //printf("for %3d, count = %3d\n", tmp,c);
  return(c);
}

