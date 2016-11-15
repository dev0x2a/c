#include <stdio.h>
#include <math.h>
#include "m_atoi.c"

int root(int n)
{
  return (int) sqrt((float) n);
}

int prime(int n)
{
  int i, bound;
  bound = root(n);
  for (i=2; i<=bound; ++i)
    if (n%i == 0)
      return 0;
  return 1;
}

int main(int argc, char *argv[])
{
  int i, n;
  n = m_atoi(argv[1]);

  for (i=2; i<=n; ++i)
    if (prime(i))
      printf("%d\n", i);
  return 0;
}

