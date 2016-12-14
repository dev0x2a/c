#define RN_DEFINES
#include "rn_mul_comba.c"
#if defined(RN_MUL3) && RN_SIZ >= 6
void rn_mul_comba3(rni *A, rni *B, rni *C)
{
  rnd c0, c1, c2, at[6];
  memcpy(at, A->dp, 3*sizeof(rnd));
  memcpy(at+3, B->dp, 3*sizeof(rnd));
  COMBA_START;
  COMBA_CLR;
  /* 0 */
  MULADD(at[0], at[3]);
  COMBA_STO(C->dp[0]);
  /* 1 */
  COMBA_FOW;
  MULADD(at[0], at[4]);
  MULADD(at[1], at[3]);
  COMBA_STO(C->dp[1]);
  /* 2 */
  COMBA_FOW;
  MULADD(at[0], at[5]);
  MULADD(at[1], at[4]);
  MULADD(at[2], at[3]);
  COMBA_STO(C->dp[2]);
  /* 3 */
  COMBA_FOW;
  MULADD(at[1], at[5]);
  MULADD(at[2], at[4]);
  COMBA_STO(C->dp[3]);
  /* 4 */
  COMBA_FOW;
  MULADD(at[2], at[5]);
  COMBA_STO(C->dp[4]);
  COMBA_STO2(C->dp[5]);
  C->u = 6;
  C->s = A->s^B->s;
  rn_clamp(C);
  COMBA_FIN;
}
#endif

