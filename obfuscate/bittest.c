#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  int N;
  N = atoi(argv[1]);

  printf("%d\n", (N<<1)+N);

  return(0);
}

