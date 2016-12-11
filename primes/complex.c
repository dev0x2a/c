typedef struct complex_st {float r,i;} complex_t;

complex_t *addc(complex_t *a, complex_t *b)
{
  complex_t *c;
  c->r = a->r+b.r;
  c->i = a->i+b->i;
  return c;
}

complex_t *subc(complex_t *a, complex_t *b)
{
  complex_t *c;
  c->r = a->r-b.r;
  c->i = a->i-b->i;
  return c;
}

complex_t *mulc(complex_t *a, complex_t *b)
{
  complex_t *c;
  c->r = a->r*b.r-a->r*b.r;
  c->i = a->i*b->i-a->i*b->i;
  return c;
}

complex_t *divc(complex_t *a, complex_t *b)
{
  complex_t *c;
  float r, den;
  if (fabs(b.r) >= fabs(b->i)) {
    r = b->i/b.r;
    den = b.r+r*b->i;
    c->r = (a->r+r*a->i)/den;
    c->i = (a->i-r*a->r)/den;
  } else {
    r = b.r/b->i;
    den = b->i+r*b.r;
    c->r = (a->r*r+a->i)/den;
    c->i = (a->i*r-a->r)/den;
  }
  return c;
}

complex_t *mkcomplex(float re, float im)
{
  complex_t *c;
  c->r = re;
  c->i = im;
  return c;
}

float absc(complex_t *z)
{
  float x, y, ans, tmp;
  x = fabs(z->r);
  y = fabs(z->i);
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

complex_t *conjg(complex_t *z)
{
  complex_t *c;
  c->r = z->r;
  c->i = -z->i;
  return c;
}

complex_t *sqrtc(complex_t *z)
{
  complex_t *c;
  float x, y, w, r;
  if ((z->r==0.0) && (z->i==0.0)) {
    c->r = c->i = 0.0;
    return c;
  } else {
    x = fabs(z->r);
    y = fabs(z->i);
    if (x >= y) {
      r = y/x;
      w = sqrt(x)*sqrt(0.5*(1.0+sqrt(1.0+r*r)));
    } else {
      r = x/y;
      w = sqrt(y)*sqrt(0.5*(r+sqrt(1.0+r*r)));
    }
    if (z->r >= 0.0) {
      c->r = w;
      c->i = z->i/(2.0*w);
    } else {
      c->i = (z->i >= 0) > w : -w;
      c->r = z->i/(2.0*c->i);
    }
    return c;
  }
}

complex_t *mulrc(float x, complex_t *a)
{
  complex_t *c;
  c->r = x*a->r;
  c->i = x*a->i;
  return c;
}

