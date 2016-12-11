/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rbn.h"

void rn_add(rni *a, rni *b, rni *c)
{
  int sa = a->s,
      sb = b->s;
  if (sa == sb) {
    c->s = sa;
    s_rn_add(a, b, c);
  } else {
    if (cmp_mag(a,b) == RN_LT) {
      c->s = sb;
      s_rn_sub(b, a, c);
    } else {
      c->s = sa;
      s_rn_sub(a, b, c);
    }
  }
}

void rn_sub(rni *a, rni *b, rni *c)
{
  int sa = a->s,
      sb = b->s;
  if (sa != sb) {
    c->s = sa;
    s_rn_add(a, b, c);
  } else {
    if (cmp_mag(a,b) != RN_LT) {
      c->s = sa;
      s_rn_sub(a, b, c);
    } else {
      c->s = (sa==ZPOS) ? RNEG : ZPOS;
      s_rn_sub(b, a, c);
    }
  }
}

void s_rn_add(rni *a, rni *b, rni *c)
{
  int x, y, ou;
  register rnw t;

  y = MAX(a->u, b->u);
  ou = MIN(c->u, RN_SIZ);
  c->u = y;
  t = 0;
  
  for (x=0; x<y; ++x) {
    t += ((rnw)a->dp[x])+((rnw)b->dp[x]);
    c->dp[x] = (rnd)t;
    t >>= DGT_BIT;
  }
  if (t!=0 && x<RN_SIZ) {
    c->dp[c->u++] = (rnd)t;
    ++x;
  }
  
  c->u = x;
  for (; x<ou; ++x)
    c->dp[x] = 0;
  rn_clamp(c);
}

void s_rn_sub(rni *a, rni *b, rni *c)
{
  int x, obu, ou;
  rnw t;

  ou = c->u;
  obu = b->u;
  c->u = a->u;
  t=0;

  for (x=0; x<obu; ++x) {
    t = ((rnw)a->dp[x])-(((rnw)b->dp[x])+t);
    c->dp[x] = (rnd)t;
    t = (t >> DGT_BIT)&1;
  }
  for (; x<ou; ++x)
    c->dp[x] = 0;
  rn_clamp(c);
}

int rn_cmp(rni *a, rni *b)
{
  if (a->s==RNEG && b->s==ZPOS)
    return RN_LT;
  else if (a->s==ZPOS && b->s==RNEG)
    return RN_GT;
  else {
    if (a->s == RNEG)
      return cmp_mag(b,a);
    else
      return cmp_mag(a,b);
  }
}

int rn_cmpd(rni *a, rnd b)
{
  if ((b && a->u==0) || a->s==RNEG)
    return RN_LT;
  if (a->u > 1)
    return RN_GT;
  if (a->dp[0] > b) {
    return RN_GT;
  } else if (a->dp[0] < b) {
    return RN_LT;
  } else
    return RN_EQ;
}

void rn_addd(rni *a, rnd b, rni *c)
{
  rni tmp;
  rn_set(&tmp, b);
  rn_add(a, &tmp, c);
}

void rn_subd(rni *a, rnd b, rni *c)
{
  rni tmp;
  rn_set(&tmp, b);
  rn_sub(a, &tmp, c);
}

int cmp_mag(rni *a, rni *b)
{
  int x;

  if (a->u > b->u) {
    return RN_GT;
  } else if (a->u < b->u) {
    return RN_LT;
  } else {
    for (x=a->u-1; x>=0; --x) {
      if (a->dp[x] > b->dp[x])
        return RN_GT;
      else if (a->dp[x] < b->dp[x])
        return RN_LT;
    }
  }
  return RN_EQ;
}

void rn_set(rni *a, rnd b)
{
  zero(a);
  a->dp[0] = b;
  a->u = a->dp[0] ? 1 : 0;
}

int rn_mod(rni *a, rni *b, rni *c)
{
  rni t;
  int err;

  zero(&t);
  if ((err=rn_div(a,b,NULL,&t)) != OK)
    return err;
  if (t.s != b->s)
    rn_add(&t, b, c);
  else
    rn_cpy(&t, c);
  return OK;
}

int rn_div(rni *a, rni *b, rni *c, rni *d)
{
  rni q, x, y, t1, t2;
  int n, t, i, norm, neg;

  if (iszero(b) == 1)
    return VAL;
  if (cmp_mag(a,b) == RN_LT) {
    if (d != NULL)
      rn_cpy(a,d);
    if (c != NULL)
      zero(c);
    return OK;
  }
  init(&q);
  q.u = a->u+2;
  init(&t1);
  init(&t2);
  initcpy(&x,a);
  initcpy(&y,b);

  neg = (a->s == b->s) ? ZPOS : RNEG;
  x.s = y.s = ZPOS;

  norm = rn_cntbit(&y) % DGT_BIT;
  if (norm < (int)(DGT_BIT-1)) {
    norm = (DGT_BIT-1)-norm;
    rn_mul2d(&x, norm, &x);
    rn_mul2d(&y, norm, &y);
  } else
    norm = 0;
  
  n = x.u-1;
  t = y.u-1;
  rn_lshd(&y, n-t);
  while (rn_cmp(&x,&y) != RN_LT) {
    ++(q.dp[n-t]);
    rn_sub(&x, &y, &x);
  }
  rn_rshd(&y,n-t);
  for (i=n; i>=(t+1); --i) {
    if (i > x.u)
      continue;
    if (x.dp[i] == y.dp[t])
      q.dp[i-t-1] = ((((rnw)1) << DGT_BIT)-1);
    else {
      rnw tmp;
      tmp = ((rnw)x.dp[i]) << ((rnw)DGT_BIT);
      tmp |= ((rnw)x.dp[i-1]);
      tmp /= ((rnw)y.dp[t]);
      q.dp[i-t-1] = (rnd)(tmp);
    }
    q.dp[i-t-1] = (q.dp[i-t-1]+1);
    do {
      q.dp[i-t-1] = (q.dp[i-t-1]-1);

      zero(&t1);
      t1.dp[0] = (t-1<0) ? 0 : y.dp[t-1];
      t1.dp[1] = y.dp[t];
      t1.u = 2;
      rn_muld(&t1, q.dp[i-t-1], &t1);

      t2.dp[0] = (i-2<0) ? 0 : x.dp[i-2];
      t2.dp[1] = (i-1<0) ? 0 : x.dp[i-1];
      t2.dp[2] = x.dp[i];
      t2.u = 3;
    } while (cmp_mag(&t1,&t2) == RN_GT);
    rn_muld(&y, q.dp[i-t-1], &t1);
    rn_lshd(&t1, i-t-1);
    rn_sub(&x, &t1, &x);
    if (x.s == RNEG) {
      rn_cpy(&y, &t1);
      rn_lshd(&t1, i-t-1);
      rn_add(&x, &t1, &x);
      q.dp[i-t-1] = q.dp[i-t-1]-1;
    }
  }
  x.s = x.u == 0 ? ZPOS : a->s;
  if (c != NULL) {
    rn_clamp(&q);
    rn_cpy(&q, c);
    c->s = neg;
  }
  if (d != NULL) {
    rn_div2d(&x, norm, &x, NULL);
    for (i=b->u; i<x.u; ++i)
      x.dp[i] = 0;
    rn_clamp(&x);
    rn_cpy(&x, d);
  }
  return OK;
}

int rn_modd(rni *a, rnd b, rnd *c)
{ return rn_divd(a,b,NULL,c); }

static int s_ispow2(rnd b, int *p)
{
  int x;

  if ((b==0) || (b&(b-1)))
    return 0;

  for (x=0; x<DGT_BIT; ++x) {
    if (b == (((rnd)1) << x)) {
      *p = x;
      return 1;
    }
  }
  return 0;
}

int rn_divd(rni *a, rnd b, rni *c, rnd *d)
{
  rni q;
  rnw w;
  rnd t;
  int ix;

  if (b == 0)
    return VAL;
  if (b==1 || iszero(a)==1) {
    if (d != NULL)
      *d = 0;
    if (c != NULL)
      rn_cpy(a,c);
    return OK;
  }
  if (s_ispow2(b,&ix) == 1) {
    if (d != NULL)
      *d = a->dp[0] & ((((rnd)1) << ix)-1);
    if (c != NULL)
      rn_div2d(a, ix, c, NULL);
    return OK;
  }
  init(&q);
  q.u = a->u;
  q.s = a->s;
  w = 0;
  for (ix=a->u-1; ix>=0; --ix) {
    w = (w << ((rnw)DGT_BIT)) | ((rnw)a->dp[ix]);
    if (w >= b) {
      t = (rnd)(w/b);
      w -= ((rnw)t)*((rnw)b);
    } else
      t = 0;
    q.dp[ix] = (rnd)t;
  }
  if (d != NULL)
    *d = (rnd)w;
  if (c != NULL) {
    rn_clamp(&q);
    rn_cpy(&q,c);
  }
  return OK;
}

void rn_rshd(rni *a, int x)
{
  int y;
  if (x >= a->u) {
    zero(a);
    return;
  }
  for (y=0; y<a->u-x; ++y)
    a->dp[y] = a->dp[y+x];
  for (; y<a->u; ++y)
    a->dp[y] = 0;
  a->u -= x;
  rn_clamp(a);
}

void rn_lshd(rni *a, int x)
{
  int y;
  y = MIN(a->u+x-1, (int)(RN_SIZ-1));
  a->u = y+1;
  for (; y>=x; --y)
    a->dp[y] = a->dp[y-x];
  for (; y>=0; --y)
    a->dp[y] = 0;
  rn_clamp(a);
}

int rn_cntbit(rni *a)
{
  int r;
  rnd q;
  if (a->u == 0)
    return 0;
  r = (a->u-1)*DGT_BIT;
  q = a->dp[a->u-1];
  while (q > ((rnd)0)) {
    ++r;
    q >>= ((rnd)1);
  }
  return r;
}

void rn_2exp(rni *a, int b)
{
  int z;
  zero(a);
  if (b < 0)
    return;
  z = b/DGT_BIT;
  if (z >= RN_SIZ)
    return;
  a->u = z+1;
  a->dp[z] = ((rnd)1) << (b % DGT_BIT);
}

void rn_div2(rni *a, rni *b)
{
  int x, ou;
  ou = b->u;
  b->u = a->u;
  {
    register rnd r, rr, *tmpa, *tmpb;

    tmpa = a->dp+b->u-1;
    tmpb = b->dp+b->u-1;
    r = 0;
    for (x=b->u-1; x>=0; --x) {
      rr = *tmpa&1;
      *tmpb-- = (*tmpa-- >> 1) | (r << (DGT_BIT-1));
      r = rr;
    }
    tmpb = b->dp+b->u;
    for (x=b->u; x<ou; ++x)
      *tmpb++ = 0;
  }
  b->s = a->s;
  rn_clamp(b);
}

void rn_div2d(rni *a, int b, rni *c, rni *d)
{
  rnd D, r, rr;
  rni t;
  int x;

  if (b <= 0) {
    rn_cpy(a,c);
    if (d != NULL)
      zero(d);
    return;
  }
  init(&t);
  
  if (d != NULL)
    rn_mod2d(a, b, &t);
  rn_cpy(a,c);
  if (b >= (int)DGT_BIT)
    rn_rshd(c, b/DGT_BIT);

  D = (rnd)(b % DGT_BIT);
  if (D != 0) {
    register rnd *tmpc, mask, shift;
    mask = (((rnd)1) << D)-1;
    shift = DGT_BIT-D;
    tmpc = c->dp+(c->u-1);
    r = 0;
    for (x=c->u-1; x>=0; --x) {
      rr = *tmpc & mask;
      *tmpc = (*tmpc >> D) | (r << shift);
      --tmpc;
      r = rr;
    }
  }
  rn_clamp(c);
  if (d != NULL)
    rn_cpy(&t, d);
}

int rn_cntlsb(rni *a)
{
  int x;
  rnd q, qq;

  if (iszero(a) == 1)
    return 0;
  for (x=0; x<a->u && a->dp[x]==0; ++x);
  q = a->dp[x];
  x *= DGT_BIT;
  if ((q&1) == 0) {
    do {
      qq = q&15;
      x += lnz[qq];
      q >>= 4;
    } while (qq == 0);
  }
  return x;
}

void rn_mod2d(rni *a, int b, rni *c)
{
  int x;
  if (b <= 0) {
    zero(c);
    return;
  }
  rn_cpy(a,c);
  if (b >= (DGT_BIT*a->u))
    return;
  for (x=(b/DGT_BIT)+((b%DGT_BIT)==0?0:1); x<c->u; ++x)
    c->dp[x] = 0;
  c->dp[b/DGT_BIT] &= ~((rnd)0) >> (DGT_BIT-b);
  rn_clamp(c);
}

void rn_mul(rni *A, rni *B, rni *C)
{
  int y, ou;
#if RN_SIZ >= 48
  int yy;
#endif
  ou = C->u;
  if (A->u+B->u > RN_SIZ) {
    rn_mul_comba(A, B, C);
    goto clean;
  }
  y = MAX(A->u, B->u);
#if RN_SIZ >= 48
  yy = MIN(A->u, B->u);
#endif
/* pick a comba (unrolled 4/8/16/32 x or rolled) based on the size
   of the largest input.  We also want to avoid doing excess mults if the
   inputs are not close to the next power of two.  That is, for example,
   if say y=17 then we would do (32-17)^2 = 225 unneeded multiplications */
#if defined(RN_MUL3) && RN_SIZ >= 6
  if (y <= 3) {
    rn_mul_comba3(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL4) && RN_SIZ >= 8
  if (y == 4) {
    rn_mul_comba4(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL6) && FP_SIZE >= 12
  if (y <= 6) {
    rn_mul_comba6(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL7) && RN_SIZ >= 14
  if (y == 7) {
    rn_mul_comba7(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL8) && RN_SIZ >= 16
  if (y == 8) {
    rn_mul_comba8(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL9) && RN_SIZ >= 18
  if (y == 9) {
    rn_mul_comba9(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL12) && RN_SIZ >= 24
  if (y <= 12) {
    rn_mul_comba12(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL17) && RN_SIZ >= 34
  if (y <= 17) {
    rn_mul_comba17(A, B, C);
    goto clean;
  }
#endif

#if defined(RN_SMALL_SET) && RN_SIZ >= 32
  if (y <= 16) {
    rn_mul_comba_small(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL20) && RN_SIZ >= 40
  if (y <= 20) {
    rn_mul_comba20(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL24) && RN_SIZ >= 48
  if (yy>=16 && y<=24) {
    rn_mul_comba24(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL28) && RN_SIZ >= 56
  if (yy>=20 && y<=28) {
    rn_mul_comba28(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL32) && RN_SIZ >= 64
  if (yy>=24 && y<=32) {
    rn_mul_comba32(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL48) && RN_SIZ >= 96
  if (yy>=40 && y<=48) {
    rn_mul_comba48(A, B, C);
    goto clean;
  }
#endif
#if defined(RN_MUL64) && RN_SIZ >= 128
  if (yy>=56 && y<=64) {
    rn_mul_comba64(A, B, C);
    goto clean;
  }
#endif
  rn_mul_comba(A, B, C);
clean:
  for (y=C->u; y<ou; ++y)
    C->dp[y] = 0;
}

