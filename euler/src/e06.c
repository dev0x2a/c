#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int power(int b,unsigned int e)
{
  int i, res = 1; for (i = 0;i < e; i++) res *= b;return res;
}

int main()
{
  int sum1,sum2,diff;

  for (int i = 1; i <= 100; i++) {
    sum1 += power(i,2);
  }
  for (int j = 1;j <= 100; j++) {
    sum2 += j;
  }
  sum2 = power(sum2,2);
  diff = sum2 - sum1;

  printf("%d\n", sum1);
  printf("%d\n", sum2);
  printf("%d\n", diff);
  return 0;
}

