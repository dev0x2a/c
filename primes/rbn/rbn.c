/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rbn_priv.h"

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
  int sa=a->s, sb=b->s;
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
  int sa=a->s, sb=b->s;
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
  int x, y=MAX(a->u, b->u), ou=MIN(c->u, RN_SIZ);
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
  int x, ou=c->u, obu=b->u;
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
  if (a->u > b->u) {
    return RN_GT;
  } else if (a->u < b->u) {
    return RN_LT;
  } else {
    int x;
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
  norm = rn_cntbit(&y)%DGT_BIT;
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
  if ((b==0) || (b&(b-1)))
    return 0;
  int x;
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
  if (b == 0)
    return VAL;
  if (b==1 || iszero(a)==1) {
    if (d != NULL)
      *d = 0;
    if (c != NULL)
      rn_cpy(a,c);
    return OK;
  }
  int ix;
  if (s_ispow2(b,&ix) == 1) {
    if (d != NULL)
      *d = a->dp[0]&((((rnd)1)<<ix)-1);
    if (c != NULL)
      rn_div2d(a, ix, c, NULL);
    return OK;
  }
  rni q;
  rnd t;
  rnw w=0;
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
  if (x >= a->u) {
    zero(a);
    return;
  }
  int y;
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
  int x, ou = b->u;
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
  if (b <= 0) {
    rn_cpy(a,c);
    if (d != NULL)
      zero(d);
    return;
  }
  rni t;
  init(&t);
  if (d != NULL)
    rn_mod2d(a, b, &t);
  rn_cpy(a,c);
  if (b >= (int)DGT_BIT)
    rn_rshd(c, b/DGT_BIT);

  rnd D = (rnd)(b%DGT_BIT);
  if (D != 0) {
    register rnd *tmpc, mask, shift;
    mask = (((rnd)1) << D)-1;
    shift = DGT_BIT-D;
    tmpc = c->dp+(c->u-1);
    rnd rr, r=0;
    int x;
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
  if (iszero(a) == 1)
    return 0;
  int x;
  for (x=0; x<a->u && a->dp[x]==0; ++x);
  rnd qq, q=a->dp[x];
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
  if (b <= 0) {
    zero(c);
    return;
  }
  rn_cpy(a,c);
  if (b >= (DGT_BIT*a->u))
    return;
  int x;
  for (x=(b/DGT_BIT)+((b%DGT_BIT)==0?0:1); x<c->u; ++x)
    c->dp[x] = 0;
  c->dp[b/DGT_BIT] &= ~((rnd)0)>>(DGT_BIT-b);
  rn_clamp(c);
}

void rn_mul(rni *A, rni *B, rni *C)
{
#if RN_SIZ >= 48
  int yy;
#endif
  int y, ou=C->u;
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
#if defined(RN_MUL6) && RN_SIZ >= 12
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
    rn_mul_combasmall(A, B, C);
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
  int x, ou = b->u;
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
  rn_cpy(a,c);
  if (b >= DGT_BIT)
    rn_lshd(c, b/DGT_BIT);
  b %= DGT_BIT;
  if (b != 0) {
    rnd carry=0, carrytmp, shift=DGT_BIT-b;
    int x;
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
  int x, ou=c->u;
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
  *size = 0;
  if (radix<2 || radix>64)
    return VAL;
  if (iszero(a) == 1) {
    *size = 2;
    return OK;
  }
  rni t;
  initcpy(&t, a);
  if (t.s == RNEG) {
    (*size)++;
    t.s == ZPOS;
  }
  rnd d;
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
  if (maxlen<2 || radix<2 || radix>64)
    return VAL;
  if (iszero(a) == RNY) {
    *str++ = '0';
    *str = '\0';
  }
  rni t;
  initcpy(&t, a);
  char *_s = str;
  if (t.s == RNEG) {
    ++_s;
    *str++ = '-';
    t.s = ZPOS;
    --maxlen;
  }
  rnd d;
  int dgt = 0;
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
  zero(a);
  if (dgt <= 0)
    return;
  rnd d;
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
  rni u, v, r;
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
  *res = RNN;

  if (rn_cmpd(b,1) != RN_GT)
    return;
  rni n1, y, r;
  initcpy(&n1, a);
  rn_subd(&n1, 1, &n1);

  initcpy(&r, &n1);
  int s=rn_cntlsb(&r), j;
  rn_div2d(&r, s, &r, NULL);
  init(&y);
  rn_exptmod(b, &r, a, &y);

  if (rn_cmpd(&y,1)!=RN_EQ && rn_cmp(&y,&n1)!=RN_EQ) {
    j = 1;
    while ((j<=(s-1)) && rn_cmp(&y,&n1)!=RN_EQ) {
      rn_sqrmod(&y, a, &y);
      if (rn_cmpd(&y,1) == RN_EQ)
        return;
      ++j;
    }
    if (rn_cmp(&y,&n1) != RN_EQ)
      return;
  }
  *res = RNY;
}

int rn_isprime(rni *a, int t)
{
  if (t<=0 || t>PR_SIZ)
    return RNN;
  rnd d;
  int r, res;
  for (r=0; r<256; ++r) {
    rn_modd(a, primes[r], &d);
    if (d == 0)
      return RNN;
  }
  rni b;
  init(&b);
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

  if (flags & PR_2MSB_ON)
    maskOR_msb |= 1<<((size-2)&7);
  else if (flags & PR_2MSB_OFF)
    maskAND &= ~(1<<((size-2)&7));

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

#ifdef RN_TIMING_RESISTANT
/* timing resistant montgomery ladder based expmod

   Based on work by Marc Joye, Sung-Ming Yen, "The Montgomery Powering Ladder",
   Cryptographic Hardware and Embedded Systems, CHES 2002 */
static int _rn_expmod(rni *G, rni *X, rni *P, rni *Y)
{
  rnd buf, mp;
  int err, bitcnt, digidx, y;

  if ((err=rn_mont_setup(P, &mp)) != OK)
    return err;
  rni R[2];
  init(&R[0]);
  init(&R[1]);

  rn_mont_calc_norm(&R[0], P);
  if (rn_cmp_mag(P,G) != RN_GT)
    rn_mod(G, P, &R[1]);
  else
    rn_cpy(G, &R[1]);
  rn_mulmod(&R[1], &R[0], P, &R[1]);

  bitcnt = 1;
  buf = 0;
  digidx = X->u-1;

  for (;;) {
    if (--bitcnt == 0) {
      if (digidx == -1)
        break;
      buf = X->dp[digidx--];
      bitcnt = (int)DGT_BIT;
    }
    y = (rnd)(buf>>(DGT_BIT-1))&1;
    buf <<= (rnd)1;

    rn_mul(&R[0], &R[1], &R[y^1]);
    rn_mont_reduce(&R[y^1], P, mp);
    rn_sqr(&R[y], &R[y]);
    rn_mont_reduce(&R[y], P, mp);
  }
  rn_mont_reduce(&R[0], P, mp);
  rn_cpy(&R[0], Y);
  return OK;
}
#else
/* y = g**x (mod b)
   Some restrictions... x must be positive and < b */
static int _rn_expmod(rni *G, rni *X, rni *P, rni *Y)
{
  int err, bitbuf, bitcpy, bitcnt, mode, digidx, y, winsize,
      x=rn_cntbit(X);
  if (x <= 21)
    winsize = 1;
  else if (x <= 36)
    winsize = 3;
  else if (x <= 140)
    winsize = 4;
  else if (x <= 450)
    winsize = 5;
  else
    winsize = 6;
  rni M[64], res;
  rnd buf, mp;
  memset(M, 0, sizeof(M));
  if ((err=rn_mont_setup(P,&mp)) != OK)
    return err;
  init(&res);
  rn_mont_calc_norm(&res, P);
  if (rn_cmp_mag(P, G) != RN_GT)
    rn_mod(G, P, &M[1]);
  else
    rn_cpy(G, &M[1]);
  rn_mulmod(&M[1], &res, P, &M[1]);
  rn_cpy(&M[1], &M[1<<(winsize-1)]);
  for (x=0; x<(winsize-1); ++x) {
    rn_sqr(&M[1<<(winsize-1)], &M[1<<(winsize-1)]);
    rn_mont_reduce(&M[1<<(winsize-1)], P, mp);
  }
  for (x=(1<<(winsize-1))+1; x<(1<<winsize); ++x) {
    rn_mul(&M[x-1], &M[1], &M[x]);
    rn_mont_reduce(&M[x], P, mp);
  }
  buf = 0;
  mode = 0;
  bitcnt = 1;
  digidx = X->u-1;
  bitcpy = bitbuf = 0;
  for (;;) {
    if (--bitcnt == 0) {
      if (digidx == -1)
        break;
      buf = X->dp[digidx--];
      bitcnt = (int)DGT_BIT;
    }
    y = (rnd)(buf>>(DGT_BIT-1))&1;
    buf <<= (rnd)1;
    if (mode==0 && y==0)
      continue;
    if (mode==1 && y==0) {
      rn_sqr(&res, &res);
      rn_mont_reduce(&res, P, mp);
      continue;
    }
    bitbuf |= (y<<(winsize - ++bitcpy));
    mode = 2;
    if (bitcpy == winsize) {
      for (x=0; x<winsize; ++x) {
        rn_sqr(&res, &res);
        rn_mont_reduce(&res, P, mp);
      }
      rn_mul(&res, &M[bitbuf], &res);
      rn_mont_reduce(&res, P, mp);
      bitcpy = bitbuf = 0;
      mode = 1;
    }
  }
  if (mode==2 && bitcpy>0) {
    for (x=0; x<bitcpy; ++x) {
      rn_sqr(&res, &res);
      rn_mont_reduce(&res, P, mp);
      bitbuf <<= 1;
      if ((bitbuf&(1<<winsize)) != 0) {
        rn_mul(&res, &M[1], &res);
        rn_mont_reduce(&res, P, mp);
      }
    }
  }
  rn_mont_reduce(&res, P, mp);
  rn_cpy(&res, Y);
  return OK;
}
#endif

int rn_expmod(rni *G, rni *X, rni *P, rni *Y)
{
#ifdef RN_CHK
  if (P->u > (RN_SIZ/2))
    return VAL;
#endif
  if (X->s == RNEG) {
    int err;
    rni tmp;
    rn_cpy(G, &tmp);
    if ((err=rn_invmod(&tmp,P,&tmp)) != OK)
      return err;
    X->s = ZPOS;
    err = _rn_expmod(&tmp, X, P, Y);
    if (X != Y)
      X->s = RNEG;
    return err;
  } else
    return _rn_expmod(G, X, P, Y);
}

void rn_sqr(rni *A, rni *B)
{
  int y, ou=B->u;
  if (A->u+A->u > RN_SIZ) {
    rn_sqr_comba(A, B);
    goto clean;
  }
  y = A->u;
#if defined(RN_SQR3) && RN_SIZ >= 6
  if (y <= 3) {
    rn_sqr_comba3(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR4) && RN_SIZ >= 8
  if (y == 4) {
    rn_sqr_comba4(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR6) && RN_SIZ >= 12
  if (y <= 6) {
    rn_sqr_comba6(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR7) && RN_SIZ >= 14
  if (y == 7) {
    rn_sqr_comba7(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR8) && RN_SIZ >= 16
  if (y == 8) {
    rn_sqr_comba8(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR9) && RN_SIZ >= 18
  if (y == 9) {
    rn_sqr_comba9(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR12) && RN_SIZ >= 24
  if (y <= 12) {
    rn_sqr_comba12(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR17) && RN_SIZ >= 34
  if (y <= 17) {
    rn_sqr_comba17(A, B);
    goto clean;
  }
#endif
#if defined(RN_SMALL_SET)
  if (y <= 16) {
    rn_sqr_combasmall(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR20) && RN_SIZ >= 40
  if (y <= 20) {
    rn_sqr_comba20(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR24) && RN_SIZ >= 48
  if (y <= 24) {
    rn_sqr_comba24(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR28) && RN_SIZ >= 56
  if (y <= 28) {
    rn_sqr_comba28(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR32) && RN_SIZ >= 64
  if (y <= 32) {
    rn_sqr_comba32(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR48) && RN_SIZ >= 96
  if (y <= 48) {
    rn_sqr_comba48(A, B);
    goto clean;
  }
#endif
#if defined(RN_SQR64) && RN_SIZ >= 128
  if (y <= 64) {
    rn_sqr_comba64(A, B);
    goto clean;
  }
#endif
  rn_sqr_comba(A, B);
clean:
  for (y=B->u; y<ou; ++y)
    B->dp[y] = 0;
}

int rn_sqrmod(rni *a, rni *b, rni *c)
{
  rni tmp;
  zero(&tmp);
  rn_sqr(a, &tmp);
  return rn_mod(&tmp, b, c);
}

#define RN_DEFINES
#include "sqr/rn_sqr_comba.c"

void rn_sqr_comba(rni *A, rni *B)
{
  int pa, ix, iz;
  rnd c0, c1, c2;
  rni tmp, *dst;
#ifdef RN_ISO
  rnw tt;
#endif
  pa = A->u+A->u;
  if (pa >= RN_SIZ)
    pa = RN_SIZ-1;

  COMBA_START;
  CLR_CARRY;
  if (A == B) {
    zero(&tmp);
    dst = &tmp;
  } else {
    zero(B);
    dst = B;
  }
  for (ix=0; ix<pa; ++ix) {
    int tx, ty, iy;
    rnd *tmpy, *tmpx;

    ty = MIN(A->u-1, ix);
    tx = ix-ty;
    tmpx = A->dp+tx;
    tmpy = A->dp+ty;
    iy = MIN(A->u-tx, ty+1);
    iy = MIN(iy, (ty-tx+1)>>1);
    CARRY_FOW;
    for (iz=0; iz<iy; ++iz) {
      rnd _tmpx = *tmpx++;
      rnd _tmpy = *tmpy--;
      SQRADD2(_tmpx, _tmpy);
    }
    if ((ix&1) == 0) {
      rnd _a_dp = A->dp[ix>>1];
      SQRADD(_a_dp, A->dp[ix>>1]);
    }
    COMBA_STO(dst->dp[ix]);
  }
  COMBA_FIN;
  dst->u = pa;
  rn_clamp(dst);
  if (dst != B)
    rn_cpy(dst, B);
}
#undef RN_DEFINES

static int rn_invmod_slow(rni *a, rni *b, rni *c)
{
  rni x, y, u, v, A, B, C, D;
  int res;
  if (b->s==RNEG || iszero(b)==1)
    return VAL;
  init(&x);
  init(&y);
  init(&u);
  init(&v);
  init(&A);
  init(&B);
  init(&C);
  init(&D);
  if ((res=rn_mod(a,b,&x)) != OK)
    return res;
  rn_cpy(b, &y);
  if (iseven(&x)==1 && iseven(&y)==1)
    return VAL;
  rn_cpy(&x, &u);
  rn_cpy(&y, &v);
  rn_set(&A, 1);
  rn_set(&D, 1);
top:
  while (iseven(&u) == 1) {
    rn_div2(&u, &u);
    if (isodd(&A)==1 || isodd(&B)==1) {
      rn_add(&A, &y, &A);
      rn_sub(&B, &x, &B);
    }
    rn_div2(&A, &A);
    rn_div2(&B, &B);
  }
  while (iseven(&v) == 1) {
    rn_div2(&v, &v);
    if (isodd(&C)==1 || isodd(&D)==1) {
      rn_add(&C, &y, &C);
      rn_sub(&D, &x, &D);
    }
    rn_div2(&C, &C);
    rn_div2(&D, &D);
  }
  if (rn_cmp(&u,&v) != RN_LT) {
    rn_sub(&u, &v, &u);
    rn_sub(&A, &C, &A);
    rn_sub(&B, &D, &B);
  } else {
    rn_sub(&v, &u, &v);
    rn_sub(&C, &A, &C);
    rn_sub(&D, &B, &D);
  }
  if (iszero(&u) == 0)
    goto top;
  if (rn_cmpd(&v,1) != RN_EQ)
    return VAL;
  while (rn_cmpd(&C,0) == RN_LT)
    rn_add(&C, b, &C);
  while (rn_cmp_mag(&C,b) != RN_LT)
    rn_sub(&C, b, &C);
  rn_cpy(&C, c);
  return OK;
}

/* c = 1/a (mod b) for odd b only */
int rn_invmod(rni *a, rni *b, rni *c)
{
  rni x, y, u, v, B, D;
  int neg;
  if (iseven(b) == RNY)
    return rn_invmod_slow(a, b, c);
  init(&x);
  init(&y);
  init(&u);
  init(&v);
  init(&B);
  init(&D);
  rn_cpy(b, &x);
  rn_abs(a, &y);
  rn_cpy(&x, &u);
  rn_cpy(&y, &v);
  rn_set(&D, 1);
top:
  while (iseven(&u) == RNY) {
    rn_div2(&u, &u);
    if (isodd(&B) == RNY)
      rn_sub(&B, &x, &B);
    rn_div2(&B, &B);
  }
  while (iseven(&v) == RNY) {
    rn_div2(&v, &v);
    if (isodd(&D) == RNY)
      rn_sub(&D, &x, &D);
    rn_div2(&D, &D);
  }
  if (rn_cmp(&u, &v) != RN_LT) {
    rn_sub(&u, &v, &u);
    rn_sub(&B, &D, &B);
  } else {
    rn_sub(&v, &u, &v);
    rn_sub(&D, &B, &D);
  }
  if (iszero(&u) == RNN)
    goto top;
  if (rn_cmpd(&v, 1) != RN_EQ)
    return VAL;
  neg = a->s;
  while (D.s == RNEG)
    rn_add(&D, b, &D);
  rn_cpy(&D, c);
  c->s = neg;
  return OK;
}

