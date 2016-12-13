#define RN_DEFINES
#include "rn_sqr_comba.c"

#if defined(RN_SMALL_SET)
void rn_sqr_comba_small(rni *A, rni *B)
{
  rnd *a, b[32], c0, c1, c2, sc0, sc1, sc2;
#ifdef RN_ISO
  rnw tt;
#endif
  switch (A->u) {
  case 1:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);
    COMBA_STO2(b[1]);
    COMBA_FIN;

    B->u = 2;
    B->s = ZPOS;
    memcpy(B->dp, b, 2*sizeof(rnd));
    rn_clamp(B);
    break;

  case 2:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);
    COMBA_STO2(b[3]);
    COMBA_FIN;

    B->u = 4;
    B->s = ZPOS;
    memcpy(B->dp, b, 4*sizeof(rnd));
    rn_clamp(B);
    break;

  case 3:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);
    COMBA_STO2(b[5]);
    COMBA_FIN;

    B->u = 6;
    B->s = ZPOS;
    memcpy(B->dp, b, 6*sizeof(rnd));
    rn_clamp(B);
    break;

  case 4:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADD2(a[2], a[3]);
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);
    COMBA_STO2(b[7]);
    COMBA_FIN;

    B->u = 8;
    B->s = ZPOS;
    memcpy(B->dp, b, 8*sizeof(rnd));
    rn_clamp(B);
    break;

  case 5:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADD2(a[1], a[4]);
    SQRADD2(a[2], a[3]);
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADD2(a[2], a[4]);
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADD2(a[3], a[4]);
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);
    COMBA_STO2(b[9]);
    COMBA_FIN;

    B->u = 10;
    B->s = ZPOS;
    memcpy(B->dp, b, 10*sizeof(rnd));
    rn_clamp(B);
    break;

  case 6:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADD2(a[1], a[5]);
    SQRADD2(a[2], a[4]);
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADD2(a[2], a[5]);
    SQRADD2(a[3], a[4]);
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADD2(a[3], a[5]);
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADD2(a[4], a[5]);
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);
    COMBA_STO2(b[11]);
    COMBA_FIN;

    B->u = 12;
    B->s = ZPOS;
    memcpy(B->dp, b, 12*sizeof(rnd));
    rn_clamp(B);
    break;

  case 7:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADD2(a[2], a[6]);
    SQRADD2(a[3], a[5]);
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADD2(a[3], a[6]);
    SQRADD2(a[4], a[5]);
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADD2(a[4], a[6]);
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADD2(a[5], a[6]);
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);
    COMBA_STO2(b[13]);
    COMBA_FIN;

    B->u = 14;
    B->s = ZPOS;
    memcpy(B->dp, b, 14*sizeof(rnd));
    rn_clamp(B);
    break;

  case 8:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADD2(a[3], a[7]);
    SQRADD2(a[4], a[6]);
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADD2(a[4], a[7]);
    SQRADD2(a[5], a[6]);
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADD2(a[5], a[7]);
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADD2(a[6], a[7]);
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);
    COMBA_STO2(b[15]);
    COMBA_FIN;

    B->u = 16;
    B->s = ZPOS;
    memcpy(B->dp, b, 16*sizeof(rnd));
    rn_clamp(B);
    break;

  case 9:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[0], a[8]);
    SQRADDAC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[1], a[8]);
    SQRADDAC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADDSC(a[2], a[8]);
    SQRADDAC(a[3], a[7]);
    SQRADDAC(a[4], a[6]);
    SQRADDDB;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADDSC(a[3], a[8]);
    SQRADDAC(a[4], a[7]);
    SQRADDAC(a[5], a[6]);
    SQRADDDB;
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADD2(a[4], a[8]);
    SQRADD2(a[5], a[7]);
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADD2(a[5], a[8]);
    SQRADD2(a[6], a[7]);
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADD2(a[6], a[8]);
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);

    /* output 15 */
    CARRY_FOW;
    SQRADD2(a[7], a[8]);
    COMBA_STO(b[15]);

    /* output 16 */
    CARRY_FOW;
    SQRADD(a[8], a[8]);
    COMBA_STO(b[16]);
    COMBA_STO2(b[17]);
    COMBA_FIN;

    B->u = 18;
    B->s = ZPOS;
    memcpy(B->dp, b, 18*sizeof(rnd));
    rn_clamp(B);
    break;

  case 10:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[0], a[8]);
    SQRADDAC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[0], a[9]);
    SQRADDAC(a[1], a[8]);
    SQRADDAC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADDSC(a[1], a[9]);
    SQRADDAC(a[2], a[8]);
    SQRADDAC(a[3], a[7]);
    SQRADDAC(a[4], a[6]);
    SQRADDDB;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADDSC(a[2], a[9]);
    SQRADDAC(a[3], a[8]);
    SQRADDAC(a[4], a[7]);
    SQRADDAC(a[5], a[6]);
    SQRADDDB;
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADDSC(a[3], a[9]);
    SQRADDAC(a[4], a[8]);
    SQRADDAC(a[5], a[7]);
    SQRADDDB;
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADDSC(a[4], a[9]);
    SQRADDAC(a[5], a[8]);
    SQRADDAC(a[6], a[7]);
    SQRADDDB;
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADD2(a[5], a[9]);
    SQRADD2(a[6], a[8]);
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);

    /* output 15 */
    CARRY_FOW;
    SQRADD2(a[6], a[9]);
    SQRADD2(a[7], a[8]);
    COMBA_STO(b[15]);

    /* output 16 */
    CARRY_FOW;
    SQRADD2(a[7], a[9]);
    SQRADD(a[8], a[8]);
    COMBA_STO(b[16]);

    /* output 17 */
    CARRY_FOW;
    SQRADD2(a[8], a[9]);
    COMBA_STO(b[17]);

    /* output 18 */
    CARRY_FOW;
    SQRADD(a[9], a[9]);
    COMBA_STO(b[18]);
    COMBA_STO2(b[19]);
    COMBA_FIN;

    B->u = 20;
    B->s = ZPOS;
    memcpy(B->dp, b, 20*sizeof(rnd));
    rn_clamp(B);
    break;

  case 11:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[0], a[8]);
    SQRADDAC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[0], a[9]);
    SQRADDAC(a[1], a[8]);
    SQRADDAC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADDSC(a[0], a[10]);
    SQRADDAC(a[1], a[9]);
    SQRADDAC(a[2], a[8]);
    SQRADDAC(a[3], a[7]);
    SQRADDAC(a[4], a[6]);
    SQRADDDB;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADDSC(a[1], a[10]);
    SQRADDAC(a[2], a[9]);
    SQRADDAC(a[3], a[8]);
    SQRADDAC(a[4], a[7]);
    SQRADDAC(a[5], a[6]);
    SQRADDDB;
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADDSC(a[2], a[10]);
    SQRADDAC(a[3], a[9]);
    SQRADDAC(a[4], a[8]);
    SQRADDAC(a[5], a[7]);
    SQRADDDB;
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADDSC(a[3], a[10]);
    SQRADDAC(a[4], a[9]);
    SQRADDAC(a[5], a[8]);
    SQRADDAC(a[6], a[7]);
    SQRADDDB;
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADDSC(a[4], a[10]);
    SQRADDAC(a[5], a[9]);
    SQRADDAC(a[6], a[8]);
    SQRADDDB;
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);

    /* output 15 */
    CARRY_FOW;
    SQRADDSC(a[5], a[10]);
    SQRADDAC(a[6], a[9]);
    SQRADDAC(a[7], a[8]);
    SQRADDDB;
    COMBA_STO(b[15]);

    /* output 16 */
    CARRY_FOW;
    SQRADD2(a[6], a[10]);
    SQRADD2(a[7], a[9]);
    SQRADD(a[8], a[8]);
    COMBA_STO(b[16]);

    /* output 17 */
    CARRY_FOW;
    SQRADD2(a[7], a[10]);
    SQRADD2(a[8], a[9]);
    COMBA_STO(b[17]);

    /* output 18 */
    CARRY_FOW;
    SQRADD2(a[8], a[10]);
    SQRADD(a[9], a[9]);
    COMBA_STO(b[18]);

    /* output 19 */
    CARRY_FOW;
    SQRADD2(a[9], a[10]);
    COMBA_STO(b[19]);

    /* output 20 */
    CARRY_FOW;
    SQRADD(a[10], a[10]);
    COMBA_STO(b[20]);
    COMBA_STO2(b[21]);
    COMBA_FIN;

    B->u = 22;
    B->s = ZPOS;
    memcpy(B->dp, b, 22*sizeof(rnd));
    rn_clamp(B);
    break;

  case 12:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[0], a[8]);
    SQRADDAC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[0], a[9]);
    SQRADDAC(a[1], a[8]);
    SQRADDAC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADDSC(a[0], a[10]);
    SQRADDAC(a[1], a[9]);
    SQRADDAC(a[2], a[8]);
    SQRADDAC(a[3], a[7]);
    SQRADDAC(a[4], a[6]);
    SQRADDDB;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADDSC(a[0], a[11]);
    SQRADDAC(a[1], a[10]);
    SQRADDAC(a[2], a[9]);
    SQRADDAC(a[3], a[8]);
    SQRADDAC(a[4], a[7]);
    SQRADDAC(a[5], a[6]);
    SQRADDDB;
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADDSC(a[1], a[11]);
    SQRADDAC(a[2], a[10]);
    SQRADDAC(a[3], a[9]);
    SQRADDAC(a[4], a[8]);
    SQRADDAC(a[5], a[7]);
    SQRADDDB;
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADDSC(a[2], a[11]);
    SQRADDAC(a[3], a[10]);
    SQRADDAC(a[4], a[9]);
    SQRADDAC(a[5], a[8]);
    SQRADDAC(a[6], a[7]);
    SQRADDDB;
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADDSC(a[3], a[11]);
    SQRADDAC(a[4], a[10]);
    SQRADDAC(a[5], a[9]);
    SQRADDAC(a[6], a[8]);
    SQRADDDB;
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);

    /* output 15 */
    CARRY_FOW;
    SQRADDSC(a[4], a[11]);
    SQRADDAC(a[5], a[10]);
    SQRADDAC(a[6], a[9]);
    SQRADDAC(a[7], a[8]);
    SQRADDDB;
    COMBA_STO(b[15]);

    /* output 16 */
    CARRY_FOW;
    SQRADDSC(a[5], a[11]);
    SQRADDAC(a[6], a[10]);
    SQRADDAC(a[7], a[9]);
    SQRADDDB;
    SQRADD(a[8], a[8]);
    COMBA_STO(b[16]);

    /* output 17 */
    CARRY_FOW;
    SQRADDSC(a[6], a[11]);
    SQRADDAC(a[7], a[10]);
    SQRADDAC(a[8], a[9]);
    SQRADDDB;
    COMBA_STO(b[17]);

    /* output 18 */
    CARRY_FOW;
    SQRADD2(a[7], a[11]);
    SQRADD2(a[8], a[10]);
    SQRADD(a[9], a[9]);
    COMBA_STO(b[18]);

    /* output 19 */
    CARRY_FOW;
    SQRADD2(a[8], a[11]);
    SQRADD2(a[9], a[10]);
    COMBA_STO(b[19]);

    /* output 20 */
    CARRY_FOW;
    SQRADD2(a[9], a[11]);
    SQRADD(a[10], a[10]);
    COMBA_STO(b[20]);

    /* output 21 */
    CARRY_FOW;
    SQRADD2(a[10], a[11]);
    COMBA_STO(b[21]);

    /* output 22 */
    CARRY_FOW;
    SQRADD(a[11], a[11]);
    COMBA_STO(b[22]);
    COMBA_STO2(b[23]);
    COMBA_FIN;

    B->u = 24;
    B->s = ZPOS;
    memcpy(B->dp, b, 24*sizeof(rnd));
    rn_clamp(B);
    break;

  case 13:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[0], a[8]);
    SQRADDAC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[0], a[9]);
    SQRADDAC(a[1], a[8]);
    SQRADDAC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADDSC(a[0], a[10]);
    SQRADDAC(a[1], a[9]);
    SQRADDAC(a[2], a[8]);
    SQRADDAC(a[3], a[7]);
    SQRADDAC(a[4], a[6]);
    SQRADDDB;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADDSC(a[0], a[11]);
    SQRADDAC(a[1], a[10]);
    SQRADDAC(a[2], a[9]);
    SQRADDAC(a[3], a[8]);
    SQRADDAC(a[4], a[7]);
    SQRADDAC(a[5], a[6]);
    SQRADDDB;
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADDSC(a[0], a[12]);
    SQRADDAC(a[1], a[11]);
    SQRADDAC(a[2], a[10]);
    SQRADDAC(a[3], a[9]);
    SQRADDAC(a[4], a[8]);
    SQRADDAC(a[5], a[7]);
    SQRADDDB;
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADDSC(a[1], a[12]);
    SQRADDAC(a[2], a[11]);
    SQRADDAC(a[3], a[10]);
    SQRADDAC(a[4], a[9]);
    SQRADDAC(a[5], a[8]);
    SQRADDAC(a[6], a[7]);
    SQRADDDB;
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADDSC(a[2], a[12]);
    SQRADDAC(a[3], a[11]);
    SQRADDAC(a[4], a[10]);
    SQRADDAC(a[5], a[9]);
    SQRADDAC(a[6], a[8]);
    SQRADDDB;
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);

    /* output 15 */
    CARRY_FOW;
    SQRADDSC(a[3], a[12]);
    SQRADDAC(a[4], a[11]);
    SQRADDAC(a[5], a[10]);
    SQRADDAC(a[6], a[9]);
    SQRADDAC(a[7], a[8]);
    SQRADDDB;
    COMBA_STO(b[15]);

    /* output 16 */
    CARRY_FOW;
    SQRADDSC(a[4], a[12]);
    SQRADDAC(a[5], a[11]);
    SQRADDAC(a[6], a[10]);
    SQRADDAC(a[7], a[9]);
    SQRADDDB;
    SQRADD(a[8], a[8]);
    COMBA_STO(b[16]);

    /* output 17 */
    CARRY_FOW;
    SQRADDSC(a[5], a[12]);
    SQRADDAC(a[6], a[11]);
    SQRADDAC(a[7], a[10]);
    SQRADDAC(a[8], a[9]);
    SQRADDDB;
    COMBA_STO(b[17]);

    /* output 18 */
    CARRY_FOW;
    SQRADDSC(a[6], a[12]);
    SQRADDAC(a[7], a[11]);
    SQRADDAC(a[8], a[10]);
    SQRADDDB;
    SQRADD(a[9], a[9]);
    COMBA_STO(b[18]);

    /* output 19 */
    CARRY_FOW;
    SQRADDSC(a[7], a[12]);
    SQRADDAC(a[8], a[11]);
    SQRADDAC(a[9], a[10]);
    SQRADDDB;
    COMBA_STO(b[19]);

    /* output 20 */
    CARRY_FOW;
    SQRADD2(a[8], a[12]);
    SQRADD2(a[9], a[11]);
    SQRADD(a[10], a[10]);
    COMBA_STO(b[20]);

    /* output 21 */
    CARRY_FOW;
    SQRADD2(a[9], a[12]);
    SQRADD2(a[10], a[11]);
    COMBA_STO(b[21]);

    /* output 22 */
    CARRY_FOW;
    SQRADD2(a[10], a[12]);
    SQRADD(a[11], a[11]);
    COMBA_STO(b[22]);

    /* output 23 */
    CARRY_FOW;
    SQRADD2(a[11], a[12]);
    COMBA_STO(b[23]);

    /* output 24 */
    CARRY_FOW;
    SQRADD(a[12], a[12]);
    COMBA_STO(b[24]);
    COMBA_STO2(b[25]);
    COMBA_FIN;

    B->u = 26;
    B->s = ZPOS;
    memcpy(B->dp, b, 26*sizeof(rnd));
    rn_clamp(B);
    break;

  case 14:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[0], a[8]);
    SQRADDAC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[0], a[9]);
    SQRADDAC(a[1], a[8]);
    SQRADDAC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADDSC(a[0], a[10]);
    SQRADDAC(a[1], a[9]);
    SQRADDAC(a[2], a[8]);
    SQRADDAC(a[3], a[7]);
    SQRADDAC(a[4], a[6]);
    SQRADDDB;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADDSC(a[0], a[11]);
    SQRADDAC(a[1], a[10]);
    SQRADDAC(a[2], a[9]);
    SQRADDAC(a[3], a[8]);
    SQRADDAC(a[4], a[7]);
    SQRADDAC(a[5], a[6]);
    SQRADDDB;
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADDSC(a[0], a[12]);
    SQRADDAC(a[1], a[11]);
    SQRADDAC(a[2], a[10]);
    SQRADDAC(a[3], a[9]);
    SQRADDAC(a[4], a[8]);
    SQRADDAC(a[5], a[7]);
    SQRADDDB;
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADDSC(a[0], a[13]);
    SQRADDAC(a[1], a[12]);
    SQRADDAC(a[2], a[11]);
    SQRADDAC(a[3], a[10]);
    SQRADDAC(a[4], a[9]);
    SQRADDAC(a[5], a[8]);
    SQRADDAC(a[6], a[7]);
    SQRADDDB;
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADDSC(a[1], a[13]);
    SQRADDAC(a[2], a[12]);
    SQRADDAC(a[3], a[11]);
    SQRADDAC(a[4], a[10]);
    SQRADDAC(a[5], a[9]);
    SQRADDAC(a[6], a[8]);
    SQRADDDB;
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);

    /* output 15 */
    CARRY_FOW;
    SQRADDSC(a[2], a[13]);
    SQRADDAC(a[3], a[12]);
    SQRADDAC(a[4], a[11]);
    SQRADDAC(a[5], a[10]);
    SQRADDAC(a[6], a[9]);
    SQRADDAC(a[7], a[8]);
    SQRADDDB;
    COMBA_STO(b[15]);

    /* output 16 */
    CARRY_FOW;
    SQRADDSC(a[3], a[13]);
    SQRADDAC(a[4], a[12]);
    SQRADDAC(a[5], a[11]);
    SQRADDAC(a[6], a[10]);
    SQRADDAC(a[7], a[9]);
    SQRADDDB;
    SQRADD(a[8], a[8]);
    COMBA_STO(b[16]);

    /* output 17 */
    CARRY_FOW;
    SQRADDSC(a[4], a[13]);
    SQRADDAC(a[5], a[12]);
    SQRADDAC(a[6], a[11]);
    SQRADDAC(a[7], a[10]);
    SQRADDAC(a[8], a[9]);
    SQRADDDB;
    COMBA_STO(b[17]);

    /* output 18 */
    CARRY_FOW;
    SQRADDSC(a[5], a[13]);
    SQRADDAC(a[6], a[12]);
    SQRADDAC(a[7], a[11]);
    SQRADDAC(a[8], a[10]);
    SQRADDDB;
    SQRADD(a[9], a[9]);
    COMBA_STO(b[18]);

    /* output 19 */
    CARRY_FOW;
    SQRADDSC(a[6], a[13]);
    SQRADDAC(a[7], a[12]);
    SQRADDAC(a[8], a[11]);
    SQRADDAC(a[9], a[10]);
    SQRADDDB;
    COMBA_STO(b[19]);

    /* output 20 */
    CARRY_FOW;
    SQRADDSC(a[7], a[13]);
    SQRADDAC(a[8], a[12]);
    SQRADDAC(a[9], a[11]);
    SQRADDDB;
    SQRADD(a[10], a[10]);
    COMBA_STO(b[20]);

    /* output 21 */
    CARRY_FOW;
    SQRADDSC(a[8], a[13]);
    SQRADDAC(a[9], a[12]);
    SQRADDAC(a[10], a[11]);
    SQRADDDB;
    COMBA_STO(b[21]);

    /* output 22 */
    CARRY_FOW;
    SQRADD2(a[9], a[13]);
    SQRADD2(a[10], a[12]);
    SQRADD(a[11], a[11]);
    COMBA_STO(b[22]);

    /* output 23 */
    CARRY_FOW;
    SQRADD2(a[10], a[13]);
    SQRADD2(a[11], a[12]);
    COMBA_STO(b[23]);

    /* output 24 */
    CARRY_FOW;
    SQRADD2(a[11], a[13]);
    SQRADD(a[12], a[12]);
    COMBA_STO(b[24]);

    /* output 25 */
    CARRY_FOW;
    SQRADD2(a[12], a[13]);
    COMBA_STO(b[25]);

    /* output 26 */
    CARRY_FOW;
    SQRADD(a[13], a[13]);
    COMBA_STO(b[26]);
    COMBA_STO2(b[27]);
    COMBA_FIN;

    B->u = 28;
    B->s = ZPOS;
    memcpy(B->dp, b, 28*sizeof(rnd));
    rn_clamp(B);
    break;

  case 15:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[0], a[8]);
    SQRADDAC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[0], a[9]);
    SQRADDAC(a[1], a[8]);
    SQRADDAC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADDSC(a[0], a[10]);
    SQRADDAC(a[1], a[9]);
    SQRADDAC(a[2], a[8]);
    SQRADDAC(a[3], a[7]);
    SQRADDAC(a[4], a[6]);
    SQRADDDB;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADDSC(a[0], a[11]);
    SQRADDAC(a[1], a[10]);
    SQRADDAC(a[2], a[9]);
    SQRADDAC(a[3], a[8]);
    SQRADDAC(a[4], a[7]);
    SQRADDAC(a[5], a[6]);
    SQRADDDB;
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADDSC(a[0], a[12]);
    SQRADDAC(a[1], a[11]);
    SQRADDAC(a[2], a[10]);
    SQRADDAC(a[3], a[9]);
    SQRADDAC(a[4], a[8]);
    SQRADDAC(a[5], a[7]);
    SQRADDDB;
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADDSC(a[0], a[13]);
    SQRADDAC(a[1], a[12]);
    SQRADDAC(a[2], a[11]);
    SQRADDAC(a[3], a[10]);
    SQRADDAC(a[4], a[9]);
    SQRADDAC(a[5], a[8]);
    SQRADDAC(a[6], a[7]);
    SQRADDDB;
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADDSC(a[0], a[14]);
    SQRADDAC(a[1], a[13]);
    SQRADDAC(a[2], a[12]);
    SQRADDAC(a[3], a[11]);
    SQRADDAC(a[4], a[10]);
    SQRADDAC(a[5], a[9]);
    SQRADDAC(a[6], a[8]);
    SQRADDDB;
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);

    /* output 15 */
    CARRY_FOW;
    SQRADDSC(a[1], a[14]);
    SQRADDAC(a[2], a[13]);
    SQRADDAC(a[3], a[12]);
    SQRADDAC(a[4], a[11]);
    SQRADDAC(a[5], a[10]);
    SQRADDAC(a[6], a[9]);
    SQRADDAC(a[7], a[8]);
    SQRADDDB;
    COMBA_STO(b[15]);

    /* output 16 */
    CARRY_FOW;
    SQRADDSC(a[2], a[14]);
    SQRADDAC(a[3], a[13]);
    SQRADDAC(a[4], a[12]);
    SQRADDAC(a[5], a[11]);
    SQRADDAC(a[6], a[10]);
    SQRADDAC(a[7], a[9]);
    SQRADDDB;
    SQRADD(a[8], a[8]);
    COMBA_STO(b[16]);

    /* output 17 */
    CARRY_FOW;
    SQRADDSC(a[3], a[14]);
    SQRADDAC(a[4], a[13]);
    SQRADDAC(a[5], a[12]);
    SQRADDAC(a[6], a[11]);
    SQRADDAC(a[7], a[10]);
    SQRADDAC(a[8], a[9]);
    SQRADDDB;
    COMBA_STO(b[17]);

    /* output 18 */
    CARRY_FOW;
    SQRADDSC(a[4], a[14]);
    SQRADDAC(a[5], a[13]);
    SQRADDAC(a[6], a[12]);
    SQRADDAC(a[7], a[11]);
    SQRADDAC(a[8], a[10]);
    SQRADDDB;
    SQRADD(a[9], a[9]);
    COMBA_STO(b[18]);

    /* output 19 */
    CARRY_FOW;
    SQRADDSC(a[5], a[14]);
    SQRADDAC(a[6], a[13]);
    SQRADDAC(a[7], a[12]);
    SQRADDAC(a[8], a[11]);
    SQRADDAC(a[9], a[10]);
    SQRADDDB;
    COMBA_STO(b[19]);

    /* output 20 */
    CARRY_FOW;
    SQRADDSC(a[6], a[14]);
    SQRADDAC(a[7], a[13]);
    SQRADDAC(a[8], a[12]);
    SQRADDAC(a[9], a[11]);
    SQRADDDB;
    SQRADD(a[10], a[10]);
    COMBA_STO(b[20]);

    /* output 21 */
    CARRY_FOW;
    SQRADDSC(a[7], a[14]);
    SQRADDAC(a[8], a[13]);
    SQRADDAC(a[9], a[12]);
    SQRADDAC(a[10], a[11]);
    SQRADDDB;
    COMBA_STO(b[21]);

    /* output 22 */
    CARRY_FOW;
    SQRADDSC(a[8], a[14]);
    SQRADDAC(a[9], a[13]);
    SQRADDAC(a[10], a[12]);
    SQRADDDB;
    SQRADD(a[11], a[11]);
    COMBA_STO(b[22]);

    /* output 23 */
    CARRY_FOW;
    SQRADDSC(a[9], a[14]);
    SQRADDAC(a[10], a[13]);
    SQRADDAC(a[11], a[12]);
    SQRADDDB;
    COMBA_STO(b[23]);

    /* output 24 */
    CARRY_FOW;
    SQRADD2(a[10], a[14]);
    SQRADD2(a[11], a[13]);
    SQRADD(a[12], a[12]);
    COMBA_STO(b[24]);

    /* output 25 */
    CARRY_FOW;
    SQRADD2(a[11], a[14]);
    SQRADD2(a[12], a[13]);
    COMBA_STO(b[25]);

    /* output 26 */
    CARRY_FOW;
    SQRADD2(a[12], a[14]);
    SQRADD(a[13], a[13]);
    COMBA_STO(b[26]);

    /* output 27 */
    CARRY_FOW;
    SQRADD2(a[13], a[14]);
    COMBA_STO(b[27]);

    /* output 28 */
    CARRY_FOW;
    SQRADD(a[14], a[14]);
    COMBA_STO(b[28]);
    COMBA_STO2(b[29]);
    COMBA_FIN;

    B->u = 30;
    B->s = ZPOS;
    memcpy(B->dp, b, 30*sizeof(rnd));
    rn_clamp(B);
    break;

  case 16:
    a = A->dp;
    COMBA_START;
    CLR_CARRY;

    /* output 0 */
    SQRADD(a[0], a[0]);
    COMBA_STO(b[0]);

    /* output 1 */
    CARRY_FOW;
    SQRADD2(a[0], a[1]);
    COMBA_STO(b[1]);

    /* output 2 */
    CARRY_FOW;
    SQRADD2(a[0], a[2]);
    SQRADD(a[1], a[1]);
    COMBA_STO(b[2]);

    /* output 3 */
    CARRY_FOW;
    SQRADD2(a[0], a[3]);
    SQRADD2(a[1], a[2]);
    COMBA_STO(b[3]);

    /* output 4 */
    CARRY_FOW;
    SQRADD2(a[0], a[4]);
    SQRADD2(a[1], a[3]);
    SQRADD(a[2], a[2]);
    COMBA_STO(b[4]);

    /* output 5 */
    CARRY_FOW;
    SQRADDSC(a[0], a[5]);
    SQRADDAC(a[1], a[4]);
    SQRADDAC(a[2], a[3]);
    SQRADDDB;
    COMBA_STO(b[5]);

    /* output 6 */
    CARRY_FOW;
    SQRADDSC(a[0], a[6]);
    SQRADDAC(a[1], a[5]);
    SQRADDAC(a[2], a[4]);
    SQRADDDB;
    SQRADD(a[3], a[3]);
    COMBA_STO(b[6]);

    /* output 7 */
    CARRY_FOW;
    SQRADDSC(a[0], a[7]);
    SQRADDAC(a[1], a[6]);
    SQRADDAC(a[2], a[5]);
    SQRADDAC(a[3], a[4]);
    SQRADDDB;
    COMBA_STO(b[7]);

    /* output 8 */
    CARRY_FOW;
    SQRADDSC(a[0], a[8]);
    SQRADDAC(a[1], a[7]);
    SQRADDAC(a[2], a[6]);
    SQRADDAC(a[3], a[5]);
    SQRADDDB;
    SQRADD(a[4], a[4]);
    COMBA_STO(b[8]);

    /* output 9 */
    CARRY_FOW;
    SQRADDSC(a[0], a[9]);
    SQRADDAC(a[1], a[8]);
    SQRADDAC(a[2], a[7]);
    SQRADDAC(a[3], a[6]);
    SQRADDAC(a[4], a[5]);
    SQRADDDB;
    COMBA_STO(b[9]);

    /* output 10 */
    CARRY_FOW;
    SQRADDSC(a[0], a[10]);
    SQRADDAC(a[1], a[9]);
    SQRADDAC(a[2], a[8]);
    SQRADDAC(a[3], a[7]);
    SQRADDAC(a[4], a[6]);
    SQRADDDB;
    SQRADD(a[5], a[5]);
    COMBA_STO(b[10]);

    /* output 11 */
    CARRY_FOW;
    SQRADDSC(a[0], a[11]);
    SQRADDAC(a[1], a[10]);
    SQRADDAC(a[2], a[9]);
    SQRADDAC(a[3], a[8]);
    SQRADDAC(a[4], a[7]);
    SQRADDAC(a[5], a[6]);
    SQRADDDB;
    COMBA_STO(b[11]);

    /* output 12 */
    CARRY_FOW;
    SQRADDSC(a[0], a[12]);
    SQRADDAC(a[1], a[11]);
    SQRADDAC(a[2], a[10]);
    SQRADDAC(a[3], a[9]);
    SQRADDAC(a[4], a[8]);
    SQRADDAC(a[5], a[7]);
    SQRADDDB;
    SQRADD(a[6], a[6]);
    COMBA_STO(b[12]);

    /* output 13 */
    CARRY_FOW;
    SQRADDSC(a[0], a[13]);
    SQRADDAC(a[1], a[12]);
    SQRADDAC(a[2], a[11]);
    SQRADDAC(a[3], a[10]);
    SQRADDAC(a[4], a[9]);
    SQRADDAC(a[5], a[8]);
    SQRADDAC(a[6], a[7]);
    SQRADDDB;
    COMBA_STO(b[13]);

    /* output 14 */
    CARRY_FOW;
    SQRADDSC(a[0], a[14]);
    SQRADDAC(a[1], a[13]);
    SQRADDAC(a[2], a[12]);
    SQRADDAC(a[3], a[11]);
    SQRADDAC(a[4], a[10]);
    SQRADDAC(a[5], a[9]);
    SQRADDAC(a[6], a[8]);
    SQRADDDB;
    SQRADD(a[7], a[7]);
    COMBA_STO(b[14]);

    /* output 15 */
    CARRY_FOW;
    SQRADDSC(a[0], a[15]);
    SQRADDAC(a[1], a[14]);
    SQRADDAC(a[2], a[13]);
    SQRADDAC(a[3], a[12]);
    SQRADDAC(a[4], a[11]);
    SQRADDAC(a[5], a[10]);
    SQRADDAC(a[6], a[9]);
    SQRADDAC(a[7], a[8]);
    SQRADDDB;
    COMBA_STO(b[15]);

    /* output 16 */
    CARRY_FOW;
    SQRADDSC(a[1], a[15]);
    SQRADDAC(a[2], a[14]);
    SQRADDAC(a[3], a[13]);
    SQRADDAC(a[4], a[12]);
    SQRADDAC(a[5], a[11]);
    SQRADDAC(a[6], a[10]);
    SQRADDAC(a[7], a[9]);
    SQRADDDB;
    SQRADD(a[8], a[8]);
    COMBA_STO(b[16]);

    /* output 17 */
    CARRY_FOW;
    SQRADDSC(a[2], a[15]);
    SQRADDAC(a[3], a[14]);
    SQRADDAC(a[4], a[13]);
    SQRADDAC(a[5], a[12]);
    SQRADDAC(a[6], a[11]);
    SQRADDAC(a[7], a[10]);
    SQRADDAC(a[8], a[9]);
    SQRADDDB;
    COMBA_STO(b[17]);

    /* output 18 */
    CARRY_FOW;
    SQRADDSC(a[3], a[15]);
    SQRADDAC(a[4], a[14]);
    SQRADDAC(a[5], a[13]);
    SQRADDAC(a[6], a[12]);
    SQRADDAC(a[7], a[11]);
    SQRADDAC(a[8], a[10]);
    SQRADDDB;
    SQRADD(a[9], a[9]);
    COMBA_STO(b[18]);

    /* output 19 */
    CARRY_FOW;
    SQRADDSC(a[4], a[15]);
    SQRADDAC(a[5], a[14]);
    SQRADDAC(a[6], a[13]);
    SQRADDAC(a[7], a[12]);
    SQRADDAC(a[8], a[11]);
    SQRADDAC(a[9], a[10]);
    SQRADDDB;
    COMBA_STO(b[19]);

    /* output 20 */
    CARRY_FOW;
    SQRADDSC(a[5], a[15]);
    SQRADDAC(a[6], a[14]);
    SQRADDAC(a[7], a[13]);
    SQRADDAC(a[8], a[12]);
    SQRADDAC(a[9], a[11]);
    SQRADDDB;
    SQRADD(a[10], a[10]);
    COMBA_STO(b[20]);

    /* output 21 */
    CARRY_FOW;
    SQRADDSC(a[6], a[15]);
    SQRADDAC(a[7], a[14]);
    SQRADDAC(a[8], a[13]);
    SQRADDAC(a[9], a[12]);
    SQRADDAC(a[10], a[11]);
    SQRADDDB;
    COMBA_STO(b[21]);

    /* output 22 */
    CARRY_FOW;
    SQRADDSC(a[7], a[15]);
    SQRADDAC(a[8], a[14]);
    SQRADDAC(a[9], a[13]);
    SQRADDAC(a[10], a[12]);
    SQRADDDB;
    SQRADD(a[11], a[11]);
    COMBA_STO(b[22]);

    /* output 23 */
    CARRY_FOW;
    SQRADDSC(a[8], a[15]);
    SQRADDAC(a[9], a[14]);
    SQRADDAC(a[10], a[13]);
    SQRADDAC(a[11], a[12]);
    SQRADDDB;
    COMBA_STO(b[23]);

    /* output 24 */
    CARRY_FOW;
    SQRADDSC(a[9], a[15]);
    SQRADDAC(a[10], a[14]);
    SQRADDAC(a[11], a[13]);
    SQRADDDB;
    SQRADD(a[12], a[12]);
    COMBA_STO(b[24]);

    /* output 25 */
    CARRY_FOW;
    SQRADDSC(a[10], a[15]);
    SQRADDAC(a[11], a[14]);
    SQRADDAC(a[12], a[13]);
    SQRADDDB;
    COMBA_STO(b[25]);

    /* output 26 */
    CARRY_FOW;
    SQRADD2(a[11], a[15]);
    SQRADD2(a[12], a[14]);
    SQRADD(a[13], a[13]);
    COMBA_STO(b[26]);

    /* output 27 */
    CARRY_FOW;
    SQRADD2(a[12], a[15]);
    SQRADD2(a[13], a[14]);
    COMBA_STO(b[27]);

    /* output 28 */
    CARRY_FOW;
    SQRADD2(a[13], a[15]);
    SQRADD(a[14], a[14]);
    COMBA_STO(b[28]);

    /* output 29 */
    CARRY_FOW;
    SQRADD2(a[14], a[15]);
    COMBA_STO(b[29]);

    /* output 30 */
    CARRY_FOW;
    SQRADD(a[15], a[15]);
    COMBA_STO(b[30]);
    COMBA_STO2(b[31]);
    COMBA_FIN;

    B->u = 32;
    B->s = ZPOS;
    memcpy(B->dp, b, 32*sizeof(rnd));
    rn_clamp(B);
    break;
  }
}
#endif /* RN_SMALL_SET */

