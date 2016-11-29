#ifndef RBIGNUM_H
#define RBIGNUM_H

#include <stdint.h>

#ifndef USETYPEDEFS
#define USETYPEDEFS 1
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef unsigned int uint;
#endif

#ifndef NMAX
#define NMAX(_a,_b) ((_a>_b)?(_a):(_b))
#endif

#ifndef NMIN
#define NMIN(_a,_b) ((_a<_b)?(_a):(_b))
#endif

typedef struct {
  int sign;
  int size;
  int *tab;
} bignum;

bignum add(bignum a, bignum b); /* a+b */
bignum sub(bignum a, bignum b); /* a-b */
bignum mul(bignum a, bignum b); /* ab */
bignum rem(bignum a, bignum n); /* a/n -> remainder */
bignum amod(bignum a, bignum b, bignum n); /* a+b (mod n) */
bignum mmod(bignum a, bignum b, bignum n); /* ab (mod n) */
bignum emod(bignum a, bignum b, bignum n); /* a^b (mod n) */
bignum grand(int len); /* gen rand int w/ size --len-- bits */
bignum rprim(int len); /* gen rand prime w/ size --len-- bits
                          using milrab test */
int milrab(bignum a, int t); /* miller-rabin primality test on a
                                w/ security parameter t */

/*****/
/* gen RSA modulus n=pq, p,q are primes of size --len-- bit
 * also gives (e,d) as public,private exponent pair */
void keygen(bignum *n, bignum *e, bignum *d, int len);

/* input message --m--, public exponent --e--, RSA modulus --n--
 * returns corresponding ciphertext --c-- */
bignum cryptrsa(bignum m, bignum e, bignum n);

/* input ciphertext c, provate exponent --d--, RSA modulus --n--
 * returns corresponding plaintext --m-- */
bignum decryptrsa(bignum c, bignum d, bignum n);

/* gen RSA public key (e,n) and corresponding private key (d,n)
 * prompt user input for message --m-- to encrypt
 * output corresponding ciphertext encrypted w/ pub key (n,e)
 * apply decrypt alg w/ priv key (d,n)
 * check orig msg was recovered */
void testrsa(int len);

#endif
