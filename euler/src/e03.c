#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int i;
  unsigned long n;
  
  printf("prime factor:\t");
  scanf("%lu", &n);

  while (n % 2 == 0) {
    printf("%d\n", 2);
    n /= 2;
  }

  for (i = 3; i<= sqrt(n); i+=2) {
    while (n % i == 0) {
      printf("%d\n", i);
      n /= i;
    }
  }
  if (n > 2) printf("%lu\n", n);
  return 0;

}

