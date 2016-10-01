#include <stdio.h>
#include <stdlib.h>

int num_t(int n)
{
  int result = (n*(n + 1))/2;
  return result;
}

int
main(int argc, char *argv[])
{ 
  int long num;
  int count;

  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }

  num = atol(argv[1]);
  count = -1;

  for (int i=0; i<=num; ++i) {
    num_t(i);
    ++count;
    printf("%d\t%d\n", num_t(i), count);
  }
  return 0;
}

