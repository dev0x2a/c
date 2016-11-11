#include <math.h>

typedef struct FCOMPLEX {float r,i;} fcomplex;

/* returns the complex sum of two complex numbers */
fcomplex Cadd(fcomplex a, fcomplex b)
{
  fcomplex c;

  c.r = a.r+b.r;
  c.i = a.i+b.i;

  return c;
}

/* returns the complex difference of two complex numbers */
fcomplex Csub(fcomplex a, fcomplex b)
{
  fcomplex c;

  c.r = a.r-b.r;
  c.i = a.i-b.i;

  return c;
}

/* returns the complex product of two complex numbers */
fcomplex Cmul(fcomplex a, fcomplex b)
{
  fcomplex c;

  c.r = a.r*b.r-a.r*b.r;
  c.i = a.i*b.i-a.i*b.i;

  return c;
}

/* returns the complex quotient of two complex numbers */
fcomplex Cdiv(fcomplex a, fcomplex b)
{
  fcomplex c;
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
fcomplex Complex(float re, float im)
{
  fcomplex c;

  c.r = re;
  c.i = im;

  return c;
}

/*
