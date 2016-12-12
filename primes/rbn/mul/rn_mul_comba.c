#if defined(RN_PRESCOTT) && defined(RN_SSE2)
#undef RN_SSE2
#define RN_X86
#endif

#include "../rbn_priv.h"

/* anything you need at the start */
#define COMBA_START
/* clear the chaining variables */
#define COMBA_CLR c0=c1=c2=0;
/* forward the carry to the next digit */
#define COMBA_FOW \
  do { c0=c1; c1=c2; c2=0; } while (0);
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

#elif defined(RN_SSE2)
/* use SSE2 optimizations */
#undef COMBA_FIN
#define COMBA_FIN asm("emms");

#define MULADD(i,j) \
  asm("movd  %6,%%mm0     \n\t" \
      "movd  %7,%%mm1     \n\t" \
      "pmuludq %%mm1,%%mm0\n\t" \
      "movd  %%mm0,%%eax  \n\t" \
      "psrlq $32,%%mm0    \n\t" \
      "addl  %%eax,%0     \n\t" \
      "movd  %%mm0,%%eax  \n\t" \
      "adcl  %%eax,%1     \n\t" \
      "adcl  $0,%2        \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"m"(i),"m"(j) \
      : "%eax","cc");

#elif defined(RN_ARM)
/* ARM code */
#define MULADD(i,j) \
  asm("  UMULL  r0,r1,%6,%7           \n\t" \
      "  ADDS   %0,%0,r0              \n\t" \
      "  ADCS   %1,%1,r1              \n\t" \
      "  ADC    %2,%2,#0              \n\t" \
      : "=r"(c0), "=r"(c1), "=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"r"(i),"r"(j) \
      : "r0","r1","cc");

#elif defined(RN_PPC32)
/* For 32-bit PPC */
/* untested: will mulhwu change the flags?  Docs say no */
#define MULADD(i,j) \
  asm(" mullw  16,%6,%7       \n\t" \
      " addc   %0,%0,16       \n\t" \
      " mulhwu 16,%6,%7       \n\t" \
      " adde   %1,%1,16       \n\t" \
      " addze  %2,%2          \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"r"(i),"r"(j) \
      : "16");

#elif defined(RN_PPC64)
/* For 64-bit PPC */
/* untested: will mulhdu change the flags?  Docs say no */
#define MULADD(i,j) \
  asm(" mulld  r16,%6,%7       \n\t" \
      " addc   %0,%0,16       \n\t"  \
      " mulhdu r16,%6,%7       \n\t" \
      " adde   %1,%1,16       \n\t"  \
      " addze  %2,%2          \n\t"  \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"r"(i),"r"(j) \
      : "r16");

#elif defined(RN_AVR32)
/* ISO C code */
#define MULADD(i,j) \
  asm(" mulu.d r2,%6,%7        \n\t" \
      " add    %0,r2           \n\t" \
      " adc    %1,%1,r3        \n\t" \
      " acr    %2              \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"r"(i),"r"(j) \
      : "r2","r3");

#elif defined(RN_MIPS)
#define MULADD(i,j) \
  asm(" multu  %6,%7          \n\t" \
      " mflo   $12            \n\t" \
      " mfhi   $13            \n\t" \
      " addu    %0,%0,$12     \n\t" \
      " sltu   $12,%0,$12     \n\t" \
      " addu    %1,%1,$13     \n\t" \
      " sltu   $13,%1,$13     \n\t" \
      " addu    %1,%1,$12     \n\t" \
      " sltu   $12,%1,$12     \n\t" \
      " addu    %2,%2,$13     \n\t" \
      " addu    %2,%2,$12     \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"r"(i),"r"(j) \
      : "$12","$13");
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

