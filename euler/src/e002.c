#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  long int i, j, f1 = 0, f2 = 1, up, sum, all;

  printf("range: ");
  scanf("%ld", &j);
  printf("\nfibonacci seq range [0,%ld], summation of evens and of all\n", j);

  for (i=0; i<j; ++i) {
    if (i <= 1) up = i;
    else {
      up = f1 + f2;
      f1 = f2;
      f2 = up;
    }
    printf("%2ld ", up);
    if (up%2 == 0)
      sum += up;
    all += up;
  }
  printf("\nsum: %ld, %ld\n", sum, all);
  return 0;
}

