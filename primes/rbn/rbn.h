#ifndef RBN_H
#define RBN_H
/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtypedef.h"
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
   Not required if you make sure your numbers are within range */
/* #define RN_CHK */
/* #define RN_PRESCOTT */
/* #define RN_TIMING_RESISTANT */
#endif /* RN_ALREADY_SET */

#undef MASK
#undef OK
#undef VAL
#undef MEM
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

#define PR_SIZ 256
#define PR_BBS 0x0001
#define PR_SAFE 0x0002
#define PR_2MSB_OFF 0x0004
#define PR_2MSB_ON 0x0008

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

static const int lnz[16] = {
  4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0
};
const char *rn_srmap =
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";

/* functions */
/* returns a RN ident string useful for debugging... */
const char *rn_ident(void);

/* set to a small digit */
void rn_set(rni *a, rnd b);

/* makes a pseudo-random int of a given size */
void rn_rand(rni *a, int digits);

/* right shift x digits */
void rn_rshd(rni *a, int x);

/* left shift x digits */
void rn_lshd(rni *a, int x);

/* signed comparison */
int rn_cmp(rni *a, rni *b);

/* unsigned comparison */
int rn_cmp_mag(rni *a, rni *b);

/* power of 2 operations */
void rn_div2d(rni *a, int b, rni *c, rni *d);
void rn_mod2d(rni *a, int b, rni *c);
void rn_mul2d(rni *a, int b, rni *c);
void rn_2expt(rni *a, int b);
void rn_mul2(rni *a, rni *c);
void rn_div2(rni *a, rni *c);

/* Counts the number of lsbs which are zero before the first zero bit */
int rn_cntlsb(rni *a);

/* c = a + b */
void rn_add(rni *a, rni *b, rni *c);

/* c = a - b */
void rn_sub(rni *a, rni *b, rni *c);

/* c = a * b */
void rn_mul(rni *a, rni *b, rni *c);

/* b = a*a */
void rn_sqr(rni *a, rni *b);

/* a/b => cb + d == a */
int rn_div(rni *a, rni *b, rni *c, rni *d);

/* c = a mod b, 0 <= c < b  */
int rn_mod(rni *a, rni *b, rni *c);

/* compare against a single digit */
int rn_cmpd(rni *a, rnd b);

/* c = a + b */
void rn_addd(rni *a, rnd b, rni *c);

/* c = a - b */
void rn_subd(rni *a, rnd b, rni *c);

/* c = a * b */
void rn_muld(rni *a, rnd b, rni *c);

/* a/b => cb + d == a */
int rn_divd(rni *a, rnd b, rni *c, rnd *d);

/* c = a mod b, 0 <= c < b  */
int rn_modd(rni *a, rnd b, rnd *c);

/* num theory */
/* d = a + b (mod c) */
int rn_addmod(rni *a, rni *b, rni *c, rni *d);

/* d = a - b (mod c) */
int rn_submod(rni *a, rni *b, rni *c, rni *d);

/* d = a * b (mod c) */
int rn_mulmod(rni *a, rni *b, rni *c, rni *d);

/* c = a * a (mod b) */
int rn_sqrmod(rni *a, rni *b, rni *c);

/* c = 1/a (mod b) */
int rn_invmod(rni *a, rni *b, rni *c);

/* c = (a, b) */
void rn_gcd(rni *a, rni *b, rni *c);

/* c = [a, b] */
void rn_lcm(rni *a, rni *b, rni *c);

/* setups the montgomery reduction */
int rn_mont_setup(rni *a, rnd *mp);

/* computes a = B**n mod b without division or multiplication useful for
 * normalizing numbers in a Montgomery system */
void rn_mont_calc_norm(rni *a, rni *b);

/* computes x/R == x (mod N) via Montgomery Reduction */
void rn_mont_reduce(rni *a, rni *m, rnd mp);

/* d = a**b (mod c) */
int rn_exptmod(rni *a, rni *b, rni *c, rni *d);

/* primality stuff */
/* perform a Miller-Rabin test of a to the base b and store result in
   "result" */
void rn_pr_millrab(rni *a, rni *b, int *result);

int rn_isprime(rni *a, int t);

/* callback for rn_prime_random, should fill dst with random bytes and
 * return how many read [upto len] */
typedef int rn_prime_callback(unsigned char *dst, int len, void *dat);

#define rn_pr_rand_macro(a,t,size,bbs,cb,dat) \
  rn_pr_rand(a,t,((size)*8)+1, (bbs==1) ? RN_PRIME_BBS : 0,cb,dat)

int rn_pr_rand(rni *a, int t, int size, int flags,
                       rn_prime_callback cb, void *dat);

/* radix conersions */
int rn_cntbit(rni *a);

int rn_unsigned_bin_size(rni *a);
void rn_read_unsigned_bin(rni *a, const unsigned char *b, int c);
void rn_to_unsigned_bin(rni *a, unsigned char *b);

int rn_signed_bin_size(rni *a);
void rn_read_signed_bin(rni *a, const unsigned char *b, int c);
void rn_to_signed_bin(rni *a, unsigned char *b);

int rn_read_radix(rni *a, const char *str, int radix);

int rn_radix_siz(rni *a, int radix, int *size);
int rn_toradix(rni *a, char *str, int radix);
int rn_toradixn(rni *a, char *str, int radix, int maxlen);

#if 0
void rn_add(rni *a, rni *b, rni *c);
void rn_addd(rni *a, rnd b, rni *c);
void s_rn_add(rni *a, rni *b, rni *c);

void rn_sub(rni *a, rni *b, rni *c);
void rn_subd(rni *a, rnd b, rni *c);
void s_rn_sub(rni *a, rni *b, rni *c);

int rn_cmp(rni *a, rni *b);
int rn_cmpd(rni *a, rnd b);
int rn_cmp_mag(rni *a, rni *b);

void rn_set(rni *a, rnd b);
void rn_rshd(rni *a, int x);
void rn_lshd(rni *a, int x);
void rn_2exp(rni *a, int b);
static int s_ispow2(rnd b, int *p);
int rn_cntbit(rni *a);
int rn_cntlsb(rni *a);

int rn_mod(rni *a, rni *b, rni *c);
int rn_modd(rni *a, rnd b, rnd *c);
void rn_mod2d(rni *a, int b, rni *c);

void rn_mul(rni *A, rni *B, rni *C);
void rn_mul2(rni *a, rni *b);
void rn_muld(rni *a, rnd b, rni *c);
void rn_mul2d(rni *a, int b, rni *c);
int rn_mulmod(rni *a, rni *b, rni *c, rni *d);

int rn_div(rni *a, rni *b, rni *c, rni *d);
int rn_divd(rni *a, rnd b, rni *c, rnd *d);
void rn_div2(rni *a, rni *b);
void rn_div2d(rni *a, int b, rni *c, rni *d);

int rn_radix_siz(rni *a, int radix, int *size);
int rn_read_radix(rni *a, const char *str, int radix);
int rn_toradixn(rni *a, char *str, int radix, int maxlen);
int rn_toradix(rni *a,  char *str, int radix);
void rn_printf(rni *a, int radix, FILE *o);
void rn_rev(unsigned char *s, int len);
void rn_rand(rni *a, int dgt);
void rn_gcd(rni *a, rni *b, rni *c);
#endif /* #if 0 */
#endif /* RBN_H */

