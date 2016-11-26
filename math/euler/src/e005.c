#include <stdio.h>

int gcd(int a, int b)
{
  while (a != b) {
    if (a > b)
      a -= b;
    else
      b -= a;
  }
  return(a);
}

int lcm(int a, int b)
{
  return(a/gcd(a,b)*b);
}

int main(void) 
{
  int n=1;
  
  for(int i=1; i<21; ++i)
    n = lcm(n, i+1);
  printf("-> %d\n", n);

  return(0);
}

