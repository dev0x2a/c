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

#define BASE 16

struct integer {
  char c;
  struct integer *next;
};

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


/* 
 * notes
 *
 * RAM
 * m[0],m[1],m[2],... 
 * Instructions
 * I_0,I_1,...
 *
 *
 * arithmetic
 * a <- b * g (where * denotes an interger operation)
 *    ie +,-,x,floor(./.)
 * b and g are of the form c, m[a], m[m[a]]
 * (where c is an int constant, a is an unsigned int constant)
 * b * g ->eval->store in a
 *
 * branching
 *
 * IF b <> g GOTO i
 * (where i is the index of an instruction, and <> a comparison operator
 *   =, !=, <, >, <=, >= and b,g are as above)
 * passes flow of control conditionally to instruction I_i
 *
 * halt
 * halts execution 
 *
 * base-B
 */

#if 0
int table[489720];

int lookup(unsigned char *key)
{
  int index = hash(key);
  return table[index];
}

struct entry {
  unsigned char *key;
  int value;
  struct entry *next;
} *table[1<<20];

int lookup(unsigned char *key){
  int index = hash(key) % (1<<20);
  
  for (struct entry *e=table[index]; e!=NULL; e=e->next) {
    if (!strcmp(key, e->key))
      return e->value;
  }
  // not found
}

int hashstring(const char *s)
{
  /* take the result % hash table size */
  int key = 0;
  while (*s) {
    key = key*37 + *s++;
  }
  return key;
}
#endif
#include <stdio.h>
int test()
{
  int t;
  int a[200];
  int n,i,j,tmp,m,x;

  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    a[0] = 1; //array init 1
    m = 1;    //dgt counter

    tmp = 0; //carry
    for (i=1; i<=n; ++i) {
      for (j=0; j<m; ++j) {
        x = a[j]*i+tmp; //x contains dgt by dgt product
        a[j] = x%10; //dgt in pos j
        tmp = x/10;  //carry value that will be stored on later indices
        }
      while (tmp > 0) { //store carry in arr
        a[m] = tmp%10;
        tmp /= 10;
        m++; //dgt counter
      }
    }
    for (i=m-1; i>=0; --i)//print
      printf("%d", a[i]);
    putchar('\n');
  }
  return 0;
}
#if 0
uint32_t carry=0;
for (i=0; i<len; ++i) {
  uint64_t tmp = n*(uint64_t)big[i] + carry;
  big[i] = tmp;
  carry = tmp >> 32;
}
if (carry) big[len++] = carry;
#endif

#endif /* RBIGNUM_H */
