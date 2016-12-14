/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

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

int rn_modd(rni *a, rnd b, rnd *c)
{ return rn_divd(a,b,NULL,c); }

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

int rn_mulmod(rni *a, rni *b, rni *c, rni *d)
{
  rni tmp;
  zero(&tmp);
  rn_mul(a, b, &tmp);
  return rn_mod(&tmp, c, d);
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

  bitcnt=1; buf=0;
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
  if (rn_cmp_mag(P,G) != RN_GT)
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
  buf=0; mode=0; bitcnt=1;
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

int rn_sqrmod(rni *a, rni *b, rni *c)
{
  rni tmp;
  zero(&tmp);
  rn_sqr(a, &tmp);
  return rn_mod(&tmp, b, c);
}
#undef RN_DEFINES

static int rn_invmod_slow(rni *a, rni *b, rni *c)
{
  if (b->s==RNEG || iszero(b)==1)
    return VAL;
  rni x, y, u, v, A, B, C, D;
  init(&x);
  init(&y);
  init(&u);
  init(&v);
  init(&A);
  init(&B);
  init(&C);
  init(&D);
  int res;
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
  if (iseven(b) == RNY)
    return rn_invmod_slow(a, b, c);
  int neg;
  rni x, y, u, v, B, D;
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

