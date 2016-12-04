#include <stdio.h>

int main(void)
{
  int i;
  for (i=1; i*i<=100; ++i)
    printf("door %d open\n", i*i);
  return 0;
}

