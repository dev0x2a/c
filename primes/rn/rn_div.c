/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

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

