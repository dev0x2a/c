#include <stdio.h>

int main ()
{
  enum {RED=5, YELLOW, GREEN=4, BLUE};

  printf("RED = %d\n", RED);
  printf("YELLOW = %d\n", YELLOW);
  printf("GREEN = %d\n", GREEN);
  printf("BLUE = %d\n", BLUE);
  return 0;
}

