#include <stdio.h>
#include <stdlib.h>

char *
bin(int);

int
main(int argc, char *argv[])
{
  int num, k;
  char *p;

  if (argc != 2) {
    fprintf(stderr, "%s <num> to convert base10 to base2\n", argv[0]);
    return(-1);
  }
  num = atol(argv[1]);
  p = bin(num);

  printf("%s", p);
  printf("\n");
  free(p);
  return 0;
}

char *
bin(int num)
{
  int k, count;
  char *p;

  count = 0;
  p = (char*)malloc(32+1);

  if (p == NULL)
    exit(EXIT_FAILURE);

  for (int i=31; i>=0; --i) {
    k = num >> i;
    if (k&1)
      *(p+count) = 1 + '0';
    else
      *(p+count) = 0 + '0';
    ++count;
  }
  *(p+count) = '\0';
  return p;
}

