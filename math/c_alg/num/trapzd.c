#include <math.h>
#include "nrutil.h"

#define FUNC(x) ((*func)(x))
#define EPS 1.0e-5
#define JMAX 20

float trapzd(float (*func)(), float a, float b, int n)
{
  float x, tnm, sum, del;
  static float s;
  static int it;
  int j;

  if (n == 1) {
    it=1;
    return (s=0.5*(b-a)*(FUNC(a)+FUNC(b)));
  } else {
    tnm=it;
    del=(b-a)/tnm;
    x=a+0.5*del;
    for (sum=0.0,j=1; j<=it; ++j,x+=del)
      sum += FUNC(x);
    it *= 2;
    s=0.5*(s+(b-a)*sum/tnm);
    return s;
  }
}

float qtrap(float (*func)(), float a, float b)
{
  int j;
  float s, olds;
  void nrerror();

  olds = -1.0e30;
  for (j=1; j<=JMAX; ++j) {
    s=trapzd(func,a,b,j);
    if (fabs(s-olds) < EPS*fabs(olds))
      return s;
    olds=s;
  }
  nrerror("Too many steps in routine QTRAP");
}

int main(int argc, char *argv[])
{
  float (*func)();
  float a, b;

  a = 1.0;
  b = 2.0;

  printf("%f\n", qtrap(func, a, b));
  return 0;
}

