#include <stdio.h>
#include <stdlib.h>
int
fact(int a)
{
  if (a==0)
    return(1);
  return(a*fact(a-1));
}
int
main(int argc, char *argv[])
{
  if (argc!=2)
    return(-1);
  int N;
  N=atoi(argv[1]);
  printf("%d\n", fact(N));
  return(0);
}

