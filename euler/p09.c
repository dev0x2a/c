#include <stdio.h>
#include <math.h>

#define MAX 1000
#define ERROR 0

int main()
{
  int a, b, c, d, e, f, g, h, i, k, m, n;
  double cf;
   
  for (a=1; a<MAX; a++) {
    for (b=a; b<MAX; b++) {
      cf = sqrt(a*a+b*b);
      c = cf;
      if ((double)c == cf) {
         if (a+b+c == MAX) {
           printf("%4d² + %4d² = %4d² \t\t(%3d + %4d + %4d = %4d)\tYEA!!\t", a, b, c, a, b, c, a+b+c);
           printf("%d", a*b*c);
         }
         else
           printf("%4d² + %4d² = %4d² \t\t(%3d + %4d + %4d = %4d)\n", a, b, c, a, b, c, a+b+c);
      }
    }
  }
       
#if 0
  for (a=3,b=4,c=5; a+b+c<=600; ++a, ++b, ++c) {
    k = a-(2*b)+(2*c);
    m = (2*a)-b+(2*c);
    n = (2*a)-(2*b)+(3*c);

    d = a+(2*b)+(2*c);
    e = (2*a)+b+(2*c);
    f = (2*a)+(2*b)+(3*c);

    g = -a+(2*b)+(2*c);
    h = -(2*a)+b+(2*c);
    i = -(2*a)+(2*b)+(3*c);

    printf("%4d\t%4d\t%4d\t%4d\n", k, m, n, k+m+n);
    printf("%4d\t%4d\t%4d\t%4d\n", d, e, f, d+e+f);
    printf("%4d\t%4d\t%4d\t%4d\n", g, h, i, g+h+i);
  }
  // this generates primitive triples
  for (k=80, a=3, b=4, c=5; (k*a+k*b+k*c)<=MAX; ++k) {
    printf("%4d\t%4d\t%4d\t%4d\t%4d\n",((k*a) + (k*b) + (k*c)), k*a, k*b, k*c, k);
  }
#endif  

  return 0;
}

