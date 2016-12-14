#define RN_DEFINES
#include "rn_mul_comba.c"
#if defined(RN_MUL4) && RN_SIZ >= 8
void rn_mul_comba4(rni *A, rni *B, rni *C)
{
  rnd c0, c1, c2, at[8];
  memcpy(at, A->dp, 4*sizeof(rnd));
  memcpy(at+4, B->dp, 4*sizeof(rnd));
  COMBA_START;
  COMBA_CLR;
  /* 0 */
  MULADD(at[0], at[4]);
  COMBA_STO(C->dp[0]);
  /* 1 */
  COMBA_FOW;
  MULADD(at[0], at[5]);
  MULADD(at[1], at[4]);
  COMBA_STO(C->dp[1]);
  /* 2 */
  COMBA_FOW;
  MULADD(at[0], at[6]);
  MULADD(at[1], at[5]);
  MULADD(at[2], at[4]);
  COMBA_STO(C->dp[2]);
  /* 3 */
  COMBA_FOW;
  MULADD(at[0], at[7]);
  MULADD(at[1], at[6]);
  MULADD(at[2], at[5]);
  MULADD(at[3], at[4]);
  COMBA_STO(C->dp[3]);
  /* 4 */
  COMBA_FOW;
  MULADD(at[1], at[7]);
  MULADD(at[2], at[6]);
  MULADD(at[3], at[5]);
  COMBA_STO(C->dp[4]);
  /* 5 */
  COMBA_FOW;
  MULADD(at[2], at[7]);
  MULADD(at[3], at[6]);
  COMBA_STO(C->dp[5]);
  /* 6 */
  COMBA_FOW;
  MULADD(at[3], at[7]);
  COMBA_STO(C->dp[6]);
  COMBA_STO2(C->dp[7]);
  C->u = 8;
  C->s = A->s^B->s;
  rn_clamp(C);
  COMBA_FIN;
}
#endif

