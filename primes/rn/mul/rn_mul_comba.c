#if defined(RN_PRESCOTT) && defined(RN_SSE2)
#undef RN_SSE2
#define RN_X86
#endif
#include "../rn_priv.h"

/* anything you need at the start */
#define COMBA_START
/* clear the chaining variables */
#define COMBA_CLR c0=c1=c2=0;
/* forward the carry to the next digit */
#define COMBA_FOW do { c0=c1; c1=c2; c2=0; } while (0);
/* store the first sum */
#define COMBA_STO(x) x=c0;
/* store the second sum [carry] */
#define COMBA_STO2(x) x=c1;
/* anything you need at the end */
#define COMBA_FIN

/* these are the combas.  Worship them. */
#if defined(RN_X86)
/* Generic x86 optimized code */
/* this should multiply i and j  */
#define MULADD(i,j) \
  asm("movl  %6,%%eax     \n\t" \
      "mull  %7           \n\t" \
      "addl  %%eax,%0     \n\t" \
      "adcl  %%edx,%1     \n\t" \
      "adcl  $0,%2        \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"m"(i),"m"(j) \
      : "%eax","%edx", "cc");

#elif defined(RN_X86_64)
/* x86-64 optimized */
#define MULADD(i,j) \
  asm("movq  %6,%%rax     \n\t" \
      "mulq  %7           \n\t" \
      "addq  %%rax,%0     \n\t" \
      "adcq  %%rdx,%1     \n\t" \
      "adcq  $0,%2        \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"g"(i),"g"(j) \
      : "%rax","%rdx","cc");

#else
/* ISO C code */
#define MULADD(i,j) \
  do { rnw t; t=(rnw)c0+((rnw)i)*((rnw)j); \
    c0=t; t=(rnw)c1+(t>>DGT_BIT); \
    c1=t; c2+=t>>DGT_BIT; } while (0);
#endif

#ifndef RN_DEFINES
/* generic PxQ multiplier */
void rn_mul_comba(rni *A, rni *B, rni *C)
{
  int ix, iy, iz, tx, ty, pa;
  rnd c0, c1, c2, *tmpx, *tmpy;
  rni tmp, *dst;

  COMBA_START;
  COMBA_CLR;
  pa = A->u+B->u;
  if (pa >= RN_SIZ)
    pa = RN_SIZ-1;
  if (A==C || B==C) {
    zero(&tmp);
    dst = &tmp;
  } else {
    zero(C);
    dst = C;
  }
  for (ix=0; ix<pa; ++ix) {
    ty = MIN(ix, B->u-1);
    tx = ix-ty;

    tmpx = A->dp+tx;
    tmpy = B->dp+ty;
    iy = MIN(A->u-tx, ty+1);

    COMBA_FOW;
    for (iz=0; iz<iy; ++iz) {
      rnd _tmpx = *tmpx++;
      rnd _tmpy = *tmpy--;
      MULADD(_tmpx, _tmpy);
    }
    COMBA_STO(dst->dp[ix]);
  }
  COMBA_FIN;
  dst->u = pa;
  dst->s = A->s^B->s;
  rn_clamp(dst);
  rn_cpy(dst, C);
}
#endif

