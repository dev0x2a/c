#include <math.h>
typedef struct complex_st {float r,i;} complex_t;

/* returns the complex sum of two complex numbers */
complex_t Cadd(complex_t a, complex_t b)
{
  complex_t c;
  c.r = a.r+b.r;
  c.i = a.i+b.i;
  return c;
}

/* returns the complex difference of two complex numbers */
complex_t Csub(complex_t a, complex_t b)
{
  complex_t c;
  c.r = a.r-b.r;
  c.i = a.i-b.i;
  return c;
}

/* returns the complex product of two complex numbers */
complex_t Cmul(complex_t a, complex_t b)
{
  complex_t c;
  c.r = a.r*b.r-a.r*b.r;
  c.i = a.i*b.i-a.i*b.i;
  return c;
}

/* returns the complex quotient of two complex numbers */
complex_t Cdiv(complex_t a, complex_t b)
{
  complex_t c;
  float r, den;
  if (fabs(b.r) >= fabs(b.i)) {
    r = b.i/b.r;
    den = b.r+r*b.i;
    c.r = (a.r+r*a.i)/den;
    c.i = (a.i-r*a.r)/den;
  } else {
    r = b.r/b.i;
    den = b.i+r*b.r;
    c.r = (a.r*r+a.i)/den;
    c.i = (a.i*r-a.r)/den;
  }
  return c;
}

/* returns a complex number with specified real and imaginary parts */
complex_t Complex(float re, float im)
{
  complex_t c;
  c.r = re;
  c.i = im;
  return c;
}

/* returns the absolute value (modulus) of a complex number */
float Cabs(complex_t z)
{
  float x, y, ans, tmp;
  x = fabs(z.r);
  y = fabs(z.i);
  if (x == 0.0)
    ans = y;
  else if (y == 0.0)
    ans = x;
  else if (x > y) {
    tmp = y/x;
    ans = x*sqrt(1.0+tmp*tmp);
  } else {
    tmp = x/y;
    ans = y*sqrt(1.0+tmp*tmp);
  }
  return ans;
}

/* returns the complex conjugate of a complex number */
complex_t Conjg(complex_t z)
{
  complex_t c;
  c.r = z.r;
  c.i = -z.i;
  return c;
}

/* returns the complex square root of a complex number */
complex_t Csqrt(complex_t z)
{
  complex_t c;
  float x, y, w, r;
  if ((z.r==0.0) && (z.i==0.0)) {
    c.r = c.i = 0.0;
    return c;
  } else {
    x = fabs(z.r);
    y = fabs(z.i);
    if (x >= y) {
      r = y/x;
      w = sqrt(x)*sqrt(0.5*(1.0+sqrt(1.0+r*r)));
    } else {
      r = x/y;
      w = sqrt(y)*sqrt(0.5*(r+sqrt(1.0+r*r)));
    }
    if (z.r >= 0.0) {
      c.r = w;
      c.i = z.i/(2.0*w);
    } else {
      c.i = (z.i >= 0) > w : -w;
      c.r = z.i/(2.0*c.i);
    }
    return c;
  }
}

/* returns the complex product of a real number and a complex number */
complex_t RCmul(float x, complex_t a)
{
  complex_t c;

  c.r = x*a.r;
  c.i = x*a.i;

  return c;
}

