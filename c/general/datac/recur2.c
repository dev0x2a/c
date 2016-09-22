/*
 * recur2.c
 * second example of recursion
 */
#include <stdio.h>

int p(int n);

int main()
{
  p(80);
}

int p(int n)
{
  if (n>0) { p(n-40); printf("%3d", n); p(n-20); }
}

