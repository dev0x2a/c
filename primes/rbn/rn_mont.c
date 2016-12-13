#include <tfm_private.h>

#define MONT_START
#define MONT_FIN
#define LOOP_END
#define LOOP_START mu = c[x]*mp
/******************************************************************/
#if defined(TFM_X86) && !defined(TFM_SSE2) /* x86-32 code */

#define INNERMUL \
  asm("movl %5,%%eax \n\t" \
      "mull %4       \n\t" \
      "addl %1,%%eax \n\t" \
      "adcl $0,%%edx \n\t" \
      "addl %%eax,%0 \n\t" \
      "adcl $0,%%edx \n\t" \
      "movl %%edx,%1 \n\t" \
      : "=g"(_c[LO]),"=r"(cy) \
      : "0"(_c[LO]),"1"(cy),"r"(mu),"r"(*tmpm++) \
      : "%eax","%edx","cc")

#define PROPCARRY \
  asm("addl   %1,%0    \n\t" \
      "setb   %%al     \n\t" \
      "movzbl %%al,%1 \n\t" \
      : "=g"(_c[LO]),"=r"(cy) \
      : "0"(_c[LO]),"1"(cy) \
      : "%eax","cc")

/******************************************************************/
#elif defined(TFM_X86_64) /* x86-64 code */

#define INNERMUL \
  asm("movq %5,%%rax \n\t" \
      "mulq %4       \n\t" \
      "addq %1,%%rax \n\t" \
      "adcq $0,%%rdx \n\t" \
      "addq %%rax,%0 \n\t" \
      "adcq $0,%%rdx \n\t" \
      "movq %%rdx,%1 \n\t" \
      : "=g"(_c[LO]),"=r"(cy) \
      : "0"(_c[LO]),"1"(cy),"r"(mu),"r"(*tmpm++) \
      : "%rax","%rdx","cc")

#define INNERMUL8 \
  asm("movq 0(%5),%%rax    \n\t" \
      "movq 0(%2),%%r10    \n\t" \
      "movq 0x8(%5),%%r11  \n\t" \
      "mulq %4             \n\t" \
      "addq %%r10,%%rax    \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq 0x8(%2),%%r10  \n\t" \
      "addq %3,%%rax       \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq %%rax,0(%0)    \n\t" \
      "movq %%rdx,%1       \n\t" \
                                 \
      "movq %%r11,%%rax    \n\t" \
      "movq 0x10(%5),%%r11 \n\t" \
      "mulq %4             \n\t" \
      "addq %%r10,%%rax    \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq 0x10(%2),%%r10 \n\t" \
      "addq %3,%%rax       \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq %%rax,0x8(%0)  \n\t" \
      "movq %%rdx,%1       \n\t" \
                                 \
      "movq %%r11,%%rax    \n\t" \
      "movq 0x18(%5),%%r11 \n\t" \
      "mulq %4             \n\t" \
      "addq %%r10,%%rax    \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq 0x18(%2),%%r10 \n\t" \
      "addq %3,%%rax       \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq %%rax,0x10(%0) \n\t" \
      "movq %%rdx,%1       \n\t" \
                                 \
      "movq %%r11,%%rax    \n\t" \
      "movq 0x20(%5),%%r11 \n\t" \
      "mulq %4             \n\t" \
      "addq %%r10,%%rax    \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq 0x20(%2),%%r10 \n\t" \
      "addq %3,%%rax       \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq %%rax,0x18(%0) \n\t" \
      "movq %%rdx,%1       \n\t" \
                                 \
      "movq %%r11,%%rax    \n\t" \
      "movq 0x28(%5),%%r11 \n\t" \
      "mulq %4             \n\t" \
      "addq %%r10,%%rax    \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq 0x28(%2),%%r10 \n\t" \
      "addq %3,%%rax       \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq %%rax,0x20(%0) \n\t" \
      "movq %%rdx,%1       \n\t" \
                                 \
      "movq %%r11,%%rax    \n\t" \
      "movq 0x30(%5),%%r11 \n\t" \
      "mulq %4             \n\t" \
      "addq %%r10,%%rax    \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq 0x30(%2),%%r10 \n\t" \
      "addq %3,%%rax       \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq %%rax,0x28(%0) \n\t" \
      "movq %%rdx,%1       \n\t" \
                                 \
      "movq %%r11,%%rax    \n\t" \
      "movq 0x38(%5),%%r11 \n\t" \
      "mulq %4             \n\t" \
      "addq %%r10,%%rax    \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq 0x38(%2),%%r10 \n\t" \
      "addq %3,%%rax       \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq %%rax,0x30(%0) \n\t" \
      "movq %%rdx,%1       \n\t" \
                                 \
      "movq %%r11,%%rax    \n\t" \
      "mulq %4             \n\t" \
      "addq %%r10,%%rax    \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "addq %3,%%rax       \n\t" \
      "adcq $0,%%rdx       \n\t" \
      "movq %%rax,0x38(%0) \n\t" \
      "movq %%rdx,%1       \n\t" \
                                 \
      : "=r"(_c),"=r"(cy) \
      : "0"(_c),"1"(cy),"g"(mu),"r"(tmpm) \
      : "%rax","%rdx","%r10","%r11","cc")

#define PROPCARRY \
  asm("addq   %1,%0    \n\t" \
      "setb   %%al     \n\t" \
      "movzbq %%al,%1 \n\t" \
      : "=g"(_c[LO]), "=r"(cy) \
      : "0"(_c[LO]), "1"(cy) \
      : "%rax", "cc")
/******************************************************************/
#else /* ISO C code */

#define INNERMUL \
  do { fnw t; _c[0] = t =((rnw)_c[0]+(rnw)cy)+(((rnw)mu)*((rnw)*tmpm++)); \
    cy = (t >> DGT_BIT); } while (0)

#define PROPCARRY \
  do { rnd t = _c[0] += cy; cy = (t < cy); } while (0)

#endif
/******************************************************************/

#define LO 0
#ifdef RN_SMALL_MONT_SET
#include "rn_mont_small.i"
#endif

/* computes x/R == x (mod N) via Montgomery Reduction */
void rn_mont_reduce(rni *a, rni *m, rnd mp)
{
  rnd c[RN_SIZ], *_c, *tmpm, mu;
  int ou, x, y, pa;

  if (m->u > (RN_SIZ/2))
    return;
#ifdef RN_SMALL_MONT_SET
  if (m->u <= 16) {
    rn_mont_reduce_small(a, m, mp);
    return;
  }
#endif
#if defined(USE_MEMSET)
  memset(c, 0, sizeof c);
#endif
  pa = m->u;
  ou = a->u;
  for (x=0; x<ou; ++x)
    c[x] = a->dp[x];
#if !defined(USE_MEMSET)
  for (; x<2*pa+1; ++x)
    c[x] = 0;
#endif
  MONT_START;
  for (x=0; x<pa; ++x) {
    rnd cy = 0;
    LOOP_START;
    _c = c+x;
    tmpm = m->dp;
    y = 0;
#if defined(INNERMUL8)
    for (; y<(pa&~7); y+=8) {
      INNERMUL8;
      _c += 8;
      tmpm += 8;
    }
#endif
    for (; y<pa; ++y) {
      INNERMUL;
      ++_c;
    }
    LOOP_END;
    while (cy) {
      PROPCARRY;
      ++_c;
    }
  }
  _c = c+pa;
  tmpm = a->dp;
  for (x=0; x<pa+1; ++x)
    *tmpm++ = *_c++;
  for (; x<ou; x++)
    *tmpm++ = 0;
  MONT_FIN;
  a->u = pa+1;
  rn_clamp(a);
  if (rn_cmp_mag(a, m) != RN_LT)
    s_rn_sub(a, m, a);
}

void rn_mont_calc_norm(rni *a, rni *b)
{ /* computes a = B**n mod b without division or multiplication
     useful for normalizing numbers in a Montgomery system */
  int x, bits=rn_cntbit(b)%DGT_BIT;
  if (!bits)
    bits = DGT_BIT;
  if (b->u > 1)
    rn_2exp(a, (b->u-1)*DGT_BIT+bits-1);
  else {
    rn_set(a, 1);
    bits = 1;
  }
  for (x=bits-1; x<(int)DGT_BIT; ++x) {
    rn_mul2(a, a);
    if (fn_cmp_mag(a,b) != RN_LT)
      s_rn_sub(a, b, a);
  }
}

int rn_mont_setup(rni *a, rnd *rho)
{ /* fast inversion mod 2**k
     Based on the fact that
     XA = 1 (mod 2**n)  =>  (X(2-XA)) A = 1 (mod 2**2n)
                        =>  2*X*A - X*X*A*A = 1
                        =>  2*(1) - (1)     = 1    */
  rnd x, b=a->dp[0];
  if ((b&1) == 0)
    return VAL;
  x = (((b+2)&4)<<1)+b; /* here x*a==1 mod 2**4 */
  x *= 2-b*x;           /* here x*a==1 mod 2**8 */
  x *= 2-b*x;           /* here x*a==1 mod 2**16 */
  x *= 2-b*x;           /* here x*a==1 mod 2**32 */
#ifdef RN_64BIT
  x *= 2-b*x;           /* here x*a==1 mod 2**64 */
#endif
  /* rho = -1/m mod b */
  *rho = (((rnw)1<<((rnw)DGT_BIT))-((rnw)x));
  return OK;
}

