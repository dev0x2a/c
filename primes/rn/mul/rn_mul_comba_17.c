#define RN_DEFINES
#include "rn_mul_comba.c"
#if defined(RN_MUL17) && RN_SIZ >= 34
void rn_mul_comba17(rni *A, rni *B, rni *C)
{
  rnd c0, c1, c2, at[34];
  memcpy(at, A->dp, 17*sizeof(rnd));
  memcpy(at+17, B->dp, 17*sizeof(rnd));
  COMBA_START;
  COMBA_CLR;
  /* 0 */
  MULADD(at[0], at[17]);
  COMBA_STO(C->dp[0]);
  /* 1 */
  COMBA_FOW;
  MULADD(at[0], at[18]);
  MULADD(at[1], at[17]);
  COMBA_STO(C->dp[1]);
  /* 2 */
  COMBA_FOW;
  MULADD(at[0], at[19]);
  MULADD(at[1], at[18]);
  MULADD(at[2], at[17]);
  COMBA_STO(C->dp[2]);
  /* 3 */
  COMBA_FOW;
  MULADD(at[0], at[20]);
  MULADD(at[1], at[19]);
  MULADD(at[2], at[18]);
  MULADD(at[3], at[17]);
  COMBA_STO(C->dp[3]);
  /* 4 */
  COMBA_FOW;
  MULADD(at[0], at[21]);
  MULADD(at[1], at[20]);
  MULADD(at[2], at[19]);
  MULADD(at[3], at[18]);
  MULADD(at[4], at[17]);
  COMBA_STO(C->dp[4]);
  /* 5 */
  COMBA_FOW;
  MULADD(at[0], at[22]);
  MULADD(at[1], at[21]);
  MULADD(at[2], at[20]);
  MULADD(at[3], at[19]);
  MULADD(at[4], at[18]);
  MULADD(at[5], at[17]);
  COMBA_STO(C->dp[5]);
  /* 6 */
  COMBA_FOW;
  MULADD(at[0], at[23]);
  MULADD(at[1], at[22]);
  MULADD(at[2], at[21]);
  MULADD(at[3], at[20]);
  MULADD(at[4], at[19]);
  MULADD(at[5], at[18]);
  MULADD(at[6], at[17]);
  COMBA_STO(C->dp[6]);
  /* 7 */
  COMBA_FOW;
  MULADD(at[0], at[24]);
  MULADD(at[1], at[23]);
  MULADD(at[2], at[22]);
  MULADD(at[3], at[21]);
  MULADD(at[4], at[20]);
  MULADD(at[5], at[19]);
  MULADD(at[6], at[18]);
  MULADD(at[7], at[17]);
  COMBA_STO(C->dp[7]);
  /* 8 */
  COMBA_FOW;
  MULADD(at[0], at[25]);
  MULADD(at[1], at[24]);
  MULADD(at[2], at[23]);
  MULADD(at[3], at[22]);
  MULADD(at[4], at[21]);
  MULADD(at[5], at[20]);
  MULADD(at[6], at[19]);
  MULADD(at[7], at[18]);
  MULADD(at[8], at[17]);
  COMBA_STO(C->dp[8]);
  /* 9 */
  COMBA_FOW;
  MULADD(at[0], at[26]);
  MULADD(at[1], at[25]);
  MULADD(at[2], at[24]);
  MULADD(at[3], at[23]);
  MULADD(at[4], at[22]);
  MULADD(at[5], at[21]);
  MULADD(at[6], at[20]);
  MULADD(at[7], at[19]);
  MULADD(at[8], at[18]);
  MULADD(at[9], at[17]);
  COMBA_STO(C->dp[9]);
  /* 10 */
  COMBA_FOW;
  MULADD(at[0], at[27]);
  MULADD(at[1], at[26]);
  MULADD(at[2], at[25]);
  MULADD(at[3], at[24]);
  MULADD(at[4], at[23]);
  MULADD(at[5], at[22]);
  MULADD(at[6], at[21]);
  MULADD(at[7], at[20]);
  MULADD(at[8], at[19]);
  MULADD(at[9], at[18]);
  MULADD(at[10], at[17]);
  COMBA_STO(C->dp[10]);
  /* 11 */
  COMBA_FOW;
  MULADD(at[0], at[28]);
  MULADD(at[1], at[27]);
  MULADD(at[2], at[26]);
  MULADD(at[3], at[25]);
  MULADD(at[4], at[24]);
  MULADD(at[5], at[23]);
  MULADD(at[6], at[22]);
  MULADD(at[7], at[21]);
  MULADD(at[8], at[20]);
  MULADD(at[9], at[19]);
  MULADD(at[10], at[18]);
  MULADD(at[11], at[17]);
  COMBA_STO(C->dp[11]);
  /* 12 */
  COMBA_FOW;
  MULADD(at[0], at[29]);
  MULADD(at[1], at[28]);
  MULADD(at[2], at[27]);
  MULADD(at[3], at[26]);
  MULADD(at[4], at[25]);
  MULADD(at[5], at[24]);
  MULADD(at[6], at[23]);
  MULADD(at[7], at[22]);
  MULADD(at[8], at[21]);
  MULADD(at[9], at[20]);
  MULADD(at[10], at[19]);
  MULADD(at[11], at[18]);
  MULADD(at[12], at[17]);
  COMBA_STO(C->dp[12]);
  /* 13 */
  COMBA_FOW;
  MULADD(at[0], at[30]);
  MULADD(at[1], at[29]);
  MULADD(at[2], at[28]);
  MULADD(at[3], at[27]);
  MULADD(at[4], at[26]);
  MULADD(at[5], at[25]);
  MULADD(at[6], at[24]);
  MULADD(at[7], at[23]);
  MULADD(at[8], at[22]);
  MULADD(at[9], at[21]);
  MULADD(at[10], at[20]);
  MULADD(at[11], at[19]);
  MULADD(at[12], at[18]);
  MULADD(at[13], at[17]);
  COMBA_STO(C->dp[13]);
  /* 14 */
  COMBA_FOW;
  MULADD(at[0], at[31]);
  MULADD(at[1], at[30]);
  MULADD(at[2], at[29]);
  MULADD(at[3], at[28]);
  MULADD(at[4], at[27]);
  MULADD(at[5], at[26]);
  MULADD(at[6], at[25]);
  MULADD(at[7], at[24]);
  MULADD(at[8], at[23]);
  MULADD(at[9], at[22]);
  MULADD(at[10], at[21]);
  MULADD(at[11], at[20]);
  MULADD(at[12], at[19]);
  MULADD(at[13], at[18]);
  MULADD(at[14], at[17]);
  COMBA_STO(C->dp[14]);
  /* 15 */
  COMBA_FOW;
  MULADD(at[0], at[32]);
  MULADD(at[1], at[31]);
  MULADD(at[2], at[30]);
  MULADD(at[3], at[29]);
  MULADD(at[4], at[28]);
  MULADD(at[5], at[27]);
  MULADD(at[6], at[26]);
  MULADD(at[7], at[25]);
  MULADD(at[8], at[24]);
  MULADD(at[9], at[23]);
  MULADD(at[10], at[22]);
  MULADD(at[11], at[21]);
  MULADD(at[12], at[20]);
  MULADD(at[13], at[19]);
  MULADD(at[14], at[18]);
  MULADD(at[15], at[17]);
  COMBA_STO(C->dp[15]);
  /* 16 */
  COMBA_FOW;
  MULADD(at[0], at[33]);
  MULADD(at[1], at[32]);
  MULADD(at[2], at[31]);
  MULADD(at[3], at[30]);
  MULADD(at[4], at[29]);
  MULADD(at[5], at[28]);
  MULADD(at[6], at[27]);
  MULADD(at[7], at[26]);
  MULADD(at[8], at[25]);
  MULADD(at[9], at[24]);
  MULADD(at[10], at[23]);
  MULADD(at[11], at[22]);
  MULADD(at[12], at[21]);
  MULADD(at[13], at[20]);
  MULADD(at[14], at[19]);
  MULADD(at[15], at[18]);
  MULADD(at[16], at[17]);
  COMBA_STO(C->dp[16]);
  /* 17 */
  COMBA_FOW;
  MULADD(at[1], at[33]);
  MULADD(at[2], at[32]);
  MULADD(at[3], at[31]);
  MULADD(at[4], at[30]);
  MULADD(at[5], at[29]);
  MULADD(at[6], at[28]);
  MULADD(at[7], at[27]);
  MULADD(at[8], at[26]);
  MULADD(at[9], at[25]);
  MULADD(at[10], at[24]);
  MULADD(at[11], at[23]);
  MULADD(at[12], at[22]);
  MULADD(at[13], at[21]);
  MULADD(at[14], at[20]);
  MULADD(at[15], at[19]);
  MULADD(at[16], at[18]);
  COMBA_STO(C->dp[17]);
  /* 18 */
  COMBA_FOW;
  MULADD(at[2], at[33]);
  MULADD(at[3], at[32]);
  MULADD(at[4], at[31]);
  MULADD(at[5], at[30]);
  MULADD(at[6], at[29]);
  MULADD(at[7], at[28]);
  MULADD(at[8], at[27]);
  MULADD(at[9], at[26]);
  MULADD(at[10], at[25]);
  MULADD(at[11], at[24]);
  MULADD(at[12], at[23]);
  MULADD(at[13], at[22]);
  MULADD(at[14], at[21]);
  MULADD(at[15], at[20]);
  MULADD(at[16], at[19]);
  COMBA_STO(C->dp[18]);
  /* 19 */
  COMBA_FOW;
  MULADD(at[3], at[33]);
  MULADD(at[4], at[32]);
  MULADD(at[5], at[31]);
  MULADD(at[6], at[30]);
  MULADD(at[7], at[29]);
  MULADD(at[8], at[28]);
  MULADD(at[9], at[27]);
  MULADD(at[10], at[26]);
  MULADD(at[11], at[25]);
  MULADD(at[12], at[24]);
  MULADD(at[13], at[23]);
  MULADD(at[14], at[22]);
  MULADD(at[15], at[21]);
  MULADD(at[16], at[20]);
  COMBA_STO(C->dp[19]);
  /* 20 */
  COMBA_FOW;
  MULADD(at[4], at[33]);
  MULADD(at[5], at[32]);
  MULADD(at[6], at[31]);
  MULADD(at[7], at[30]);
  MULADD(at[8], at[29]);
  MULADD(at[9], at[28]);
  MULADD(at[10], at[27]);
  MULADD(at[11], at[26]);
  MULADD(at[12], at[25]);
  MULADD(at[13], at[24]);
  MULADD(at[14], at[23]);
  MULADD(at[15], at[22]);
  MULADD(at[16], at[21]);
  COMBA_STO(C->dp[20]);
  /* 21 */
  COMBA_FOW;
  MULADD(at[5], at[33]);
  MULADD(at[6], at[32]);
  MULADD(at[7], at[31]);
  MULADD(at[8], at[30]);
  MULADD(at[9], at[29]);
  MULADD(at[10], at[28]);
  MULADD(at[11], at[27]);
  MULADD(at[12], at[26]);
  MULADD(at[13], at[25]);
  MULADD(at[14], at[24]);
  MULADD(at[15], at[23]);
  MULADD(at[16], at[22]);
  COMBA_STO(C->dp[21]);
  /* 22 */
  COMBA_FOW;
  MULADD(at[6], at[33]);
  MULADD(at[7], at[32]);
  MULADD(at[8], at[31]);
  MULADD(at[9], at[30]);
  MULADD(at[10], at[29]);
  MULADD(at[11], at[28]);
  MULADD(at[12], at[27]);
  MULADD(at[13], at[26]);
  MULADD(at[14], at[25]);
  MULADD(at[15], at[24]);
  MULADD(at[16], at[23]);
  COMBA_STO(C->dp[22]);
  /* 23 */
  COMBA_FOW;
  MULADD(at[7], at[33]);
  MULADD(at[8], at[32]);
  MULADD(at[9], at[31]);
  MULADD(at[10], at[30]);
  MULADD(at[11], at[29]);
  MULADD(at[12], at[28]);
  MULADD(at[13], at[27]);
  MULADD(at[14], at[26]);
  MULADD(at[15], at[25]);
  MULADD(at[16], at[24]);
  COMBA_STO(C->dp[23]);
  /* 24 */
  COMBA_FOW;
  MULADD(at[8], at[33]);
  MULADD(at[9], at[32]);
  MULADD(at[10], at[31]);
  MULADD(at[11], at[30]);
  MULADD(at[12], at[29]);
  MULADD(at[13], at[28]);
  MULADD(at[14], at[27]);
  MULADD(at[15], at[26]);
  MULADD(at[16], at[25]);
  COMBA_STO(C->dp[24]);
  /* 25 */
  COMBA_FOW;
  MULADD(at[9], at[33]);
  MULADD(at[10], at[32]);
  MULADD(at[11], at[31]);
  MULADD(at[12], at[30]);
  MULADD(at[13], at[29]);
  MULADD(at[14], at[28]);
  MULADD(at[15], at[27]);
  MULADD(at[16], at[26]);
  COMBA_STO(C->dp[25]);
  /* 26 */
  COMBA_FOW;
  MULADD(at[10], at[33]);
  MULADD(at[11], at[32]);
  MULADD(at[12], at[31]);
  MULADD(at[13], at[30]);
  MULADD(at[14], at[29]);
  MULADD(at[15], at[28]);
  MULADD(at[16], at[27]);
  COMBA_STO(C->dp[26]);
  /* 27 */
  COMBA_FOW;
  MULADD(at[11], at[33]);
  MULADD(at[12], at[32]);
  MULADD(at[13], at[31]);
  MULADD(at[14], at[30]);
  MULADD(at[15], at[29]);
  MULADD(at[16], at[28]);
  COMBA_STO(C->dp[27]);
  /* 28 */
  COMBA_FOW;
  MULADD(at[12], at[33]);
  MULADD(at[13], at[32]);
  MULADD(at[14], at[31]);
  MULADD(at[15], at[30]);
  MULADD(at[16], at[29]);
  COMBA_STO(C->dp[28]);
  /* 29 */
  COMBA_FOW;
  MULADD(at[13], at[33]);
  MULADD(at[14], at[32]);
  MULADD(at[15], at[31]);
  MULADD(at[16], at[30]);
  COMBA_STO(C->dp[29]);
  /* 30 */
  COMBA_FOW;
  MULADD(at[14], at[33]);
  MULADD(at[15], at[32]);
  MULADD(at[16], at[31]);
  COMBA_STO(C->dp[30]);
  /* 31 */
  COMBA_FOW;
  MULADD(at[15], at[33]);
  MULADD(at[16], at[32]);
  COMBA_STO(C->dp[31]);
  /* 32 */
  COMBA_FOW;
  MULADD(at[16], at[33]);
  COMBA_STO(C->dp[32]);
  COMBA_STO2(C->dp[33]);
  C->u = 34;
  C->s = A->s^B->s;
  rn_clamp(C);
  COMBA_FIN;
}
#endif

