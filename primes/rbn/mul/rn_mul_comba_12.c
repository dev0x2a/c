#define RN_DEFINES
#include "rn_mul_comba.c"
#if defined(RN_MUL12) && RN_SIZ >= 24
void rn_mul_comba12(rni *A, rni *B, rni *C)
{
  rnd c0, c1, c2, at[24];
  memcpy(at, A->dp, 12*sizeof(rnd));
  memcpy(at+12, B->dp, 12*sizeof(rnd));
  COMBA_START;
  COMBA_CLR;
  /* 0 */
  MULADD(at[0], at[12]);
  COMBA_STO(C->dp[0]);
  /* 1 */
  COMBA_FOW;
  MULADD(at[0], at[13]);
  MULADD(at[1], at[12]);
  COMBA_STO(C->dp[1]);
  /* 2 */
  COMBA_FOW;
  MULADD(at[0], at[14]);
  MULADD(at[1], at[13]);
  MULADD(at[2], at[12]);
  COMBA_STO(C->dp[2]);
  /* 3 */
  COMBA_FOW;
  MULADD(at[0], at[15]);
  MULADD(at[1], at[14]);
  MULADD(at[2], at[13]);
  MULADD(at[3], at[12]);
  COMBA_STO(C->dp[3]);
  /* 4 */
  COMBA_FOW;
  MULADD(at[0], at[16]);
  MULADD(at[1], at[15]);
  MULADD(at[2], at[14]);
  MULADD(at[3], at[13]);
  MULADD(at[4], at[12]);
  COMBA_STO(C->dp[4]);
  /* 5 */
  COMBA_FOW;
  MULADD(at[0], at[17]);
  MULADD(at[1], at[16]);
  MULADD(at[2], at[15]);
  MULADD(at[3], at[14]);
  MULADD(at[4], at[13]);
  MULADD(at[5], at[12]);
  COMBA_STO(C->dp[5]);
  /* 6 */
  COMBA_FOW;
  MULADD(at[0], at[18]);
  MULADD(at[1], at[17]);
  MULADD(at[2], at[16]);
  MULADD(at[3], at[15]);
  MULADD(at[4], at[14]);
  MULADD(at[5], at[13]);
  MULADD(at[6], at[12]);
  COMBA_STO(C->dp[6]);
  /* 7 */
  COMBA_FOW;
  MULADD(at[0], at[19]);
  MULADD(at[1], at[18]);
  MULADD(at[2], at[17]);
  MULADD(at[3], at[16]);
  MULADD(at[4], at[15]);
  MULADD(at[5], at[14]);
  MULADD(at[6], at[13]);
  MULADD(at[7], at[12]);
  COMBA_STO(C->dp[7]);
  /* 8 */
  COMBA_FOW;
  MULADD(at[0], at[20]);
  MULADD(at[1], at[19]);
  MULADD(at[2], at[18]);
  MULADD(at[3], at[17]);
  MULADD(at[4], at[16]);
  MULADD(at[5], at[15]);
  MULADD(at[6], at[14]);
  MULADD(at[7], at[13]);
  MULADD(at[8], at[12]);
  COMBA_STO(C->dp[8]);
  /* 9 */
  COMBA_FOW;
  MULADD(at[0], at[21]);
  MULADD(at[1], at[20]);
  MULADD(at[2], at[19]);
  MULADD(at[3], at[18]);
  MULADD(at[4], at[17]);
  MULADD(at[5], at[16]);
  MULADD(at[6], at[15]);
  MULADD(at[7], at[14]);
  MULADD(at[8], at[13]);
  MULADD(at[9], at[12]);
  COMBA_STO(C->dp[9]);
  /* 10 */
  COMBA_FOW;
  MULADD(at[0], at[22]);
  MULADD(at[1], at[21]);
  MULADD(at[2], at[20]);
  MULADD(at[3], at[19]);
  MULADD(at[4], at[18]);
  MULADD(at[5], at[17]);
  MULADD(at[6], at[16]);
  MULADD(at[7], at[15]);
  MULADD(at[8], at[14]);
  MULADD(at[9], at[13]);
  MULADD(at[10], at[12]);
  COMBA_STO(C->dp[10]);
  /* 11 */
  COMBA_FOW;
  MULADD(at[0], at[23]);
  MULADD(at[1], at[22]);
  MULADD(at[2], at[21]);
  MULADD(at[3], at[20]);
  MULADD(at[4], at[19]);
  MULADD(at[5], at[18]);
  MULADD(at[6], at[17]);
  MULADD(at[7], at[16]);
  MULADD(at[8], at[15]);
  MULADD(at[9], at[14]);
  MULADD(at[10], at[13]);
  MULADD(at[11], at[12]);
  COMBA_STO(C->dp[11]);
  /* 12 */
  COMBA_FOW;
  MULADD(at[1], at[23]);
  MULADD(at[2], at[22]);
  MULADD(at[3], at[21]);
  MULADD(at[4], at[20]);
  MULADD(at[5], at[19]);
  MULADD(at[6], at[18]);
  MULADD(at[7], at[17]);
  MULADD(at[8], at[16]);
  MULADD(at[9], at[15]);
  MULADD(at[10], at[14]);
  MULADD(at[11], at[13]);
  COMBA_STO(C->dp[12]);
  /* 13 */
  COMBA_FOW;
  MULADD(at[2], at[23]);
  MULADD(at[3], at[22]);
  MULADD(at[4], at[21]);
  MULADD(at[5], at[20]);
  MULADD(at[6], at[19]);
  MULADD(at[7], at[18]);
  MULADD(at[8], at[17]);
  MULADD(at[9], at[16]);
  MULADD(at[10], at[15]);
  MULADD(at[11], at[14]);
  COMBA_STO(C->dp[13]);
  /* 14 */
  COMBA_FOW;
  MULADD(at[3], at[23]);
  MULADD(at[4], at[22]);
  MULADD(at[5], at[21]);
  MULADD(at[6], at[20]);
  MULADD(at[7], at[19]);
  MULADD(at[8], at[18]);
  MULADD(at[9], at[17]);
  MULADD(at[10], at[16]);
  MULADD(at[11], at[15]);
  COMBA_STO(C->dp[14]);
  /* 15 */
  COMBA_FOW;
  MULADD(at[4], at[23]);
  MULADD(at[5], at[22]);
  MULADD(at[6], at[21]);
  MULADD(at[7], at[20]);
  MULADD(at[8], at[19]);
  MULADD(at[9], at[18]);
  MULADD(at[10], at[17]);
  MULADD(at[11], at[16]);
  COMBA_STO(C->dp[15]);
  /* 16 */
  COMBA_FOW;
  MULADD(at[5], at[23]);
  MULADD(at[6], at[22]);
  MULADD(at[7], at[21]);
  MULADD(at[8], at[20]);
  MULADD(at[9], at[19]);
  MULADD(at[10], at[18]);
  MULADD(at[11], at[17]);
  COMBA_STO(C->dp[16]);
  /* 17 */
  COMBA_FOW;
  MULADD(at[6], at[23]);
  MULADD(at[7], at[22]);
  MULADD(at[8], at[21]);
  MULADD(at[9], at[20]);
  MULADD(at[10], at[19]);
  MULADD(at[11], at[18]);
  COMBA_STO(C->dp[17]);
  /* 18 */
  COMBA_FOW;
  MULADD(at[7], at[23]);
  MULADD(at[8], at[22]);
  MULADD(at[9], at[21]);
  MULADD(at[10], at[20]);
  MULADD(at[11], at[19]);
  COMBA_STO(C->dp[18]);
  /* 19 */
  COMBA_FOW;
  MULADD(at[8], at[23]);
  MULADD(at[9], at[22]);
  MULADD(at[10], at[21]);
  MULADD(at[11], at[20]);
  COMBA_STO(C->dp[19]);
  /* 20 */
  COMBA_FOW;
  MULADD(at[9], at[23]);
  MULADD(at[10], at[22]);
  MULADD(at[11], at[21]);
  COMBA_STO(C->dp[20]);
  /* 21 */
  COMBA_FOW;
  MULADD(at[10], at[23]);
  MULADD(at[11], at[22]);
  COMBA_STO(C->dp[21]);
  /* 22 */
  COMBA_FOW;
  MULADD(at[11], at[23]);
  COMBA_STO(C->dp[22]);
  COMBA_STO2(C->dp[23]);
  C->u = 24;
  C->s = A->s^B->s;
  rn_clamp(C);
  COMBA_FIN;
}
#endif

