#include <stdio.h>
#include <stdlib.h>

int main() {
  
  long int i, j, F1 = 0, F2 = 1, up, sum, all;

  printf("range:  ");
  scanf("%ld", &j);
  printf("prints fibonacci seq. from 0 to %ld, returning a sum of evens and of all.\n\n", j);

  for (i = 0; i < j; i++) {
    if (i <= 1) up = i;
    else {
      up = F1 + F2;
      F1 = F2;
      F2 = up;
    }
    printf("%ld\t", up);
    if (up % 2 == 0) {
    sum += up;
    }
    all += up;
  }
  printf("\n\nsum:  %ld\n", sum);
  printf("\nall:  %ld\nwarning: negative numbers are a result of data overflow\n\n", all);
  return 0;
}

