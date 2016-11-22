#include <stdio.h>
#include <math.h>

#define MAX 1000

int main(void)
{
  int a, b, c;
  double cf;

  for (a=1; a<MAX; ++a) {
    for (b=a; b<MAX; ++b) {
      cf=sqrt(a*a+b*b);
      c=cf;
      if ((double)c==cf) {
        if (a+b+c==MAX) {
           printf("%4d²+%4d² = %4d²\t(%3d+%4d+%4d = %4d)\tYEA!!", a,b,c,a,b,c,a+b+c);
           printf("%d",a*b*c);
        } else
          printf("%4d²+%4d² = %4d²\t(%3d+%4d+%4d = %4d)\n", a,b,c,a,b,c,a+b+c);
  }}}
  return(0);
}

