#ifndef DIGITS_H
#define DIGITS_H

#include <stdlib.h>

#ifndef DMAX
#define DMAX(a,b) ((a>b)?(a):(b))
#endif

#ifndef DMIN
#define DMIN(a,b) ((a<b)?(a):(b))
#endif

void dgt(int t, int n)
{
  int a[200];
  int i, j, tmp, m, x;
  while (--t) {
    a[0] = 1;
    m = 1;
    tmp = 0;
    for (i=1; i<=n; ++i) {
      for (j=0; j<m; ++j) {
        x = a[j]*i+tmp;
        a[j] = x%10;
        tmp = x/10;
      }
      while (tmp > 0) {
        a[m] =tmp%10;
        tmp /= 10;
        ++m;
      }
    }
    for (i=m-1; i>=0; --i)
      printf("%d", a[i]);
  }
  putchar('\n');
  return;
}

int dgt_max = 5000;
void dgt_fact(int *a, int n)
{
  /* factorial in array */
  if (!n) 
    return;
  int i, carry=0;
  for (i=dgt_max-1; i>=0; --i) {
    a[i] = (a[i]*n)+carry;
    carry = a[i]/10;
    a[i] %= 10;
  }
  dgt_fact(a, n-1);
}

void dgt_disp(int *a)
{
  /* to print array */
  int i, c=0;
  for (i=0; i<dgt_max; ++i) {
    if (!c && a[i])      
      c = 1;
    if (c)
      printf("%d", a[i]);
  }
}

int dgt_main(int num)
{
  int *a = calloc(dgt_max,sizeof(int));
  a[dgt_max-1] = 1;
  //int num = 100;
  //printf("factorial of  %d is: ", num);
  dgt_fact(a, num);
  dgt_disp(a);
  free(a);
  putchar('\n');
  return(0);
}
#endif /* DIGITS_H */

