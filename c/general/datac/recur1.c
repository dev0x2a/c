/*
 * recur1.c
 * first example of recursion
 */
#include <stdio.h>

int p(int n);

int main()
{
  p(4);
}

int p(n) int n;
{
  if (n>0) { p(n-2); printf("%3d", n); p(n-1); }
}

