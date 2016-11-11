#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
  if (argc != 3) {
    printf("%s sum Σ <num> <lim>\n",argv[0]);
    exit(-1);
  }

  int i, n, lim;
  long int s;
  
  n=atoi(argv[1]);
  lim=atoi(argv[2]);
  s=0;
  
  for (i=n; i<=lim; ++i) {
    s+=i;
  }

  printf(" %d\n", lim); 
  printf(" Σi = %ld\n", s);
  printf("i=%d\n", n);
  exit(0);
}

