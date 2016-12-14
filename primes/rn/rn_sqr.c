/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

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

