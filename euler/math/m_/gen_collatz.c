/*
 * collatz.c
 *  counts steps in collatz seq
 *  for a given num
 * (c) copyright 2016 Ryan Keleti
 */
#include <stdio.h>
#include <stdlib.h>

void gen(int N);

int 
main(int argc, char *argv[]) 
{
  if (argc!=2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  unsigned long long N;

  N = atoi(argv[1]);
  if ((signed)N<1) {
    printf("%s: input < 1\n", argv[0]);
    return(-1);
  }
  printf("\n");
  for (int i=1; i<=N; ++i) {
    gen(i);
  }
  //printf("1");
  return(0);
}

void
gen(int N)
{
  int c=0;
  int tmp=N;
  while (N!=1) {
    //printf("%llu ", N);
    
    if (N&1) {
      N=(((N<<1)+N)+1)>>1;
      c+=2;
    } else {
      N>>=1;
      ++c;
    }
  }
  printf("for %3d, count = %3d\n", tmp,c);
}
