#define RN_DEFINES
#include "rn_sqr_comba.c"

#if defined(RN_SQR20) && RN_SIZ >= 40
void rn_sqr_comba20(rni *A, rni *B)
{
  rnd *a, b[40], c0, c1, c2, sc0, sc1, sc2;
#ifdef RN_ISO
  rnw tt;
#endif
  a = A->dp;
  COMBA_START;

  /* clear carries */
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
  SQRADDSC(a[0], a[16]);
  SQRADDAC(a[1], a[15]);
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
  SQRADDSC(a[0], a[17]);
  SQRADDAC(a[1], a[16]);
  SQRADDAC(a[2], a[15]);
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
  SQRADDSC(a[0], a[18]);
  SQRADDAC(a[1], a[17]);
  SQRADDAC(a[2], a[16]);
  SQRADDAC(a[3], a[15]);
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
  SQRADDSC(a[0], a[19]);
  SQRADDAC(a[1], a[18]);
  SQRADDAC(a[2], a[17]);
  SQRADDAC(a[3], a[16]);
  SQRADDAC(a[4], a[15]);
  SQRADDAC(a[5], a[14]);
  SQRADDAC(a[6], a[13]);
  SQRADDAC(a[7], a[12]);
  SQRADDAC(a[8], a[11]);
  SQRADDAC(a[9], a[10]);
  SQRADDDB;
  COMBA_STO(b[19]);

  /* output 20 */
  CARRY_FOW;
  SQRADDSC(a[1], a[19]);
  SQRADDAC(a[2], a[18]);
  SQRADDAC(a[3], a[17]);
  SQRADDAC(a[4], a[16]);
  SQRADDAC(a[5], a[15]);
  SQRADDAC(a[6], a[14]);
  SQRADDAC(a[7], a[13]);
  SQRADDAC(a[8], a[12]);
  SQRADDAC(a[9], a[11]);
  SQRADDDB;
  SQRADD(a[10], a[10]);
  COMBA_STO(b[20]);

  /* output 21 */
  CARRY_FOW;
  SQRADDSC(a[2], a[19]);
  SQRADDAC(a[3], a[18]);
  SQRADDAC(a[4], a[17]);
  SQRADDAC(a[5], a[16]);
  SQRADDAC(a[6], a[15]);
  SQRADDAC(a[7], a[14]);
  SQRADDAC(a[8], a[13]);
  SQRADDAC(a[9], a[12]);
  SQRADDAC(a[10], a[11]);
  SQRADDDB;
  COMBA_STO(b[21]);

  /* output 22 */
  CARRY_FOW;
  SQRADDSC(a[3], a[19]);
  SQRADDAC(a[4], a[18]);
  SQRADDAC(a[5], a[17]);
  SQRADDAC(a[6], a[16]);
  SQRADDAC(a[7], a[15]);
  SQRADDAC(a[8], a[14]);
  SQRADDAC(a[9], a[13]);
  SQRADDAC(a[10], a[12]);
  SQRADDDB;
  SQRADD(a[11], a[11]);
  COMBA_STO(b[22]);

  /* output 23 */
  CARRY_FOW;
  SQRADDSC(a[4], a[19]);
  SQRADDAC(a[5], a[18]);
  SQRADDAC(a[6], a[17]);
  SQRADDAC(a[7], a[16]);
  SQRADDAC(a[8], a[15]);
  SQRADDAC(a[9], a[14]);
  SQRADDAC(a[10], a[13]);
  SQRADDAC(a[11], a[12]);
  SQRADDDB;
  COMBA_STO(b[23]);

  /* output 24 */
  CARRY_FOW;
  SQRADDSC(a[5], a[19]);
  SQRADDAC(a[6], a[18]);
  SQRADDAC(a[7], a[17]);
  SQRADDAC(a[8], a[16]);
  SQRADDAC(a[9], a[15]);
  SQRADDAC(a[10], a[14]);
  SQRADDAC(a[11], a[13]);
  SQRADDDB;
  SQRADD(a[12], a[12]);
  COMBA_STO(b[24]);

  /* output 25 */
  CARRY_FOW;
  SQRADDSC(a[6], a[19]);
  SQRADDAC(a[7], a[18]);
  SQRADDAC(a[8], a[17]);
  SQRADDAC(a[9], a[16]);
  SQRADDAC(a[10], a[15]);
  SQRADDAC(a[11], a[14]);
  SQRADDAC(a[12], a[13]);
  SQRADDDB;
  COMBA_STO(b[25]);

  /* output 26 */
  CARRY_FOW;
  SQRADDSC(a[7], a[19]);
  SQRADDAC(a[8], a[18]);
  SQRADDAC(a[9], a[17]);
  SQRADDAC(a[10], a[16]);
  SQRADDAC(a[11], a[15]);
  SQRADDAC(a[12], a[14]);
  SQRADDDB;
  SQRADD(a[13], a[13]);
  COMBA_STO(b[26]);

  /* output 27 */
  CARRY_FOW;
  SQRADDSC(a[8], a[19]);
  SQRADDAC(a[9], a[18]);
  SQRADDAC(a[10], a[17]);
  SQRADDAC(a[11], a[16]);
  SQRADDAC(a[12], a[15]);
  SQRADDAC(a[13], a[14]);
  SQRADDDB;
  COMBA_STO(b[27]);

  /* output 28 */
  CARRY_FOW;
  SQRADDSC(a[9], a[19]);
  SQRADDAC(a[10], a[18]);
  SQRADDAC(a[11], a[17]);
  SQRADDAC(a[12], a[16]);
  SQRADDAC(a[13], a[15]);
  SQRADDDB;
  SQRADD(a[14], a[14]);
  COMBA_STO(b[28]);

  /* output 29 */
  CARRY_FOW;
  SQRADDSC(a[10], a[19]);
  SQRADDAC(a[11], a[18]);
  SQRADDAC(a[12], a[17]);
  SQRADDAC(a[13], a[16]);
  SQRADDAC(a[14], a[15]);
  SQRADDDB;
  COMBA_STO(b[29]);

  /* output 30 */
  CARRY_FOW;
  SQRADDSC(a[11], a[19]);
  SQRADDAC(a[12], a[18]);
  SQRADDAC(a[13], a[17]);
  SQRADDAC(a[14], a[16]);
  SQRADDDB;
  SQRADD(a[15], a[15]);
  COMBA_STO(b[30]);

  /* output 31 */
  CARRY_FOW;
  SQRADDSC(a[12], a[19]);
  SQRADDAC(a[13], a[18]);
  SQRADDAC(a[14], a[17]);
  SQRADDAC(a[15], a[16]);
  SQRADDDB;
  COMBA_STO(b[31]);

  /* output 32 */
  CARRY_FOW;
  SQRADDSC(a[13], a[19]);
  SQRADDAC(a[14], a[18]);
  SQRADDAC(a[15], a[17]);
  SQRADDDB;
  SQRADD(a[16], a[16]);
  COMBA_STO(b[32]);

  /* output 33 */
  CARRY_FOW;
  SQRADDSC(a[14], a[19]);
  SQRADDAC(a[15], a[18]);
  SQRADDAC(a[16], a[17]);
  SQRADDDB;
  COMBA_STO(b[33]);

  /* output 34 */
  CARRY_FOW;
  SQRADD2(a[15], a[19]);
  SQRADD2(a[16], a[18]);
  SQRADD(a[17], a[17]);
  COMBA_STO(b[34]);

  /* output 35 */
  CARRY_FOW;
  SQRADD2(a[16], a[19]);
  SQRADD2(a[17], a[18]);
  COMBA_STO(b[35]);

  /* output 36 */
  CARRY_FOW;
  SQRADD2(a[17], a[19]);
  SQRADD(a[18], a[18]);
  COMBA_STO(b[36]);

  /* output 37 */
  CARRY_FOW;
  SQRADD2(a[18], a[19]);
  COMBA_STO(b[37]);

  /* output 38 */
  CARRY_FOW;
  SQRADD(a[19], a[19]);
  COMBA_STO(b[38]);
  COMBA_STO2(b[39]);
  COMBA_FIN;

  B->u = 40;
  B->s = ZPOS;
  memcpy(B->dp, b, 40*sizeof(rnd));
  rn_clamp(B);
}
#endif

