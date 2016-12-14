/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

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
   inputs are not close to the next power of two. That is, for example,
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
  int x, ou=b->u;
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

