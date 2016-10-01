#include <stdio.h>
#include <stdlib.h>

int
main(void)
{  
  int n, sum = 0;

  printf("range: ");
  scanf("%d", &n);
  printf("\nfind multiples of 3 & 5 in range [1,%d], w/ summation\n", n-1);

  for (int i=1; i<n; ++i) {
    if (i%3 == 0 || i%5 == 0) {
      printf("%d ", i);
      sum += i;         
    }
  }
  printf("\nsum: %d\n\n", sum);
  return 0;
}

