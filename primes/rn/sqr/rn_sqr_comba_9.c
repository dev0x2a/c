#define RN_DEFINES
#include "rn_sqr_comba.c"

#if defined(RN_SQR9) && RN_SIZ >= 18
void rn_sqr_comba9(rni *A, rni *B)
{
  rnd *a, b[18], c0, c1, c2, sc0, sc1, sc2;
#ifdef RN_ISO
  rnw tt;
#endif
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
}
#endif

