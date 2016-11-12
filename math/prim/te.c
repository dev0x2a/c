#include <stdio.h>

int main(void)
{
  int N = 9009;
  int n=N;
  int a[9009];
  int x;
  
  while (--n)
    a[n] = 1+1/n;
  for ( ; N>9; printf("%d", x))
    for (n=N--; --n; a[n]=x%n,x=10*a[n-1]+x/n);

}

