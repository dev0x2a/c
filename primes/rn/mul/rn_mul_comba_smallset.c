#define RN_DEFINES
#include "rn_mul_comba.c"
#if defined(RN_SMALL_SET)
void rn_mul_combasmall(rni *A, rni *B, rni *C)
{
  rnd c0, c1, c2, at[32];
  switch (MAX(A->u, B->u)) {
  case 1:
    memcpy(at, A->dp, 1*sizeof(rnd));
    memcpy(at+1, B->dp, 1*sizeof(rnd));
    COMBA_START;
    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[1]);
    COMBA_STO(C->dp[0]);
    COMBA_STO2(C->dp[1]);
    C->u = 2;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 2:
    memcpy(at, A->dp, 2*sizeof(rnd));
    memcpy(at+2, B->dp, 2*sizeof(rnd));
    COMBA_START;
    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[2]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[3]);
    MULADD(at[1], at[2]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[1], at[3]);
    COMBA_STO(C->dp[2]);
    COMBA_STO2(C->dp[3]);
    C->u = 4;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 3:
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
    break;

  case 4:
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
    break;

  case 5:
    memcpy(at, A->dp, 5*sizeof(rnd));
    memcpy(at+5, B->dp, 5*sizeof(rnd));
    COMBA_START;
    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[5]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[6]);
    MULADD(at[1], at[5]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[7]);
    MULADD(at[1], at[6]);
    MULADD(at[2], at[5]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[8]);
    MULADD(at[1], at[7]);
    MULADD(at[2], at[6]);
    MULADD(at[3], at[5]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[9]);
    MULADD(at[1], at[8]);
    MULADD(at[2], at[7]);
    MULADD(at[3], at[6]);
    MULADD(at[4], at[5]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[1], at[9]);
    MULADD(at[2], at[8]);
    MULADD(at[3], at[7]);
    MULADD(at[4], at[6]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[2], at[9]);
    MULADD(at[3], at[8]);
    MULADD(at[4], at[7]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[3], at[9]);
    MULADD(at[4], at[8]);
    COMBA_STO(C->dp[7]);
    /* 8 */
    COMBA_FOW;
    MULADD(at[4], at[9]);
    COMBA_STO(C->dp[8]);
    COMBA_STO2(C->dp[9]);
    C->u = 10;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 6:
    memcpy(at, A->dp, 6*sizeof(rnd));
    memcpy(at+6, B->dp, 6*sizeof(rnd));
    COMBA_START;

    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[6]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[7]);
    MULADD(at[1], at[6]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[8]);
    MULADD(at[1], at[7]);
    MULADD(at[2], at[6]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[9]);
    MULADD(at[1], at[8]);
    MULADD(at[2], at[7]);
    MULADD(at[3], at[6]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[10]);
    MULADD(at[1], at[9]);
    MULADD(at[2], at[8]);
    MULADD(at[3], at[7]);
    MULADD(at[4], at[6]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[11]);
    MULADD(at[1], at[10]);
    MULADD(at[2], at[9]);
    MULADD(at[3], at[8]);
    MULADD(at[4], at[7]);
    MULADD(at[5], at[6]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[1], at[11]);
    MULADD(at[2], at[10]);
    MULADD(at[3], at[9]);
    MULADD(at[4], at[8]);
    MULADD(at[5], at[7]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[2], at[11]);
    MULADD(at[3], at[10]);
    MULADD(at[4], at[9]);
    MULADD(at[5], at[8]);
    COMBA_STO(C->dp[7]);
    /* 8 */
    COMBA_FOW;
    MULADD(at[3], at[11]);
    MULADD(at[4], at[10]);
    MULADD(at[5], at[9]);
    COMBA_STO(C->dp[8]);
    /* 9 */
    COMBA_FOW;
    MULADD(at[4], at[11]);
    MULADD(at[5], at[10]);
    COMBA_STO(C->dp[9]);
    /* 10 */
    COMBA_FOW;
    MULADD(at[5], at[11]);
    COMBA_STO(C->dp[10]);
    COMBA_STO2(C->dp[11]);
    C->u = 12;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 7:
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
    break;

  case 8:
    memcpy(at, A->dp, 8*sizeof(rnd));
    memcpy(at+8, B->dp, 8*sizeof(rnd));
    COMBA_START;

    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[8]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[9]);
    MULADD(at[1], at[8]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[10]);
    MULADD(at[1], at[9]);
    MULADD(at[2], at[8]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[11]);
    MULADD(at[1], at[10]);
    MULADD(at[2], at[9]);
    MULADD(at[3], at[8]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[12]);
    MULADD(at[1], at[11]);
    MULADD(at[2], at[10]);
    MULADD(at[3], at[9]);
    MULADD(at[4], at[8]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[13]);
    MULADD(at[1], at[12]);
    MULADD(at[2], at[11]);
    MULADD(at[3], at[10]);
    MULADD(at[4], at[9]);
    MULADD(at[5], at[8]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[0], at[14]);
    MULADD(at[1], at[13]);
    MULADD(at[2], at[12]);
    MULADD(at[3], at[11]);
    MULADD(at[4], at[10]);
    MULADD(at[5], at[9]);
    MULADD(at[6], at[8]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[0], at[15]);
    MULADD(at[1], at[14]);
    MULADD(at[2], at[13]);
    MULADD(at[3], at[12]);
    MULADD(at[4], at[11]);
    MULADD(at[5], at[10]);
    MULADD(at[6], at[9]);
    MULADD(at[7], at[8]);
    COMBA_STO(C->dp[7]);
    /* 8 */
    COMBA_FOW;
    MULADD(at[1], at[15]);
    MULADD(at[2], at[14]);
    MULADD(at[3], at[13]);
    MULADD(at[4], at[12]);
    MULADD(at[5], at[11]);
    MULADD(at[6], at[10]);
    MULADD(at[7], at[9]);
    COMBA_STO(C->dp[8]);
    /* 9 */
    COMBA_FOW;
    MULADD(at[2], at[15]);
    MULADD(at[3], at[14]);
    MULADD(at[4], at[13]);
    MULADD(at[5], at[12]);
    MULADD(at[6], at[11]);
    MULADD(at[7], at[10]);
    COMBA_STO(C->dp[9]);
    /* 10 */
    COMBA_FOW;
    MULADD(at[3], at[15]);
    MULADD(at[4], at[14]);
    MULADD(at[5], at[13]);
    MULADD(at[6], at[12]);
    MULADD(at[7], at[11]);
    COMBA_STO(C->dp[10]);
    /* 11 */
    COMBA_FOW;
    MULADD(at[4], at[15]);
    MULADD(at[5], at[14]);
    MULADD(at[6], at[13]);
    MULADD(at[7], at[12]);
    COMBA_STO(C->dp[11]);
    /* 12 */
    COMBA_FOW;
    MULADD(at[5], at[15]);
    MULADD(at[6], at[14]);
    MULADD(at[7], at[13]);
    COMBA_STO(C->dp[12]);
    /* 13 */
    COMBA_FOW;
    MULADD(at[6], at[15]);
    MULADD(at[7], at[14]);
    COMBA_STO(C->dp[13]);
    /* 14 */
    COMBA_FOW;
    MULADD(at[7], at[15]);
    COMBA_STO(C->dp[14]);
    COMBA_STO2(C->dp[15]);
    C->u = 16;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 9:
    memcpy(at, A->dp, 9*sizeof(rnd));
    memcpy(at+9, B->dp, 9*sizeof(rnd));
    COMBA_START;

    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[9]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[10]);
    MULADD(at[1], at[9]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[11]);
    MULADD(at[1], at[10]);
    MULADD(at[2], at[9]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[12]);
    MULADD(at[1], at[11]);
    MULADD(at[2], at[10]);
    MULADD(at[3], at[9]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[13]);
    MULADD(at[1], at[12]);
    MULADD(at[2], at[11]);
    MULADD(at[3], at[10]);
    MULADD(at[4], at[9]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[14]);
    MULADD(at[1], at[13]);
    MULADD(at[2], at[12]);
    MULADD(at[3], at[11]);
    MULADD(at[4], at[10]);
    MULADD(at[5], at[9]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[0], at[15]);
    MULADD(at[1], at[14]);
    MULADD(at[2], at[13]);
    MULADD(at[3], at[12]);
    MULADD(at[4], at[11]);
    MULADD(at[5], at[10]);
    MULADD(at[6], at[9]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[0], at[16]);
    MULADD(at[1], at[15]);
    MULADD(at[2], at[14]);
    MULADD(at[3], at[13]);
    MULADD(at[4], at[12]);
    MULADD(at[5], at[11]);
    MULADD(at[6], at[10]);
    MULADD(at[7], at[9]);
    COMBA_STO(C->dp[7]);
    /* 8 */
    COMBA_FOW;
    MULADD(at[0], at[17]);
    MULADD(at[1], at[16]);
    MULADD(at[2], at[15]);
    MULADD(at[3], at[14]);
    MULADD(at[4], at[13]);
    MULADD(at[5], at[12]);
    MULADD(at[6], at[11]);
    MULADD(at[7], at[10]);
    MULADD(at[8], at[9]);
    COMBA_STO(C->dp[8]);
    /* 9 */
    COMBA_FOW;
    MULADD(at[1], at[17]);
    MULADD(at[2], at[16]);
    MULADD(at[3], at[15]);
    MULADD(at[4], at[14]);
    MULADD(at[5], at[13]);
    MULADD(at[6], at[12]);
    MULADD(at[7], at[11]);
    MULADD(at[8], at[10]);
    COMBA_STO(C->dp[9]);
    /* 10 */
    COMBA_FOW;
    MULADD(at[2], at[17]);
    MULADD(at[3], at[16]);
    MULADD(at[4], at[15]);
    MULADD(at[5], at[14]);
    MULADD(at[6], at[13]);
    MULADD(at[7], at[12]);
    MULADD(at[8], at[11]);
    COMBA_STO(C->dp[10]);
    /* 11 */
    COMBA_FOW;
    MULADD(at[3], at[17]);
    MULADD(at[4], at[16]);
    MULADD(at[5], at[15]);
    MULADD(at[6], at[14]);
    MULADD(at[7], at[13]);
    MULADD(at[8], at[12]);
    COMBA_STO(C->dp[11]);
    /* 12 */
    COMBA_FOW;
    MULADD(at[4], at[17]);
    MULADD(at[5], at[16]);
    MULADD(at[6], at[15]);
    MULADD(at[7], at[14]);
    MULADD(at[8], at[13]);
    COMBA_STO(C->dp[12]);
    /* 13 */
    COMBA_FOW;
    MULADD(at[5], at[17]);
    MULADD(at[6], at[16]);
    MULADD(at[7], at[15]);
    MULADD(at[8], at[14]);
    COMBA_STO(C->dp[13]);
    /* 14 */
    COMBA_FOW;
    MULADD(at[6], at[17]);
    MULADD(at[7], at[16]);
    MULADD(at[8], at[15]);
    COMBA_STO(C->dp[14]);
    /* 15 */
    COMBA_FOW;
    MULADD(at[7], at[17]);
    MULADD(at[8], at[16]);
    COMBA_STO(C->dp[15]);
    /* 16 */
    COMBA_FOW;
    MULADD(at[8], at[17]);
    COMBA_STO(C->dp[16]);
    COMBA_STO2(C->dp[17]);
    C->u = 18;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 10:
    memcpy(at, A->dp, 10*sizeof(rnd));
    memcpy(at+10, B->dp, 10*sizeof(rnd));
    COMBA_START;

    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[10]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[11]);
    MULADD(at[1], at[10]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[12]);
    MULADD(at[1], at[11]);
    MULADD(at[2], at[10]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[13]);
    MULADD(at[1], at[12]);
    MULADD(at[2], at[11]);
    MULADD(at[3], at[10]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[14]);
    MULADD(at[1], at[13]);
    MULADD(at[2], at[12]);
    MULADD(at[3], at[11]);
    MULADD(at[4], at[10]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[15]);
    MULADD(at[1], at[14]);
    MULADD(at[2], at[13]);
    MULADD(at[3], at[12]);
    MULADD(at[4], at[11]);
    MULADD(at[5], at[10]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[0], at[16]);
    MULADD(at[1], at[15]);
    MULADD(at[2], at[14]);
    MULADD(at[3], at[13]);
    MULADD(at[4], at[12]);
    MULADD(at[5], at[11]);
    MULADD(at[6], at[10]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[0], at[17]);
    MULADD(at[1], at[16]);
    MULADD(at[2], at[15]);
    MULADD(at[3], at[14]);
    MULADD(at[4], at[13]);
    MULADD(at[5], at[12]);
    MULADD(at[6], at[11]);
    MULADD(at[7], at[10]);
    COMBA_STO(C->dp[7]);
    /* 8 */
    COMBA_FOW;
    MULADD(at[0], at[18]);
    MULADD(at[1], at[17]);
    MULADD(at[2], at[16]);
    MULADD(at[3], at[15]);
    MULADD(at[4], at[14]);
    MULADD(at[5], at[13]);
    MULADD(at[6], at[12]);
    MULADD(at[7], at[11]);
    MULADD(at[8], at[10]);
    COMBA_STO(C->dp[8]);
    /* 9 */
    COMBA_FOW;
    MULADD(at[0], at[19]);
    MULADD(at[1], at[18]);
    MULADD(at[2], at[17]);
    MULADD(at[3], at[16]);
    MULADD(at[4], at[15]);
    MULADD(at[5], at[14]);
    MULADD(at[6], at[13]);
    MULADD(at[7], at[12]);
    MULADD(at[8], at[11]);
    MULADD(at[9], at[10]);
    COMBA_STO(C->dp[9]);
    /* 10 */
    COMBA_FOW;
    MULADD(at[1], at[19]);
    MULADD(at[2], at[18]);
    MULADD(at[3], at[17]);
    MULADD(at[4], at[16]);
    MULADD(at[5], at[15]);
    MULADD(at[6], at[14]);
    MULADD(at[7], at[13]);
    MULADD(at[8], at[12]);
    MULADD(at[9], at[11]);
    COMBA_STO(C->dp[10]);
    /* 11 */
    COMBA_FOW;
    MULADD(at[2], at[19]);
    MULADD(at[3], at[18]);
    MULADD(at[4], at[17]);
    MULADD(at[5], at[16]);
    MULADD(at[6], at[15]);
    MULADD(at[7], at[14]);
    MULADD(at[8], at[13]);
    MULADD(at[9], at[12]);
    COMBA_STO(C->dp[11]);
    /* 12 */
    COMBA_FOW;
    MULADD(at[3], at[19]);
    MULADD(at[4], at[18]);
    MULADD(at[5], at[17]);
    MULADD(at[6], at[16]);
    MULADD(at[7], at[15]);
    MULADD(at[8], at[14]);
    MULADD(at[9], at[13]);
    COMBA_STO(C->dp[12]);
    /* 13 */
    COMBA_FOW;
    MULADD(at[4], at[19]);
    MULADD(at[5], at[18]);
    MULADD(at[6], at[17]);
    MULADD(at[7], at[16]);
    MULADD(at[8], at[15]);
    MULADD(at[9], at[14]);
    COMBA_STO(C->dp[13]);
    /* 14 */
    COMBA_FOW;
    MULADD(at[5], at[19]);
    MULADD(at[6], at[18]);
    MULADD(at[7], at[17]);
    MULADD(at[8], at[16]);
    MULADD(at[9], at[15]);
    COMBA_STO(C->dp[14]);
    /* 15 */
    COMBA_FOW;
    MULADD(at[6], at[19]);
    MULADD(at[7], at[18]);
    MULADD(at[8], at[17]);
    MULADD(at[9], at[16]);
    COMBA_STO(C->dp[15]);
    /* 16 */
    COMBA_FOW;
    MULADD(at[7], at[19]);
    MULADD(at[8], at[18]);
    MULADD(at[9], at[17]);
    COMBA_STO(C->dp[16]);
    /* 17 */
    COMBA_FOW;
    MULADD(at[8], at[19]);
    MULADD(at[9], at[18]);
    COMBA_STO(C->dp[17]);
    /* 18 */
    COMBA_FOW;
    MULADD(at[9], at[19]);
    COMBA_STO(C->dp[18]);
    COMBA_STO2(C->dp[19]);
    C->u = 20;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 11:
    memcpy(at, A->dp, 11*sizeof(rnd));
    memcpy(at+11, B->dp, 11*sizeof(rnd));
    COMBA_START;

    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[11]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[12]);
    MULADD(at[1], at[11]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[13]);
    MULADD(at[1], at[12]);
    MULADD(at[2], at[11]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[14]);
    MULADD(at[1], at[13]);
    MULADD(at[2], at[12]);
    MULADD(at[3], at[11]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[15]);
    MULADD(at[1], at[14]);
    MULADD(at[2], at[13]);
    MULADD(at[3], at[12]);
    MULADD(at[4], at[11]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[16]);
    MULADD(at[1], at[15]);
    MULADD(at[2], at[14]);
    MULADD(at[3], at[13]);
    MULADD(at[4], at[12]);
    MULADD(at[5], at[11]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[0], at[17]);
    MULADD(at[1], at[16]);
    MULADD(at[2], at[15]);
    MULADD(at[3], at[14]);
    MULADD(at[4], at[13]);
    MULADD(at[5], at[12]);
    MULADD(at[6], at[11]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[0], at[18]);
    MULADD(at[1], at[17]);
    MULADD(at[2], at[16]);
    MULADD(at[3], at[15]);
    MULADD(at[4], at[14]);
    MULADD(at[5], at[13]);
    MULADD(at[6], at[12]);
    MULADD(at[7], at[11]);
    COMBA_STO(C->dp[7]);
    /* 8 */
    COMBA_FOW;
    MULADD(at[0], at[19]);
    MULADD(at[1], at[18]);
    MULADD(at[2], at[17]);
    MULADD(at[3], at[16]);
    MULADD(at[4], at[15]);
    MULADD(at[5], at[14]);
    MULADD(at[6], at[13]);
    MULADD(at[7], at[12]);
    MULADD(at[8], at[11]);
    COMBA_STO(C->dp[8]);
    /* 9 */
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
    MULADD(at[9], at[11]);
    COMBA_STO(C->dp[9]);
    /* 10 */
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
    MULADD(at[10], at[11]);
    COMBA_STO(C->dp[10]);
    /* 11 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[11]);
    /* 12 */
    COMBA_FOW;
    MULADD(at[2], at[21]);
    MULADD(at[3], at[20]);
    MULADD(at[4], at[19]);
    MULADD(at[5], at[18]);
    MULADD(at[6], at[17]);
    MULADD(at[7], at[16]);
    MULADD(at[8], at[15]);
    MULADD(at[9], at[14]);
    MULADD(at[10], at[13]);
    COMBA_STO(C->dp[12]);
    /* 13 */
    COMBA_FOW;
    MULADD(at[3], at[21]);
    MULADD(at[4], at[20]);
    MULADD(at[5], at[19]);
    MULADD(at[6], at[18]);
    MULADD(at[7], at[17]);
    MULADD(at[8], at[16]);
    MULADD(at[9], at[15]);
    MULADD(at[10], at[14]);
    COMBA_STO(C->dp[13]);
    /* 14 */
    COMBA_FOW;
    MULADD(at[4], at[21]);
    MULADD(at[5], at[20]);
    MULADD(at[6], at[19]);
    MULADD(at[7], at[18]);
    MULADD(at[8], at[17]);
    MULADD(at[9], at[16]);
    MULADD(at[10], at[15]);
    COMBA_STO(C->dp[14]);
    /* 15 */
    COMBA_FOW;
    MULADD(at[5], at[21]);
    MULADD(at[6], at[20]);
    MULADD(at[7], at[19]);
    MULADD(at[8], at[18]);
    MULADD(at[9], at[17]);
    MULADD(at[10], at[16]);
    COMBA_STO(C->dp[15]);
    /* 16 */
    COMBA_FOW;
    MULADD(at[6], at[21]);
    MULADD(at[7], at[20]);
    MULADD(at[8], at[19]);
    MULADD(at[9], at[18]);
    MULADD(at[10], at[17]);
    COMBA_STO(C->dp[16]);
    /* 17 */
    COMBA_FOW;
    MULADD(at[7], at[21]);
    MULADD(at[8], at[20]);
    MULADD(at[9], at[19]);
    MULADD(at[10], at[18]);
    COMBA_STO(C->dp[17]);
    /* 18 */
    COMBA_FOW;
    MULADD(at[8], at[21]);
    MULADD(at[9], at[20]);
    MULADD(at[10], at[19]);
    COMBA_STO(C->dp[18]);
    /* 19 */
    COMBA_FOW;
    MULADD(at[9], at[21]);
    MULADD(at[10], at[20]);
    COMBA_STO(C->dp[19]);
    /* 20 */
    COMBA_FOW;
    MULADD(at[10], at[21]);
    COMBA_STO(C->dp[20]);
    COMBA_STO2(C->dp[21]);
    C->u = 22;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 12:
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
    break;

  case 13:
    memcpy(at, A->dp, 13*sizeof(rnd));
    memcpy(at+13, B->dp, 13*sizeof(rnd));
    COMBA_START;

    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[13]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[14]);
    MULADD(at[1], at[13]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[15]);
    MULADD(at[1], at[14]);
    MULADD(at[2], at[13]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[16]);
    MULADD(at[1], at[15]);
    MULADD(at[2], at[14]);
    MULADD(at[3], at[13]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[17]);
    MULADD(at[1], at[16]);
    MULADD(at[2], at[15]);
    MULADD(at[3], at[14]);
    MULADD(at[4], at[13]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[18]);
    MULADD(at[1], at[17]);
    MULADD(at[2], at[16]);
    MULADD(at[3], at[15]);
    MULADD(at[4], at[14]);
    MULADD(at[5], at[13]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[0], at[19]);
    MULADD(at[1], at[18]);
    MULADD(at[2], at[17]);
    MULADD(at[3], at[16]);
    MULADD(at[4], at[15]);
    MULADD(at[5], at[14]);
    MULADD(at[6], at[13]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[0], at[20]);
    MULADD(at[1], at[19]);
    MULADD(at[2], at[18]);
    MULADD(at[3], at[17]);
    MULADD(at[4], at[16]);
    MULADD(at[5], at[15]);
    MULADD(at[6], at[14]);
    MULADD(at[7], at[13]);
    COMBA_STO(C->dp[7]);
    /* 8 */
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
    COMBA_STO(C->dp[8]);
    /* 9 */
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
    COMBA_STO(C->dp[9]);
    /* 10 */
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
    COMBA_STO(C->dp[10]);
    /* 11 */
    COMBA_FOW;
    MULADD(at[0], at[24]);
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
    COMBA_STO(C->dp[11]);
    /* 12 */
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
    MULADD(at[9], at[16]);
    MULADD(at[10], at[15]);
    MULADD(at[11], at[14]);
    MULADD(at[12], at[13]);
    COMBA_STO(C->dp[12]);
    /* 13 */
    COMBA_FOW;
    MULADD(at[1], at[25]);
    MULADD(at[2], at[24]);
    MULADD(at[3], at[23]);
    MULADD(at[4], at[22]);
    MULADD(at[5], at[21]);
    MULADD(at[6], at[20]);
    MULADD(at[7], at[19]);
    MULADD(at[8], at[18]);
    MULADD(at[9], at[17]);
    MULADD(at[10], at[16]);
    MULADD(at[11], at[15]);
    MULADD(at[12], at[14]);
    COMBA_STO(C->dp[13]);
    /* 14 */
    COMBA_FOW;
    MULADD(at[2], at[25]);
    MULADD(at[3], at[24]);
    MULADD(at[4], at[23]);
    MULADD(at[5], at[22]);
    MULADD(at[6], at[21]);
    MULADD(at[7], at[20]);
    MULADD(at[8], at[19]);
    MULADD(at[9], at[18]);
    MULADD(at[10], at[17]);
    MULADD(at[11], at[16]);
    MULADD(at[12], at[15]);
    COMBA_STO(C->dp[14]);
    /* 15 */
    COMBA_FOW;
    MULADD(at[3], at[25]);
    MULADD(at[4], at[24]);
    MULADD(at[5], at[23]);
    MULADD(at[6], at[22]);
    MULADD(at[7], at[21]);
    MULADD(at[8], at[20]);
    MULADD(at[9], at[19]);
    MULADD(at[10], at[18]);
    MULADD(at[11], at[17]);
    MULADD(at[12], at[16]);
    COMBA_STO(C->dp[15]);
    /* 16 */
    COMBA_FOW;
    MULADD(at[4], at[25]);
    MULADD(at[5], at[24]);
    MULADD(at[6], at[23]);
    MULADD(at[7], at[22]);
    MULADD(at[8], at[21]);
    MULADD(at[9], at[20]);
    MULADD(at[10], at[19]);
    MULADD(at[11], at[18]);
    MULADD(at[12], at[17]);
    COMBA_STO(C->dp[16]);
    /* 17 */
    COMBA_FOW;
    MULADD(at[5], at[25]);
    MULADD(at[6], at[24]);
    MULADD(at[7], at[23]);
    MULADD(at[8], at[22]);
    MULADD(at[9], at[21]);
    MULADD(at[10], at[20]);
    MULADD(at[11], at[19]);
    MULADD(at[12], at[18]);
    COMBA_STO(C->dp[17]);
    /* 18 */
    COMBA_FOW;
    MULADD(at[6], at[25]);
    MULADD(at[7], at[24]);
    MULADD(at[8], at[23]);
    MULADD(at[9], at[22]);
    MULADD(at[10], at[21]);
    MULADD(at[11], at[20]);
    MULADD(at[12], at[19]);
    COMBA_STO(C->dp[18]);
    /* 19 */
    COMBA_FOW;
    MULADD(at[7], at[25]);
    MULADD(at[8], at[24]);
    MULADD(at[9], at[23]);
    MULADD(at[10], at[22]);
    MULADD(at[11], at[21]);
    MULADD(at[12], at[20]);
    COMBA_STO(C->dp[19]);
    /* 20 */
    COMBA_FOW;
    MULADD(at[8], at[25]);
    MULADD(at[9], at[24]);
    MULADD(at[10], at[23]);
    MULADD(at[11], at[22]);
    MULADD(at[12], at[21]);
    COMBA_STO(C->dp[20]);
    /* 21 */
    COMBA_FOW;
    MULADD(at[9], at[25]);
    MULADD(at[10], at[24]);
    MULADD(at[11], at[23]);
    MULADD(at[12], at[22]);
    COMBA_STO(C->dp[21]);
    /* 22 */
    COMBA_FOW;
    MULADD(at[10], at[25]);
    MULADD(at[11], at[24]);
    MULADD(at[12], at[23]);
    COMBA_STO(C->dp[22]);
    /* 23 */
    COMBA_FOW;
    MULADD(at[11], at[25]);
    MULADD(at[12], at[24]);
    COMBA_STO(C->dp[23]);
    /* 24 */
    COMBA_FOW;
    MULADD(at[12], at[25]);
    COMBA_STO(C->dp[24]);
    COMBA_STO2(C->dp[25]);
    C->u = 26;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 14:
    memcpy(at, A->dp, 14*sizeof(rnd));
    memcpy(at+14, B->dp, 14*sizeof(rnd));
    COMBA_START;

    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[14]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[15]);
    MULADD(at[1], at[14]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[16]);
    MULADD(at[1], at[15]);
    MULADD(at[2], at[14]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[17]);
    MULADD(at[1], at[16]);
    MULADD(at[2], at[15]);
    MULADD(at[3], at[14]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[18]);
    MULADD(at[1], at[17]);
    MULADD(at[2], at[16]);
    MULADD(at[3], at[15]);
    MULADD(at[4], at[14]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[19]);
    MULADD(at[1], at[18]);
    MULADD(at[2], at[17]);
    MULADD(at[3], at[16]);
    MULADD(at[4], at[15]);
    MULADD(at[5], at[14]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[0], at[20]);
    MULADD(at[1], at[19]);
    MULADD(at[2], at[18]);
    MULADD(at[3], at[17]);
    MULADD(at[4], at[16]);
    MULADD(at[5], at[15]);
    MULADD(at[6], at[14]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[0], at[21]);
    MULADD(at[1], at[20]);
    MULADD(at[2], at[19]);
    MULADD(at[3], at[18]);
    MULADD(at[4], at[17]);
    MULADD(at[5], at[16]);
    MULADD(at[6], at[15]);
    MULADD(at[7], at[14]);
    COMBA_STO(C->dp[7]);
    /* 8 */
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
    COMBA_STO(C->dp[8]);
    /* 9 */
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
    COMBA_STO(C->dp[9]);
    /* 10 */
    COMBA_FOW;
    MULADD(at[0], at[24]);
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
    COMBA_STO(C->dp[10]);
    /* 11 */
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
    MULADD(at[9], at[16]);
    MULADD(at[10], at[15]);
    MULADD(at[11], at[14]);
    COMBA_STO(C->dp[11]);
    /* 12 */
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
    MULADD(at[10], at[16]);
    MULADD(at[11], at[15]);
    MULADD(at[12], at[14]);
    COMBA_STO(C->dp[12]);
    /* 13 */
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
    MULADD(at[11], at[16]);
    MULADD(at[12], at[15]);
    MULADD(at[13], at[14]);
    COMBA_STO(C->dp[13]);
    /* 14 */
    COMBA_FOW;
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
    MULADD(at[12], at[16]);
    MULADD(at[13], at[15]);
    COMBA_STO(C->dp[14]);
    /* 15 */
    COMBA_FOW;
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
    MULADD(at[13], at[16]);
    COMBA_STO(C->dp[15]);
    /* 16 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[16]);
    /* 17 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[17]);
    /* 18 */
    COMBA_FOW;
    MULADD(at[5], at[27]);
    MULADD(at[6], at[26]);
    MULADD(at[7], at[25]);
    MULADD(at[8], at[24]);
    MULADD(at[9], at[23]);
    MULADD(at[10], at[22]);
    MULADD(at[11], at[21]);
    MULADD(at[12], at[20]);
    MULADD(at[13], at[19]);
    COMBA_STO(C->dp[18]);
    /* 19 */
    COMBA_FOW;
    MULADD(at[6], at[27]);
    MULADD(at[7], at[26]);
    MULADD(at[8], at[25]);
    MULADD(at[9], at[24]);
    MULADD(at[10], at[23]);
    MULADD(at[11], at[22]);
    MULADD(at[12], at[21]);
    MULADD(at[13], at[20]);
    COMBA_STO(C->dp[19]);
    /* 20 */
    COMBA_FOW;
    MULADD(at[7], at[27]);
    MULADD(at[8], at[26]);
    MULADD(at[9], at[25]);
    MULADD(at[10], at[24]);
    MULADD(at[11], at[23]);
    MULADD(at[12], at[22]);
    MULADD(at[13], at[21]);
    COMBA_STO(C->dp[20]);
    /* 21 */
    COMBA_FOW;
    MULADD(at[8], at[27]);
    MULADD(at[9], at[26]);
    MULADD(at[10], at[25]);
    MULADD(at[11], at[24]);
    MULADD(at[12], at[23]);
    MULADD(at[13], at[22]);
    COMBA_STO(C->dp[21]);
    /* 22 */
    COMBA_FOW;
    MULADD(at[9], at[27]);
    MULADD(at[10], at[26]);
    MULADD(at[11], at[25]);
    MULADD(at[12], at[24]);
    MULADD(at[13], at[23]);
    COMBA_STO(C->dp[22]);
    /* 23 */
    COMBA_FOW;
    MULADD(at[10], at[27]);
    MULADD(at[11], at[26]);
    MULADD(at[12], at[25]);
    MULADD(at[13], at[24]);
    COMBA_STO(C->dp[23]);
    /* 24 */
    COMBA_FOW;
    MULADD(at[11], at[27]);
    MULADD(at[12], at[26]);
    MULADD(at[13], at[25]);
    COMBA_STO(C->dp[24]);
    /* 25 */
    COMBA_FOW;
    MULADD(at[12], at[27]);
    MULADD(at[13], at[26]);
    COMBA_STO(C->dp[25]);
    /* 26 */
    COMBA_FOW;
    MULADD(at[13], at[27]);
    COMBA_STO(C->dp[26]);
    COMBA_STO2(C->dp[27]);
    C->u = 28;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 15:
    memcpy(at, A->dp, 15*sizeof(rnd));
    memcpy(at+15, B->dp, 15*sizeof(rnd));
    COMBA_START;

    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[15]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[16]);
    MULADD(at[1], at[15]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[17]);
    MULADD(at[1], at[16]);
    MULADD(at[2], at[15]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[18]);
    MULADD(at[1], at[17]);
    MULADD(at[2], at[16]);
    MULADD(at[3], at[15]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[19]);
    MULADD(at[1], at[18]);
    MULADD(at[2], at[17]);
    MULADD(at[3], at[16]);
    MULADD(at[4], at[15]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[20]);
    MULADD(at[1], at[19]);
    MULADD(at[2], at[18]);
    MULADD(at[3], at[17]);
    MULADD(at[4], at[16]);
    MULADD(at[5], at[15]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[0], at[21]);
    MULADD(at[1], at[20]);
    MULADD(at[2], at[19]);
    MULADD(at[3], at[18]);
    MULADD(at[4], at[17]);
    MULADD(at[5], at[16]);
    MULADD(at[6], at[15]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[0], at[22]);
    MULADD(at[1], at[21]);
    MULADD(at[2], at[20]);
    MULADD(at[3], at[19]);
    MULADD(at[4], at[18]);
    MULADD(at[5], at[17]);
    MULADD(at[6], at[16]);
    MULADD(at[7], at[15]);
    COMBA_STO(C->dp[7]);
    /* 8 */
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
    COMBA_STO(C->dp[8]);
    /* 9 */
    COMBA_FOW;
    MULADD(at[0], at[24]);
    MULADD(at[1], at[23]);
    MULADD(at[2], at[22]);
    MULADD(at[3], at[21]);
    MULADD(at[4], at[20]);
    MULADD(at[5], at[19]);
    MULADD(at[6], at[18]);
    MULADD(at[7], at[17]);
    MULADD(at[8], at[16]);
    MULADD(at[9], at[15]);
    COMBA_STO(C->dp[9]);
    /* 10 */
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
    MULADD(at[9], at[16]);
    MULADD(at[10], at[15]);
    COMBA_STO(C->dp[10]);
    /* 11 */
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
    MULADD(at[10], at[16]);
    MULADD(at[11], at[15]);
    COMBA_STO(C->dp[11]);
    /* 12 */
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
    MULADD(at[11], at[16]);
    MULADD(at[12], at[15]);
    COMBA_STO(C->dp[12]);
    /* 13 */
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
    MULADD(at[12], at[16]);
    MULADD(at[13], at[15]);
    COMBA_STO(C->dp[13]);
    /* 14 */
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
    MULADD(at[13], at[16]);
    MULADD(at[14], at[15]);
    COMBA_STO(C->dp[14]);
    /* 15 */
    COMBA_FOW;
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
    MULADD(at[14], at[16]);
    COMBA_STO(C->dp[15]);
    /* 16 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[16]);
    /* 17 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[17]);
    /* 18 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[18]);
    /* 19 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[19]);
    /* 20 */
    COMBA_FOW;
    MULADD(at[6], at[29]);
    MULADD(at[7], at[28]);
    MULADD(at[8], at[27]);
    MULADD(at[9], at[26]);
    MULADD(at[10], at[25]);
    MULADD(at[11], at[24]);
    MULADD(at[12], at[23]);
    MULADD(at[13], at[22]);
    MULADD(at[14], at[21]);
    COMBA_STO(C->dp[20]);
    /* 21 */
    COMBA_FOW;
    MULADD(at[7], at[29]);
    MULADD(at[8], at[28]);
    MULADD(at[9], at[27]);
    MULADD(at[10], at[26]);
    MULADD(at[11], at[25]);
    MULADD(at[12], at[24]);
    MULADD(at[13], at[23]);
    MULADD(at[14], at[22]);
    COMBA_STO(C->dp[21]);
    /* 22 */
    COMBA_FOW;
    MULADD(at[8], at[29]);
    MULADD(at[9], at[28]);
    MULADD(at[10], at[27]);
    MULADD(at[11], at[26]);
    MULADD(at[12], at[25]);
    MULADD(at[13], at[24]);
    MULADD(at[14], at[23]);
    COMBA_STO(C->dp[22]);
    /* 23 */
    COMBA_FOW;
    MULADD(at[9], at[29]);
    MULADD(at[10], at[28]);
    MULADD(at[11], at[27]);
    MULADD(at[12], at[26]);
    MULADD(at[13], at[25]);
    MULADD(at[14], at[24]);
    COMBA_STO(C->dp[23]);
    /* 24 */
    COMBA_FOW;
    MULADD(at[10], at[29]);
    MULADD(at[11], at[28]);
    MULADD(at[12], at[27]);
    MULADD(at[13], at[26]);
    MULADD(at[14], at[25]);
    COMBA_STO(C->dp[24]);
    /* 25 */
    COMBA_FOW;
    MULADD(at[11], at[29]);
    MULADD(at[12], at[28]);
    MULADD(at[13], at[27]);
    MULADD(at[14], at[26]);
    COMBA_STO(C->dp[25]);
    /* 26 */
    COMBA_FOW;
    MULADD(at[12], at[29]);
    MULADD(at[13], at[28]);
    MULADD(at[14], at[27]);
    COMBA_STO(C->dp[26]);
    /* 27 */
    COMBA_FOW;
    MULADD(at[13], at[29]);
    MULADD(at[14], at[28]);
    COMBA_STO(C->dp[27]);
    /* 28 */
    COMBA_FOW;
    MULADD(at[14], at[29]);
    COMBA_STO(C->dp[28]);
    COMBA_STO2(C->dp[29]);
    C->u = 30;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;

  case 16:
    memcpy(at, A->dp, 16*sizeof(rnd));
    memcpy(at+16, B->dp, 16*sizeof(rnd));
    COMBA_START;
    COMBA_CLR;
    /* 0 */
    MULADD(at[0], at[16]);
    COMBA_STO(C->dp[0]);
    /* 1 */
    COMBA_FOW;
    MULADD(at[0], at[17]);
    MULADD(at[1], at[16]);
    COMBA_STO(C->dp[1]);
    /* 2 */
    COMBA_FOW;
    MULADD(at[0], at[18]);
    MULADD(at[1], at[17]);
    MULADD(at[2], at[16]);
    COMBA_STO(C->dp[2]);
    /* 3 */
    COMBA_FOW;
    MULADD(at[0], at[19]);
    MULADD(at[1], at[18]);
    MULADD(at[2], at[17]);
    MULADD(at[3], at[16]);
    COMBA_STO(C->dp[3]);
    /* 4 */
    COMBA_FOW;
    MULADD(at[0], at[20]);
    MULADD(at[1], at[19]);
    MULADD(at[2], at[18]);
    MULADD(at[3], at[17]);
    MULADD(at[4], at[16]);
    COMBA_STO(C->dp[4]);
    /* 5 */
    COMBA_FOW;
    MULADD(at[0], at[21]);
    MULADD(at[1], at[20]);
    MULADD(at[2], at[19]);
    MULADD(at[3], at[18]);
    MULADD(at[4], at[17]);
    MULADD(at[5], at[16]);
    COMBA_STO(C->dp[5]);
    /* 6 */
    COMBA_FOW;
    MULADD(at[0], at[22]);
    MULADD(at[1], at[21]);
    MULADD(at[2], at[20]);
    MULADD(at[3], at[19]);
    MULADD(at[4], at[18]);
    MULADD(at[5], at[17]);
    MULADD(at[6], at[16]);
    COMBA_STO(C->dp[6]);
    /* 7 */
    COMBA_FOW;
    MULADD(at[0], at[23]);
    MULADD(at[1], at[22]);
    MULADD(at[2], at[21]);
    MULADD(at[3], at[20]);
    MULADD(at[4], at[19]);
    MULADD(at[5], at[18]);
    MULADD(at[6], at[17]);
    MULADD(at[7], at[16]);
    COMBA_STO(C->dp[7]);
    /* 8 */
    COMBA_FOW;
    MULADD(at[0], at[24]);
    MULADD(at[1], at[23]);
    MULADD(at[2], at[22]);
    MULADD(at[3], at[21]);
    MULADD(at[4], at[20]);
    MULADD(at[5], at[19]);
    MULADD(at[6], at[18]);
    MULADD(at[7], at[17]);
    MULADD(at[8], at[16]);
    COMBA_STO(C->dp[8]);
    /* 9 */
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
    MULADD(at[9], at[16]);
    COMBA_STO(C->dp[9]);
    /* 10 */
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
    MULADD(at[10], at[16]);
    COMBA_STO(C->dp[10]);
    /* 11 */
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
    MULADD(at[11], at[16]);
    COMBA_STO(C->dp[11]);
    /* 12 */
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
    MULADD(at[12], at[16]);
    COMBA_STO(C->dp[12]);
    /* 13 */
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
    MULADD(at[13], at[16]);
    COMBA_STO(C->dp[13]);
    /* 14 */
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
    MULADD(at[14], at[16]);
    COMBA_STO(C->dp[14]);
    /* 15 */
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
    MULADD(at[15], at[16]);
    COMBA_STO(C->dp[15]);
    /* 16 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[16]);
    /* 17 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[17]);
    /* 18 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[18]);
    /* 19 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[19]);
    /* 20 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[20]);
    /* 21 */
    COMBA_FOW;
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
    COMBA_STO(C->dp[21]);
    /* 22 */
    COMBA_FOW;
    MULADD(at[7], at[31]);
    MULADD(at[8], at[30]);
    MULADD(at[9], at[29]);
    MULADD(at[10], at[28]);
    MULADD(at[11], at[27]);
    MULADD(at[12], at[26]);
    MULADD(at[13], at[25]);
    MULADD(at[14], at[24]);
    MULADD(at[15], at[23]);
    COMBA_STO(C->dp[22]);
    /* 23 */
    COMBA_FOW;
    MULADD(at[8], at[31]);
    MULADD(at[9], at[30]);
    MULADD(at[10], at[29]);
    MULADD(at[11], at[28]);
    MULADD(at[12], at[27]);
    MULADD(at[13], at[26]);
    MULADD(at[14], at[25]);
    MULADD(at[15], at[24]);
    COMBA_STO(C->dp[23]);
    /* 24 */
    COMBA_FOW;
    MULADD(at[9], at[31]);
    MULADD(at[10], at[30]);
    MULADD(at[11], at[29]);
    MULADD(at[12], at[28]);
    MULADD(at[13], at[27]);
    MULADD(at[14], at[26]);
    MULADD(at[15], at[25]);
    COMBA_STO(C->dp[24]);
    /* 25 */
    COMBA_FOW;
    MULADD(at[10], at[31]);
    MULADD(at[11], at[30]);
    MULADD(at[12], at[29]);
    MULADD(at[13], at[28]);
    MULADD(at[14], at[27]);
    MULADD(at[15], at[26]);
    COMBA_STO(C->dp[25]);
    /* 26 */
    COMBA_FOW;
    MULADD(at[11], at[31]);
    MULADD(at[12], at[30]);
    MULADD(at[13], at[29]);
    MULADD(at[14], at[28]);
    MULADD(at[15], at[27]);
    COMBA_STO(C->dp[26]);
    /* 27 */
    COMBA_FOW;
    MULADD(at[12], at[31]);
    MULADD(at[13], at[30]);
    MULADD(at[14], at[29]);
    MULADD(at[15], at[28]);
    COMBA_STO(C->dp[27]);
    /* 28 */
    COMBA_FOW;
    MULADD(at[13], at[31]);
    MULADD(at[14], at[30]);
    MULADD(at[15], at[29]);
    COMBA_STO(C->dp[28]);
    /* 29 */
    COMBA_FOW;
    MULADD(at[14], at[31]);
    MULADD(at[15], at[30]);
    COMBA_STO(C->dp[29]);
    /* 30 */
    COMBA_FOW;
    MULADD(at[15], at[31]);
    COMBA_STO(C->dp[30]);
    COMBA_STO2(C->dp[31]);
    C->u = 32;
    C->s = A->s^B->s;
    rn_clamp(C);
    COMBA_FIN;
    break;
  }
}
#endif

