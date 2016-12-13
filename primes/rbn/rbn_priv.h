#ifndef RBN_PRIV_H
#define RBN_PRIV_H

#define RN_VER_S "v0.0.1"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rtypedef.h"
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

static const int lnz[16] = {4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0};
static const rnd primes[PR_SIZ] = {
  0x0002, 0x0003, 0x0005, 0x0007, 0x000b, 0x000d, 0x0011, 0x0013,
  0x0017, 0x001d, 0x001f, 0x0025, 0x0029, 0x002b, 0x002f, 0x0035,
  0x003b, 0x003d, 0x0043, 0x0047, 0x0049, 0x004f, 0x0053, 0x0059,
  0x0061, 0x0065, 0x0067, 0x006b, 0x006d, 0x0071, 0x007f, 0x0083,
  0x0089, 0x008b, 0x0095, 0x0097, 0x009d, 0x00a3, 0x00a7, 0x00ad,
  0x00b3, 0x00b5, 0x00bf, 0x00c1, 0x00c5, 0x00c7, 0x00d3, 0x00df,
  0x00e3, 0x00e5, 0x00e9, 0x00ef, 0x00f1, 0x00fb, 0x0101, 0x0107,
  0x010d, 0x010f, 0x0115, 0x0119, 0x011b, 0x0125, 0x0133, 0x0137,

  0x0139, 0x013d, 0x014b, 0x0151, 0x015b, 0x015d, 0x0161, 0x0167,
  0x016f, 0x0175, 0x017b, 0x017f, 0x0185, 0x018d, 0x0191, 0x0199,
  0x01a3, 0x01a5, 0x01af, 0x01b1, 0x01b7, 0x01bb, 0x01c1, 0x01c9,
  0x01cd, 0x01cf, 0x01d3, 0x01df, 0x01e7, 0x01eb, 0x01f3, 0x01f7,
  0x01fd, 0x0209, 0x020b, 0x021d, 0x0223, 0x022d, 0x0233, 0x0239,
  0x023b, 0x0241, 0x024b, 0x0251, 0x0257, 0x0259, 0x025f, 0x0265,
  0x0269, 0x026b, 0x0277, 0x0281, 0x0283, 0x0287, 0x028d, 0x0293,
  0x0295, 0x02a1, 0x02a5, 0x02ab, 0x02b3, 0x02bd, 0x02c5, 0x02cf,

  0x02d7, 0x02dd, 0x02e3, 0x02e7, 0x02ef, 0x02f5, 0x02f9, 0x0301,
  0x0305, 0x0313, 0x031d, 0x0329, 0x032b, 0x0335, 0x0337, 0x033b,
  0x033d, 0x0347, 0x0355, 0x0359, 0x035b, 0x035f, 0x036d, 0x0371,
  0x0373, 0x0377, 0x038b, 0x038f, 0x0397, 0x03a1, 0x03a9, 0x03ad,
  0x03b3, 0x03b9, 0x03c7, 0x03cb, 0x03d1, 0x03d7, 0x03df, 0x03e5,
  0x03f1, 0x03f5, 0x03fb, 0x03fd, 0x0407, 0x0409, 0x040f, 0x0419,
  0x041b, 0x0425, 0x0427, 0x042d, 0x043f, 0x0443, 0x0445, 0x0449,
  0x044f, 0x0455, 0x045d, 0x0463, 0x0469, 0x047f, 0x0481, 0x048b,

  0x0493, 0x049d, 0x04a3, 0x04a9, 0x04b1, 0x04bd, 0x04c1, 0x04c7,
  0x04cd, 0x04cf, 0x04d5, 0x04e1, 0x04eb, 0x04fd, 0x04ff, 0x0503,
  0x0509, 0x050b, 0x0511, 0x0515, 0x0517, 0x051b, 0x0527, 0x0529,
  0x052f, 0x0551, 0x0557, 0x055d, 0x0565, 0x0577, 0x0581, 0x058f,
  0x0593, 0x0595, 0x0599, 0x059f, 0x05a7, 0x05ab, 0x05ad, 0x05b3,
  0x05bf, 0x05c9, 0x05cb, 0x05cf, 0x05d1, 0x05d5, 0x05db, 0x05e7,
  0x05f3, 0x05fb, 0x0607, 0x060d, 0x0611, 0x0617, 0x061f, 0x0623,
  0x062b, 0x062f, 0x063d, 0x0641, 0x0647, 0x0649, 0x064d, 0x0653};

/* externally define this symbol to ignore the default settings, useful for
   changing the build from the make process */
#ifndef RN_ALREADY_SET
/* do we want the large set of small multiplications ?
   Enable these if you are going to be doing a lot of small (<= 16 digit)
   multiplications say in ECC
   Or if you're on a 64-bit machine doing RSA as a 1024-bit integer == 16 digits
   ;-) */
#define RN_SMALL_SET
/* do we want huge code ?
   Enable these if you are doing 20, 24, 28, 32, 48, 64 digit multiplications
   (useful for RSA)
   Less important on 64-bit machines as 32 digits == 2048 bits */
#if 0
#define RN_MUL3
#define RN_MUL4
#define RN_MUL6
#define RN_MUL7
#define RN_MUL8
#define RN_MUL9
#define RN_MUL12
#define RN_MUL17
#endif
#define RN_MUL20
#define RN_MUL24
#define RN_MUL28
#define RN_MUL32
#define RN_MUL48
#define RN_MUL64

#if 0
#define RN_SQR3
#define RN_SQR4
#define RN_SQR6
#define RN_SQR7
#define RN_SQR8
#define RN_SQR9
#define RN_SQR12
#define RN_SQR17
#endif
#define RN_SQR20
#define RN_SQR24
#define RN_SQR28
#define RN_SQR32
#define RN_SQR48
#define RN_SQR64
#endif
/* do we want some overflow checks
   Not required if you make sure your numbers are within range */
/* #define RN_CHK */
/* #define RN_PRESCOTT */

void s_rn_add(rni *a, rni *b, rni *c);
void s_rn_sub(rni *a, rni *b, rni *c);
void rn_rev(unsigned char *s, int len);

void rn_mul_comba(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba.c"

#ifdef RN_SMALL_SET
void rn_mul_combasmall(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_smallset.c"
#endif

#ifdef RN_MUL3
//void rn_mul_comba3(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_3.c"
#endif
#ifdef RN_MUL4
//void rn_mul_comba4(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_4.c"
#endif
#ifdef RN_MUL6
//void rn_mul_comba6(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_6.c"
#endif
#ifdef RN_MUL7
//void rn_mul_comba7(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_7.c"
#endif
#ifdef RN_MUL8
//void rn_mul_comba8(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_8.c"
#endif
#ifdef RN_MUL9
//void rn_mul_comba9(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_9.c"
#endif
#ifdef RN_MUL12
//void rn_mul_comba12(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_12.c"
#endif
#ifdef RN_MUL17
//void rn_mul_comba17(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_17.c"
#endif

#ifdef RN_MUL20
//void rn_mul_comba20(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_20.c"
#endif
#ifdef RN_MUL24
//void rn_mul_comba24(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_24.c"
#endif
#ifdef RN_MUL28
//void rn_mul_comba28(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_28.c"
#endif
#ifdef RN_MUL32
//void rn_mul_comba32(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_32.c"
#endif
#ifdef RN_MUL48
//void rn_mul_comba48(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_48.c"
#endif
#ifdef RN_MUL64
//void rn_mul_comba64(rni *A, rni *B, rni *C);
#include "mul/rn_mul_comba_64.c"
#endif

void rn_sqr_comba(rni *A, rni *B);

#ifdef RN_SMALL_SET
//void rn_sqr_combasmall(rni *A, rni *B);
#include "sqr/rn_sqr_comba_smallset.c"
#endif

#ifdef RN_SQR3
//void rn_sqr_comba3(rni *A, rni *B);
#include "sqr/rn_sqr_comba_3.c"
#endif
#ifdef RN_SQR4
//void rn_sqr_comba4(rni *A, rni *B);
#include "sqr/rn_sqr_comba_4.c"
#endif
#ifdef RN_SQR6
//void rn_sqr_comba6(rni *A, rni *B);
#include "sqr/rn_sqr_comba_6.c"
#endif
#ifdef RN_SQR7
//void rn_sqr_comba7(rni *A, rni *B);
#include "sqr/rn_sqr_comba_7.c"
#endif
#ifdef RN_SQR8
//void rn_sqr_comba8(rni *A, rni *B);
#include "sqr/rn_sqr_comba_8.c"
#endif
#ifdef RN_SQR9
//void rn_sqr_comba9(rni *A, rni *B);
#include "sqr/rn_sqr_comba_9.c"
#endif
#ifdef RN_SQR12
//void rn_sqr_comba12(rni *A, rni *B);
#include "sqr/rn_sqr_comba_12.c"
#endif
#ifdef RN_SQR17
//void rn_sqr_comba17(rni *A, rni *B);
#include "sqr/rn_sqr_comba_17.c"
#endif

#ifdef RN_SQR20
//void rn_sqr_comba20(rni *A, rni *B);
#include "sqr/rn_sqr_comba_20.c"
#endif
#ifdef RN_SQR24
//void rn_sqr_comba24(rni *A, rni *B);
#include "sqr/rn_sqr_comba_24.c"
#endif
#ifdef RN_SQR28
//void rn_sqr_comba28(rni *A, rni *B);
#include "sqr/rn_sqr_comba_28.c"
#endif
#ifdef RN_SQR32
//void rn_sqr_comba32(rni *A, rni *B);
#include "sqr/rn_sqr_comba_32.c"
#endif
#ifdef RN_SQR48
//void rn_sqr_comba48(rni *A, rni *B);
#include "sqr/rn_sqr_comba_48.c"
#endif
#ifdef RN_SQR64
//void rn_sqr_comba64(rni *A, rni *B);
#include "sqr/rn_sqr_comba_64.c"
#endif
extern const char *rn_srmap;
const char *rn_srmap = /* chars used in radix conversions */
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";

#include "rbn.h"
#endif /* RBN_PRIV_H */

