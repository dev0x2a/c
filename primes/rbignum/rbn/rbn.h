#ifndef RBN_H
#define RBN_H
/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include <limits.h>
#include <stddef.h>
#include <string.h>

#define DGT_BIT (CHAR_BIT*8)
#define MAX_SIZ (4096+(8*DGT_BIT))
#define RN_SIZ (MAX_SIZ/DGT_BIT)

typedef unsigned long long rnd; /* number digit */
typedef unsigned long long rnw; /* word */
typedef struct {
  rnd dp[RN_SIZ];
  int u, s; /* used, sign */
} rni; /* int */

/* externally define this symbol to ignore the default settings, useful for
   changing the build from the make process */
#ifndef RN_ALREADY_SET
/* do we want the large set of small multiplications ?
   Enable these if you are going to be doing a lot of small (<= 16 digit)
   multiplications say in ECC
   Or if you're on a 64-bit machine doing RSA as a 1024-bit integer == 16 digits
   ;-) */
#define RN_SMALL_SET
/* do we want huge code
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
/* do we want some overflow checks
   Not required if you make sure your numbers are within range (e.g. by default
#define RN_CHK */
#endif
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

#undef init
#define init(u) (void)memset((u), 0, sizeof(rni))
#undef zero
#define zero(u) init(u)

#undef iszero
#undef iseven
#undef isodd
#define iszero(x) (((x)->u==0) ? RNY : RNN)
#define iseven(x) (((x)->u>=0 && (((x)->dp[0]&1) == 0)) ? RNY : RNN)
#define isodd(x) (((x)->u>0 && (((x)->dp[0]&1) == 1)) ? RNY : RNN)

#define rn_cpy(a,b) (void)(((a)!=(b)) && memcpy((b),(a),sizeof(rni)))
#define initcpy(a,b) rn_cpy(b,a)
#define rn_clamp(a) { while ((a)->u && (a)->dp[(a)->u-1] == 0) \
  --((a)->u); (a)->s = (a)->u ? (a)->s : ZPOS; }
#define rn_neg(a,b) { rn_cpy(a,b); (b)->s ^= 1; rn_clamp(b); }
#define rn_abs(a,b) { rn_cpy(a,b); (b)->s = 0; }

#define PRIME_SIZ 256
#define PRIME_BBS 0x0001
#define PRIME_SAFE 0x0002
#define PRIME_2MSB_OFF 0x0004
#define PRIME_2MSB_ON 0x0008

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

static const int lnz[16] = {
  4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0
};

void rn_add(rni *a, rni *b, rni *c);
void rn_addd(rni *a, rnd b, rni *c); /* c = a+b */
void s_rn_add(rni *a, rni *b, rni *c);

void rn_sub(rni *a, rni *b, rni *c);
void rn_subd(rni *a, rnd b, rni *c); /* c = a-b */
/* ||a|| >= ||b|| always */
void s_rn_sub(rni *a, rni *b, rni *c);

int rn_cmp(rni *a, rni *b);
int rn_cmpd(rni *a, rnd b);
int cmp_mag(rni *a, rni *b);

void rn_set(rni *a, rnd b);
void rn_rshd(rni *a, int x);
void rn_lshd(rni *a, int x);
void rn_2exp(rni *a, int b);
static int s_ispow2(rnd b, int *p);
int rn_cntbit(rni *a);
int rn_cntlsb(rni *a);

/* c = a mod b, 0 <= c < b */
int rn_mod(rni *a, rni *b, rni *c);
int rn_modd(rni *a, rnd b, rnd *c);
void rn_mod2d(rni *a, int b, rni *c);

/* a/b => cb + d == a */
int rn_div(rni *a, rni *b, rni *c, rni *d);
int rn_divd(rni *a, rnd b, rni *c, rnd *d);
void rn_div2(rni *a, rni *b);
void rn_div2d(rni *a, int b, rni *c, rni *d);

#endif /* RBN_H */
