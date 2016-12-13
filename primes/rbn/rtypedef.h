#ifndef RTYPEDEF_H
#define RTYPEDEF_H

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
/* autodetect x86-64 and make sure we are using 64-bit digits with x86-64
 * asm */
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

#endif /* RTYPEDEF_H */
