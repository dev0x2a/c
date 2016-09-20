#include <stdio.h>

/*  count chars in input; 1st version */

int main() {
  long nc = 0;

  while (getchar() != EOF)
    ++nc;
  printf("%ld\n",nc);
}

