/*
 * facttail.c: compute a factorial in a tail-recursive manner
 */

#include <stdio.h>
#include "alg.h"

int facttail(int n, int a)
{
  if (n < 0)
    return 0;
  else if (n == 0)
    return 1;
  else if (n == 1)
    return a;
  else
    return n*facttail(n-1, n*a);
}

int main(int argc, char *argv[])
{
  int n, a;
  n = m_atoi(argv[1]);
  a = m_atoi(argv[2]);
  
  printf("%d\n", facttail(n, a));
  return 0;
}

