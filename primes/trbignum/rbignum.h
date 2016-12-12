#ifndef RBIGNUM_H
#define RBIGNUM_H

#include <stdint.h>
#include <limits.h>
#include <stdio.h>

#define DEBUG 0

#if DEBUG
//add //sizeof(result) = max(sizeof(src1), sizeof(src2)) + 1;
/*
for (l=0,i-0; i<m; ++i) {
  l += (unsigned long long)src1[i] + src2[i];
  dest[i] = l;
  l >>= 32;
}*/

//mult //sizeof(result) = sizeof(a) + sizeof(b)
/*
costly:
unsigned long long tmp[n*n];
for (i=0; i<n; ++i)
  for (j=0; j<n; ++j)
    tmp[j*n+i] = (acc)a[i]*b[j];
*/
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

/* RAM
 * m[0],m[1],m[2],... 
 * Instructions
 * I_0,I_1,...
 *
 * arithmetic
 * a <- b * g (where * denotes an interger operation)
 *    ie +,-,x,floor(./.)
 * b and g are of the form c, m[a], m[m[a]]
 * (where c is an int constant, a is an unsigned int constant)
 * b * g ->eval->store in a
 *
 * branching
 * IF b <> g GOTO i
 * (where i is the index of an instruction, and <> a comparison operator
 *   =, !=, <, >, <=, >= and b,g are as above)
 * passes flow of control conditionally to instruction I_i */
#if !1
uint32_t carry=0;
for (i=0; i<len; ++i) {
  uint64_t tmp = n*(uint64_t)big[i] + carry;
  big[i] = tmp;
  carry = tmp >> 32;
}
if (carry) big[len++] = carry;
#endif

#endif /* RBIGNUM_H */
