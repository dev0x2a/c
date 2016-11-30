#ifndef RBIGNUM_H
#define RBIGNUM_H

#include <stdint.h>
#include <limits.h>
#include <stdio.h>

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

#define BASE 65536

#define TESTSTRUCTS 1
#define TESTBITS 0
#define DEBUG 0

#if TESTSTRUCTS
struct integer {
  char c;
  struct integer *next;
};

typedef struct {
  int sign;
  int size;
  int *tab;
} rbignum_t;

struct bignum_st {
  size_t *d; /* pointer to array of BN_BITS2 bit chunks */
  /*BN_ULONG==size_t*/
  int top; /* index last used d +1 */
  int dmax; /* size of d array */
  int neg; /* 1 if num is negative */
  int flags;
};
typedef struct bignum_st bignum;

struct gcrypt_mpi {
  int alloced; /* array sie (# allocated limbs) */
  int nlimbs; /* # of valid limbs */
  int sign;
  unsigned flags; /* bit 0: array in secure mem space
                     bit 2: ptr to sme m_alloced data */
  size_t *d; /* array w/ limbs mpi_limb_t == size_t*/
};

typedef struct {
  int _mp_alloc; /* # *limbs* allocated and pointed to
                    by the _mp_d field */
  int _mp_size; /* abs(_mp_size) = # limbs last field
                   points to. If _mp_size negative, then
                   negative number */
  size_t *_mp_d; /* ptr to table mp_limb_t==size_t */
} __mpz_struct;
#endif
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
#if TESTBITS

#define SETBIT(b,n) ((n) |= 1 << (b))
#define CLRBIT(b,n) ((n) &= ~(1 << (b)))
#define TOGBIT(b,n) ((n) ^= 1 << (b))
#define NTHBIT(b,n) ((n) ^= (-(b) ^ (n)) & (1 << (n)))
#define CHKBIT(b,n,x) ((x) = ((n) >> (b)) & 1)

struct bits {
  unsigned int a:1;
  unsigned int b:1;
  unsigned int c:1;
};
struct bits mbits;

enum bitflags = {
  bitmask = 0x0000,
  bitflag0 = 1 << 0;
  bitflag1 = 1 << 1;
  biterr = 1 << 8;
};

/*
 * bitstate |= bitflag1;
 * bitstate &= ~bitflag0;
 * if (bit & biterr) {...}
 */
/* a=target var
 * b=bit num to act upon 0-n
 */
#define BIT_SET(a,b) ((a) |= ((uintmax_t)1<<(b)))
#define BIT_CLR(a,b) ((a) &= ~((uintmax_t)1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= ((uintmax_t)1<<(b)))
#define BIT_CHK(a,b) ((a) & ((uintmax_t)1<<(b)))

/* x=target var
 * y=mask
 */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK(x,y) (((x) & (y)) == (y))

typedef enum {ERROR = -1, FALSE, TRUE } LOGICAL;
#define BOOL(x) (!(!(x)))

#define BITOP(a,b,op) \
  ((a)[(size_t)(b)/(8*sizeof *(a))] op ((size_t)1<<((size_t)(b)%(8*sizeof *(a)))))

#define BITS_ CHAR_BIT //8
#define BIT_SET_(p,n) (p[(n)/BITS_] |= (0x80>>((n)%BITS_)))
#define BIT_CLR_(p,n) (p[(n)/BITS_] &= ~(0x80>>((n)%BITS_)))
#define BIT_ISSET_(p,n) (p[(n)/BITS_] & (0x80>>((n)%BITS_)))

#define bit_test(x,y) \
  ((((const char*)&(x))[(y)>>3] & 0x80 >> ((y)&0x07)) >> (7-((y)&0x07)))

void bittestf(void)
{
  unsigned char arr[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
  for (int ix=0; ix<64; ++ix)
    printf("bit %d is %d\n", ix,bit_test(arr, ix));
}

const unsigned char quickbytemask[8] = {
  0x01, 0x02, 0x04, 0x08,
  0x10, 0x20, 0x40, 0x80
};
#endif
#if DEBUG
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
#endif
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
