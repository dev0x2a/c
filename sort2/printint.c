#include <stdio.h>

void printint(int w, int x)
{
  int n = 0, i, negint = x<0;
  char digs[30];

  if (negint)
    x = -x;
  do {
    digs[n++] = '0'+x%10;
    x /= 10;
  } while (x);
  i = w-n;
  if (negint)
    i--;
  while (i-- > 0)
    putchar(' ');
  if (negint)
    putchar('-');
  for (i=n-1; i>=0; --i)
    putchar(digs[i]);
}

int main(void)
{
  printint(1, 3);
  putchar('\n');
  return 0;
}

