/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rbn.h"

void rn_printf(rni *a, int radix, FILE *o)
{
  int x;
  char buf[4096];
  rn_toradixn(a, buf, radix, INT_MAX);
  for (x=a->u-1; x>=0; --x) {
    fprintf(o, "%c", buf[x]);
  }
  return;
}

void rn_add(rni *a, rni *b, rni *c)
{
  int sa = a->s,
      sb = b->s;
  if (sa == sb) {
    c->s = sa;
    s_rn_add(a, b, c);
  } else {
    if (rn_cmp_mag(a,b) == RN_LT) {
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
    if (rn_cmp_mag(a,b) != RN_LT) {
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
  int x,
      y = MAX(a->u, b->u),
      ou = MIN(c->u, RN_SIZ);
  register rnw t=0;
  c->u = y;
  
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
  int x,
      ou = c->u,
      obu = b->u;
  rnw t=0;
  c->u = a->u;

  for (x=0; x<obu; ++x) {
    t = ((rnw)a->dp[x])-(((rnw)b->dp[x])+t);
    c->dp[x] = (rnd)t;
    t = (t>>DGT_BIT)&1;
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
      return rn_cmp_mag(b,a);
    else
      return rn_cmp_mag(a,b);
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

int rn_cmp_mag(rni *a, rni *b)
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
  if (rn_cmp_mag(a,b) == RN_LT) {
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

  neg = (a->s==b->s) ? ZPOS : RNEG;
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
      q.dp[i-t-1] = ((((rnw)1)<<DGT_BIT)-1);
    else {
      rnw tmp;
      tmp = ((rnw)x.dp[i])<<((rnw)DGT_BIT);
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
    } while (rn_cmp_mag(&t1,&t2) == RN_GT);
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
    if (b == (((rnd)1)<<x)) {
      *p = x;
      return 1;
    }
  }
  return 0;
}

int rn_divd(rni *a, rnd b, rni *c, rnd *d)
{
  rni q;
  rnd t;
  rnw w=0;
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
  int y = MIN(a->u+x-1, (int)(RN_SIZ-1));
  a->u = y+1;
  for (; y>=x; --y)
    a->dp[y] = a->dp[y-x];
  for (; y>=0; --y)
    a->dp[y] = 0;
  rn_clamp(a);
}

int rn_cntbit(rni *a)
{
  if (a->u == 0)
    return 0;
  int r = (a->u-1)*DGT_BIT;
  rnd q = a->dp[a->u-1];
  while (q > ((rnd)0)) {
    ++r;
    q >>= ((rnd)1);
  }
  return r;
}

void rn_2exp(rni *a, int b)
{
  zero(a);
  if (b < 0)
    return;
  int z = b/DGT_BIT;
  if (z >= RN_SIZ)
    return;
  a->u = z+1;
  a->dp[z] = ((rnd)1)<<(b%DGT_BIT);
}

void rn_div2(rni *a, rni *b)
{
  int x,
      ou = b->u;
  b->u = a->u;
  {
    register rnd r=0, rr, *tmpa, *tmpb;

    tmpa = a->dp+b->u-1;
    tmpb = b->dp+b->u-1;
    for (x=b->u-1; x>=0; --x) {
      rr = *tmpa&1;
      *tmpb-- = (*tmpa-- >> 1)|(r << (DGT_BIT-1));
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
  c->dp[b/DGT_BIT] &= ~((rnd)0)>>(DGT_BIT-b);
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

void rn_mul2(rni *a, rni *b)
{
  int x,
      ou = b->u;
  b->u = a->u;
  {
    register rnd r=0, rr, *tmpa, *tmpb;

    tmpa = a->dp;
    tmpb = b->dp;
    for (x=0; x<a->u; ++x) {
      rr = *tmpa >> ((rnd)(DGT_BIT-1));
      *tmpb++ = ((*tmpa++ << ((rnd)1))|r);
      r = rr;
    }
    if (r!=0 && b->u!=(RN_SIZ-1)) {
      *tmpb = 1;
      ++(b->u);
    }
    tmpb = b->dp+b->u;
    for (x=b->u; x<ou; ++x)
      *tmpb++ = 0;
  }
  b->s = a->s;
}

void rn_mul2d(rni *a, int b, rni *c)
{
  rnd carry, carrytmp, shift;
  int x;

  rn_cpy(a,c);
  if (b >= DGT_BIT)
    rn_lshd(c, b/DGT_BIT);
  b %= DGT_BIT;
  if (b != 0) {
    carry = 0;
    shift = DGT_BIT-b;
    for (x=0; x<c->u; ++x) {
      carrytmp = c->dp[x] >> shift;
      c->dp[x] = (c->dp[x] << b)+carry;
      carry = carrytmp;
    }
    if (carry && x<RN_SIZ)
      c->dp[c->u++] = carry;
  }
  rn_clamp(c);
}

int rn_mulmod(rni *a, rni *b, rni *c, rni *d)
{
  rni tmp;
  zero(&tmp);
  rn_mul(a, b, &tmp);
  return rn_mod(&tmp, c, d);
}

void rn_muld(rni *a, rnd b, rni *c)
{
  rnw w=0;
  int x,
      ou = c->u;
  c->u = a->u;
  c->s = a->s;
  for (x=0; x<a->u; ++x) {
    w = ((rnw)a->dp[x])*((rnw)b)+w;
    c->dp[x] = (rnd)w;
    w = w>>DGT_BIT;
  }
  if (w!=0 && (a->u!=RN_SIZ)) {
    c->dp[c->u++] = w;
    ++x;
  }
  for (; x<ou; ++x)
    c->dp[x] = 0;
  rn_clamp(c);
}

void rn_rev(unsigned char *s, int len)
{
  int ix=0, iy=len-1;
  unsigned char t;

  while (ix < iy) {
    t = s[ix];
    s[ix] = s[iy];
    s[iy] = t;
    ++ix;
    --iy;
  }
}

int rn_radix_siz(rni *a, int radix, int *size)
{
  rni t;
  rnd d;
  *size = 0;
  if (radix<2 || radix>64)
    return VAL;
  if (iszero(a) == 1) {
    *size = 2;
    return OK;
  }
  initcpy(&t, a);
  if (t.s == RNEG) {
    (*size)++;
    t.s == ZPOS;
  }
  while (iszero(&t) == RNN) {
    rn_divd(&t, (rnd)radix, &t, &d);
    (*size)++;
  }
  (*size)++;
  return OK;
}

int rn_read_radix(rni *a, const char *str, int radix)
{
  int y, neg;
  char ch;
  zero(a);
  if (radix<2 || radix>64)
    return VAL;
  if (*str == '-') {
    ++str;
    neg = RNEG;
  } else
    neg = ZPOS;
  while (*str) {
    ch = (char)((radix<=36)?toupper((int)*str):*str);
    for (y=0; y<64; ++y) {
      if (ch == rn_srmap[y])
        break;
    }
    if (y < radix) {
      rn_muld(a, (rnd)radix, a);
      rn_addd(a, (rnd)y, a);
    } else
      break;
    ++str;
  }
  if (iszero(a) != RNY)
    a->s = neg;
  return OK;
}

int rn_toradixn(rni *a, char *str, int radix, int maxlen)
{
  rni t;
  rnd d;
  int dgt = 0;
  char *_s = str;

  if (maxlen<2 || radix<2 || radix>64)
    return VAL;
  if (iszero(a) == RNY) {
    *str++ = '0';
    *str = '\0';
  }
  initcpy(&t, a);
  if (t.s == RNEG) {
    ++_s;
    *str++ = '-';
    t.s = ZPOS;
    --maxlen;
  }
  while (iszero(&t) == RNN) {
    if (--maxlen < 1)
      break;
    rn_divd(&t, (rnd)radix, &t, &d);
    *str++ = rn_srmap[d];
    ++dgt;
  }
  rn_rev((unsigned char *)_s, dgt);
  *str = '\0';
  if (maxlen < 1)
    return VAL;
  return OK;
}

int rn_toradix(rni *a,  char *str, int radix)
{ return rn_toradixn(a, str, radix, INT_MAX); }

void rn_rand(rni *a, int dgt)
{
  rnd d;
  zero(a);
  if (dgt <= 0)
    return;
  do
    d = ((rnd)abs(rand())) & MASK;
  while (d == 0);
  rn_addd(a, d, a);
  while (--dgt > 0) {
    rn_lshd(a, 1);
    rn_addd(a, ((rnd)abs(rand())), a);
  }
  return;
}

void rn_gcd(rni *a, rni *b, rni *c)
{
  rni u, v, r;

  if (iszero(a)==1 && iszero(b)==0) {
    rn_abs(b, c);
    return;
  }
  if (iszero(a)==0 && iszero(b)==1) {
    rn_abs(a, c);
    return;
  }
  if (iszero(a) == 1) {
    zero(c);
    return;
  }
  if (rn_cmp_mag(a,b) != RN_LT) {
    initcpy(&u, a);
    initcpy(&v, b);
  } else {
    initcpy(&u, b);
    initcpy(&v, a);
  }
  zero(&r);
  while (iszero(&v) == RNN) {
    rn_mod(&u,&v,&r);
    rn_cpy(&v,&u);
    rn_cpy(&r,&v);
  }
  rn_cpy(&u,c);
}

void rn_lcm(rni *a, rni *b, rni *c)
{
  rni t1, t2;

  init(&t1);
  init(&t2);
  rn_gcd(a, b, &t1);
  if (rn_cmp_mag(a,b) == RN_GT) {
    rn_div(a, &t1, &t2, NULL);
    rn_mul(b, &t2, c);
  } else {
    rn_div(b, &t1, &t2, NULL);
    rn_mul(a, &t2, c);
  }
}

/* Miller-Rabin test of "a" to the base of "b" as described in
   HAC pp. 139 Algorithm 4.24
   Sets result to 0 if definitely composite or 1 if probably prime.
   Randomly the chance of error is no more than 1/4 and often
   very much lower */
void rn_pr_millrab(rni *a, rni *b, int *res)
{
  rni n1, y, r;
  int s, j;
  *res = RNN;

  if (rn_cmpd(b,1) != RN_GT)
    return;
  initcpy(&n1, a);
  rn_subd(&n1, 1, &n1);

  initcpy(&r, &n1);
  s = rn_cntlsb(&r);
  rn_div2d(&r, s, &r, NULL);
  init(&y);
  rn_exptmod(b, &r, a, &y);

  if (rn_cmpd(&y,1)!=RN_EQ && rn_cmp(&y,&n1)!=RN_EQ) {
    j = 1;
    while ((j<=(s-1)) && rn_cmp(&y,&n1)!=RN_EQ) {
      rn_sqrmod(&y, a, &y);
      if (fp_cmpd(&y,1) == RN_EQ)
        return;
      ++j;
    }
    if (rn_cmp(&y,&n1) != RN_EQ)
      return;
  }
  *res = RNY;
}

static const rnd primes[PR_SIZ] = {
  0x0002, 0x0003, 0x0005, 0x0007, 0x000b, 0x000d, 0x0011, 0x0013,
  0x0017, 0x001d, 0x001f, 0x0025, 0x0029, 0x002b, 0x002f, 0x0035,
  0x003b, 0x003d, 0x0043, 0x0047, 0x0049, 0x004f, 0x0053, 0x0059,
  0x0061, 0x0065, 0x0067, 0x006b, 0x006d, 0x0071, 0x007f, 0x0083,
  0x0089, 0x008b, 0x0095, 0x0097, 0x009d, 0x00a3, 0x00a7, 0x00ad,
  0x00b3, 0x00b5, 0x00bf, 0x00c1, 0x00c5, 0x00c7, 0x00d3, 0x00df,
  0x00e3, 0x00e5, 0x00e9, 0x00ef, 0x00f1, 0x00fb, 0x0101, 0x0107,
  0x010d, 0x010f, 0x0115, 0x0119, 0x011b, 0x0125, 0x0133, 0x0137,

  0x0139, 0x013d, 0x014b, 0x0151, 0x015b, 0x015d, 0x0161, 0x0167,
  0x016f, 0x0175, 0x017b, 0x017f, 0x0185, 0x018d, 0x0191, 0x0199,
  0x01a3, 0x01a5, 0x01af, 0x01b1, 0x01b7, 0x01bb, 0x01c1, 0x01c9,
  0x01cd, 0x01cf, 0x01d3, 0x01df, 0x01e7, 0x01eb, 0x01f3, 0x01f7,
  0x01fd, 0x0209, 0x020b, 0x021d, 0x0223, 0x022d, 0x0233, 0x0239,
  0x023b, 0x0241, 0x024b, 0x0251, 0x0257, 0x0259, 0x025f, 0x0265,
  0x0269, 0x026b, 0x0277, 0x0281, 0x0283, 0x0287, 0x028d, 0x0293,
  0x0295, 0x02a1, 0x02a5, 0x02ab, 0x02b3, 0x02bd, 0x02c5, 0x02cf,

  0x02d7, 0x02dd, 0x02e3, 0x02e7, 0x02ef, 0x02f5, 0x02f9, 0x0301,
  0x0305, 0x0313, 0x031d, 0x0329, 0x032b, 0x0335, 0x0337, 0x033b,
  0x033d, 0x0347, 0x0355, 0x0359, 0x035b, 0x035f, 0x036d, 0x0371,
  0x0373, 0x0377, 0x038b, 0x038f, 0x0397, 0x03a1, 0x03a9, 0x03ad,
  0x03b3, 0x03b9, 0x03c7, 0x03cb, 0x03d1, 0x03d7, 0x03df, 0x03e5,
  0x03f1, 0x03f5, 0x03fb, 0x03fd, 0x0407, 0x0409, 0x040f, 0x0419,
  0x041b, 0x0425, 0x0427, 0x042d, 0x043f, 0x0443, 0x0445, 0x0449,
  0x044f, 0x0455, 0x045d, 0x0463, 0x0469, 0x047f, 0x0481, 0x048b,

  0x0493, 0x049d, 0x04a3, 0x04a9, 0x04b1, 0x04bd, 0x04c1, 0x04c7,
  0x04cd, 0x04cf, 0x04d5, 0x04e1, 0x04eb, 0x04fd, 0x04ff, 0x0503,
  0x0509, 0x050b, 0x0511, 0x0515, 0x0517, 0x051b, 0x0527, 0x0529,
  0x052f, 0x0551, 0x0557, 0x055d, 0x0565, 0x0577, 0x0581, 0x058f,
  0x0593, 0x0595, 0x0599, 0x059f, 0x05a7, 0x05ab, 0x05ad, 0x05b3,
  0x05bf, 0x05c9, 0x05cb, 0x05cf, 0x05d1, 0x05d5, 0x05db, 0x05e7,
  0x05f3, 0x05fb, 0x0607, 0x060d, 0x0611, 0x0617, 0x061f, 0x0623,
  0x062b, 0x062f, 0x063d, 0x0641, 0x0647, 0x0649, 0x064d, 0x0653};

int rn_isprime(rni *a, int t)
{
  rni b;
  rnd d;
  int r, res;

  if (t<=0 || t>PR_SIZ)
    return RNN;
  for (r=0; r<256; ++r) {
    rn_modd(a, primes[r], &d);
    if (d == 0)
      return RNN;
  }
  fp_init(&b);
  for (r=0; r<t; ++r) {
    rn_set(&b, primes[r]);
    rn_pr_millrab(a, &b, &res);
    if (res == RNN)
      return RNN;
  }
  return RNY;
}

int rn_pr_rand(rni *a, int t, int size, int flags,
               rn_prime_callback cb, void *dat)
{
  unsigned char *tmp, maskAND, maskOR_msb, maskOR_lsb;
  int res, err, bsize, maskOR_msb_offset;

  if (size<=1 || cb==NULL || t<=0 || t>PR_SIZ)
    return VAL;
  if (flags & PR_SAFE)
    flags |= PR_BBS;

  bsize = (size>>3)+(size&7 ? 1 : 0);
  tmp = malloc(bsize);
  if (tmp == NULL)
    return MEM;

  maskAND = 0xff>>((8-(size&7))&7);
  maskOR_msb = 0;
  maskOR_msb_offset = (size-2)>>3;

  if (flags & PR_2MSB_ON) {
    maskOR_msb |= 1<<((size-2)&7);
  } else if (flags & PR_2MSB_OFF) {
    maskAND &= ~(1<<((size-2)&7));
  }
  maskOR_lsb = 1;
  if (flags & PR_BBS)
    maskOR_lsb |= 3;
  do {
    if (cb(tmp, bsize, dat) != bsize) {
      err = VAL;
      goto error;
    }
    tmp[0] &= maskAND;
    tmp[0] |= 1<<((size-1)&7);

    tmp[maskOR_msb_offset] |= maskOR_msb;
    tmp[bsize-1] |= maskOR_lsb;

    rn_read_unsigned_bin(a, tmp, bsize);
    res = rn_isprime(a, t);
    if (res == RNN)
      continue;
    if (flags & PR_SAFE) {
      rn_subd(a, 1, a);
      rn_div2(a, a);
      res = rn_isprime(a, t);
    }
  } while (res == RNN);
  if (flags & PR_SAFE) {
    rn_mul2(a, a);
    rn_addd(a, 1, a);
  }
  err = OK;
error:
  free(tmp);
  return err;
}

