#define RN_DEFINES
#include "rn_sqr_comba.c"

#if defined(RN_SQR3) && FP_SIZE >= 6
void rn_sqr_comba3(rni *A, rni *B)
{
  rnd *a, b[6], c0, c1, c2, sc0, sc1, sc2;
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
}
#endif

