#include <stdio.h>

int power(int b, int e)
{
  int i, res=1;
  for (i=0; i<e; ++i)
    res *= b;
  return(res);
}

int main(void)
{
  int s1, s2, ds;
  for (int i=1; i<=100; ++i)
    s1 += power(i, 2);
  for (int i=1; i<=100; ++i)
    s2 += i;

  s2 = power(s2, 2);
  ds = s2-s1;
  printf("-> %d\n-> %d\n-> %d\n", s1,s2,ds);
  return(0);
}

