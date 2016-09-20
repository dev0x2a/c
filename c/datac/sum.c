/*
 * sum.c
 * compute the sum of a sequence of integers
 */
#include <stdio.h>

int main()
{ int i, s=0;
  while (scanf("%d", &i) > 0) s += i;
  printf("\nThe sum is: %d\n", s);
}

