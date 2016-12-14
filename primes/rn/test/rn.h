#ifndef RN_H
#define RN_H
#define RN_VER_S "v0.0.1"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define DGT_BIT (CHAR_BIT*8)
#define MAX_SIZ (4096+(8*DGT_BIT))
#define RN_SIZ (MAX_SIZ/DGT_BIT)

/* will this lib work? */
#if (CHAR_BIT & 7)
#error CHAR_BIT must be a multiple of eight.
#endif
#if MAX_SIZ % CHAR_BIT
#error MAX_SIZ must be a multiple of CHAR_BIT
#endif

#if __SIZEOF_LONG__ == 8
#define RN_64BIT
#endif
/* autodetect x86-64 and make sure we are
   using 64-bit digits with x86-64 asm */
#if defined(__x86_64__)
#if defined(RN_X86) || defined(RN_SSE2) || defined(RN_ARM)
#error x86-64 detected, x86-32/SSE2/ARM optimizations are not valid!
#endif
#if !defined(RN_X86_64) && !defined(RN_NO_ASM)
#define RN_X86_64
#endif
#endif
#if defined(RN_X86_64)
#if !defined(RN_64BIT)
#define RN_64BIT
#endif
#endif
/* try to detect x86-32 */
#if defined(__i386__) && !defined(RN_SSE2)
#if defined(RN_X86_64) || defined(RN_ARM)
#error x86-32 detected, x86-64/ARM optimizations are not valid!
#endif
#if !defined(RN_X86) && !defined(RN_NO_ASM)
#define RN_X86
#endif
#endif

typedef unsigned long long ulong64;

#if defined(RN_64BIT)
#ifndef CRYPT
typedef unsigned long long ulong64;
#endif // crypt

typedef ulong64 rnd;
#define SIZEOF_RN_DGT 8
typedef unsigned long rnw __attribute__((mode(TI)));
#else

#ifndef CRYPT
#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef unsigned __int64 ulong64;
typedef signed __int64 long64;
#else
typedef unsigned long long ulong64;
typedef signed long long long64;
#endif /* defined(_MSC_VER) ... */
#endif // crypt

typedef unsigned int rnd;
#define SIZEOF_RN_DGT 4
typedef ulong64 rnw;
#endif /* rn_64BIT */

//typedef unsigned long long rnd; /* number digit */
//typedef unsigned long long rnw; /* word */
typedef struct {
  rnd dp[RN_SIZ];
  int u, s; /* used, sign */
} rni; /* int */

#define PR_SIZ 256
#define PR_BBS 0x0001
#define PR_SAFE 0x0002
#define PR_2MSB_OFF 0x0004
#define PR_2MSB_ON 0x0008


void rn_add(rni *a, rni *b, rni *c);
void rn_addd(rni *a, rnd b, rni *c);
void s_rn_add(rni *a, rni *b, rni *c);

void burn_stack(unsigned long len);
void zeromem(volatile void *out, size_t outlen);
int mem_neq(const void *a, const void *b, size_t len);

void rn_printf(rni *a, int radix, FILE *o);
void rn_set(rni *a, rnd b);
const char *rn_ident(void);

#undef init
#undef zero
#undef iszero
#undef iseven
#undef isodd
#undef MIN
#undef MAX
#undef OK
#undef VAL
#undef MEM
#undef MASK

#define RN_LT -1
#define RN_EQ 0
#define RN_GT 1
#define RNY 1
#define RNN 0
#define ZPOS 0
#define RNEG 1
#define OK 0
#define VAL 1
#define MEM 2
#define MASK (rnd)(-1)

#define init(u) (void)memset((u), 0, sizeof(rni))
#define zero(u) init(u)

#define iszero(x) (((x)->u==0) ? RNY : RNN)
#define iseven(x) (((x)->u>=0 && (((x)->dp[0]&1) == 0)) ? RNY : RNN)
#define isodd(x) (((x)->u>0 && (((x)->dp[0]&1) == 1)) ? RNY : RNN)

#define rn_cpy(a,b) (void)(((a)!=(b)) && memcpy((b),(a),sizeof(rni)))
#define initcpy(a,b) rn_cpy(b,a)
#define rn_clamp(a) { while ((a)->u && (a)->dp[(a)->u-1]==0) \
  --((a)->u); (a)->s = (a)->u ? (a)->s : ZPOS; }
#define rn_neg(a,b) { rn_cpy(a,b); (b)->s ^= 1; rn_clamp(b); }
#define rn_abs(a,b) { rn_cpy(a,b); (b)->s = 0; }

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#endif /* RN_H */

