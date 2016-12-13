#ifndef RBN_H
#define RBN_H
/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */

/* functions */
const char *rn_ident(void); /* returns RN ident string
                               useful for debugging */
void rn_set(rni *a, rnd b); /* set to a small digit */
void rn_rand(rni *a, int digits); /* gen pseudo-random int of given size */
void rn_rshd(rni *a, int x); /* right shift x digits */
void rn_lshd(rni *a, int x); /* left shift x digits */
int rn_cmp(rni *a, rni *b); /* signed comparison */
int rn_cmp_mag(rni *a, rni *b); /* unsigned comparison */

/* power of 2 operations */
void rn_div2d(rni *a, int b, rni *c, rni *d);
void rn_mod2d(rni *a, int b, rni *c);
void rn_mul2d(rni *a, int b, rni *c);
void rn_2exp(rni *a, int b);
void rn_mul2(rni *a, rni *c);
void rn_div2(rni *a, rni *c);

int rn_cntlsb(rni *a); /* Counts num of lsbs which
                          are zero before first zero bit */
void rn_add(rni *a, rni *b, rni *c); /* c = a + b */
void rn_sub(rni *a, rni *b, rni *c); /* c = a - b */
void rn_mul(rni *a, rni *b, rni *c); /* c = a * b */
void rn_sqr(rni *a, rni *b); /* b = a*a */
int rn_div(rni *a, rni *b, rni *c, rni *d); /* a/b => cb + d == a */
int rn_mod(rni *a, rni *b, rni *c); /* c = a mod b, 0 <= c < b */
int rn_cmpd(rni *a, rnd b); /* compare against a single digit */
void rn_addd(rni *a, rnd b, rni *c); /* c = a + b */
void rn_subd(rni *a, rnd b, rni *c); /* c = a - b */
void rn_muld(rni *a, rnd b, rni *c); /* c = a * b */
int rn_divd(rni *a, rnd b, rni *c, rnd *d); /* a/b => cb + d == a */
int rn_modd(rni *a, rnd b, rnd *c); /* c = a mod b, 0 <= c < b */
/* num theory */
int rn_addmod(rni *a, rni *b, rni *c, rni *d); /* d = a + b (mod c) */
int rn_submod(rni *a, rni *b, rni *c, rni *d); /* d = a - b (mod c) */
int rn_mulmod(rni *a, rni *b, rni *c, rni *d); /* d = a * b (mod c) */
int rn_sqrmod(rni *a, rni *b, rni *c); /* c = a * a (mod b) */
int rn_invmod(rni *a, rni *b, rni *c); /* c = 1/a (mod b) */
void rn_gcd(rni *a, rni *b, rni *c); /* c = (a, b) */
void rn_lcm(rni *a, rni *b, rni *c); /* c = [a, b] */

int rn_mont_setup(rni *a, rnd *mp); /* setup the montgomery reduction */
void rn_mont_calc_norm(rni *a, rni *b); /* computes a = B**n mod b without
                                           division or multiplication, useful
                                           for normalizing numbers in a
                                           Montgomery system */
void rn_mont_reduce(rni *a, rni *m, rnd mp); /* computes x/R == x (mod N)
                                                via Montgomery Reduction */
int rn_exptmod(rni *a, rni *b, rni *c, rni *d); /* d = a**b (mod c) */
/* primality stuff */
void rn_pr_millrab(rni *a, rni *b, int *result); /* perform a Miller-Rabin
                                                    test of a to the base b
                                                    and store result in
                                                    "result" */
int rn_isprime(rni *a, int t);

/* callback for rn_prime_random, should fill dst with random bytes and
   return how many read [upto len] */
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

#include "mul/rn_mul_comba.c"
#include "sqr/rn_sqr_comba.c"
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

