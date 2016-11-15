/*
 * fact.c: compute a factorial recursively
 */

#include <stdio.h>
#include "alg.h"

int fact(int n)
{
  if (n < 0)
    return 0;
  else if (n == 0)
    return 1;
  else if (n == 1)
    return 1;
  else
    return n*fact(n-1);
}

int main(int argc, char *argv[])
{
  int n;
  n = m_atoi(argv[1]);
  
  printf("%d\n", fact(n));
  return 0;
}

