#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  int num, k;

  if (argc != 2) {
    fprintf(stderr, "%s <num> to convert base10 to base2\n", argv[0]);
    return(-1);
  }
  num = atol(argv[1]);

  for (int i=31; i>=0; --i) {
    k = num >> i;
    if (k&1)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
  return 0;
}

