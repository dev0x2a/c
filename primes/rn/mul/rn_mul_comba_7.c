#define RN_DEFINES
#include "rn_mul_comba.c"

#if defined(RN_MUL7) && RN_SIZ >= 14
void rn_mul_comba7(rni *A, rni *B, rni *C)
{
  rnd c0, c1, c2, at[14];
  memcpy(at, A->dp, 7*sizeof(rnd));
  memcpy(at+7, B->dp, 7*sizeof(rnd));
  COMBA_START;
  COMBA_CLR;
  /* 0 */
  MULADD(at[0], at[7]);
  COMBA_STO(C->dp[0]);
  /* 1 */
  COMBA_FOW;
  MULADD(at[0], at[8]);
  MULADD(at[1], at[7]);
  COMBA_STO(C->dp[1]);
  /* 2 */
  COMBA_FOW;
  MULADD(at[0], at[9]);
  MULADD(at[1], at[8]);
  MULADD(at[2], at[7]);
  COMBA_STO(C->dp[2]);
  /* 3 */
  COMBA_FOW;
  MULADD(at[0], at[10]);
  MULADD(at[1], at[9]);
  MULADD(at[2], at[8]);
  MULADD(at[3], at[7]);
  COMBA_STO(C->dp[3]);
  /* 4 */
  COMBA_FOW;
  MULADD(at[0], at[11]);
  MULADD(at[1], at[10]);
  MULADD(at[2], at[9]);
  MULADD(at[3], at[8]);
  MULADD(at[4], at[7]);
  COMBA_STO(C->dp[4]);
  /* 5 */
  COMBA_FOW;
  MULADD(at[0], at[12]);
  MULADD(at[1], at[11]);
  MULADD(at[2], at[10]);
  MULADD(at[3], at[9]);
  MULADD(at[4], at[8]);
  MULADD(at[5], at[7]);
  COMBA_STO(C->dp[5]);
  /* 6 */
  COMBA_FOW;
  MULADD(at[0], at[13]);
  MULADD(at[1], at[12]);
  MULADD(at[2], at[11]);
  MULADD(at[3], at[10]);
  MULADD(at[4], at[9]);
  MULADD(at[5], at[8]);
  MULADD(at[6], at[7]);
  COMBA_STO(C->dp[6]);
  /* 7 */
  COMBA_FOW;
  MULADD(at[1], at[13]);
  MULADD(at[2], at[12]);
  MULADD(at[3], at[11]);
  MULADD(at[4], at[10]);
  MULADD(at[5], at[9]);
  MULADD(at[6], at[8]);
  COMBA_STO(C->dp[7]);
  /* 8 */
  COMBA_FOW;
  MULADD(at[2], at[13]);
  MULADD(at[3], at[12]);
  MULADD(at[4], at[11]);
  MULADD(at[5], at[10]);
  MULADD(at[6], at[9]);
  COMBA_STO(C->dp[8]);
  /* 9 */
  COMBA_FOW;
  MULADD(at[3], at[13]);
  MULADD(at[4], at[12]);
  MULADD(at[5], at[11]);
  MULADD(at[6], at[10]);
  COMBA_STO(C->dp[9]);
  /* 10 */
  COMBA_FOW;
  MULADD(at[4], at[13]);
  MULADD(at[5], at[12]);
  MULADD(at[6], at[11]);
  COMBA_STO(C->dp[10]);
  /* 11 */
  COMBA_FOW;
  MULADD(at[5], at[13]);
  MULADD(at[6], at[12]);
  COMBA_STO(C->dp[11]);
  /* 12 */
  COMBA_FOW;
  MULADD(at[6], at[13]);
  COMBA_STO(C->dp[12]);
  COMBA_STO2(C->dp[13]);
  C->u = 14;
  C->s = A->s^B->s;
  rn_clamp(C);
  COMBA_FIN;
}
#endif

