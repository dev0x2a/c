#include <stdio.h>
#include <stdlib.h>

int main() {
  
  int n, sum = 0;

  printf("range:  ");
  scanf("%d", &n);
  printf("\nthis will find multiples of 3 & 5 in range [1,%d], and produce a sum of those multiples.\n\n",n-1);

  for (int i = 1; i < n; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      printf("%d ", i);
      sum += i;         
    }
  }
  printf("\n\nSum:  %d\n\n", sum);
  return 0;
}

