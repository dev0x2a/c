#define RN_DEFINES
#include "rn_mul_comba.c"
#if defined(RN_MUL6) && RN_SIZ >= 12
void rn_mul_comba6(rni *A, rni *B, rni *C)
{
  rnd c0, c1, c2, at[12];
  memcpy(at, A->dp, 6*sizeof(rnd));
  memcpy(at+6, B->dp, 6*sizeof(rnd));
  COMBA_START;
  COMBA_CLR;
  /* 0 */
  MULADD(at[0], at[6]);
  COMBA_STORE(C->dp[0]);
  /* 1 */
  COMBA_FOW;
  MULADD(at[0], at[7]);
  MULADD(at[1], at[6]);
  COMBA_STORE(C->dp[1]);
  /* 2 */
  COMBA_FOW;
  MULADD(at[0], at[8]);
  MULADD(at[1], at[7]);
  MULADD(at[2], at[6]);
  COMBA_STORE(C->dp[2]);
  /* 3 */
  COMBA_FOW;
  MULADD(at[0], at[9]);
  MULADD(at[1], at[8]);
  MULADD(at[2], at[7]);
  MULADD(at[3], at[6]);
  COMBA_STORE(C->dp[3]);
  /* 4 */
  COMBA_FOW;
  MULADD(at[0], at[10]);
  MULADD(at[1], at[9]);
  MULADD(at[2], at[8]);
  MULADD(at[3], at[7]);
  MULADD(at[4], at[6]);
  COMBA_STORE(C->dp[4]);
  /* 5 */
  COMBA_FOW;
  MULADD(at[0], at[11]);
  MULADD(at[1], at[10]);
  MULADD(at[2], at[9]);
  MULADD(at[3], at[8]);
  MULADD(at[4], at[7]);
  MULADD(at[5], at[6]);
  COMBA_STORE(C->dp[5]);
  /* 6 */
  COMBA_FOW;
  MULADD(at[1], at[11]);
  MULADD(at[2], at[10]);
  MULADD(at[3], at[9]);
  MULADD(at[4], at[8]);
  MULADD(at[5], at[7]);
  COMBA_STORE(C->dp[6]);
  /* 7 */
  COMBA_FOW;
  MULADD(at[2], at[11]);
  MULADD(at[3], at[10]);
  MULADD(at[4], at[9]);
  MULADD(at[5], at[8]);
  COMBA_STORE(C->dp[7]);
  /* 8 */
  COMBA_FOW;
  MULADD(at[3], at[11]);
  MULADD(at[4], at[10]);
  MULADD(at[5], at[9]);
  COMBA_STORE(C->dp[8]);
  /* 9 */
  COMBA_FOW;
  MULADD(at[4], at[11]);
  MULADD(at[5], at[10]);
  COMBA_STORE(C->dp[9]);
  /* 10 */
  COMBA_FOW;
  MULADD(at[5], at[11]);
  COMBA_STORE(C->dp[10]);
  COMBA_STORE2(C->dp[11]);
  C->u = 12;
  C->s = A->s^B->s;
  rn_clamp(C);
  COMBA_FIN;
}
#endif

