#define BASE 65536

typedef struct {
  int sign;
  int size;
  int *tab;
} rbignum_t;

struct bignum_st {
  size_t *d; /* pointer to array of BN_BITS2 bit chunks */
  int top; /* index last used d +1 */
  int dmax; /* size of d array */
  int neg; /* 1 if num is negative */
  int flags;
};
typedef struct bignum_st BIGNUM;

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
  size_t *_mp_d; /* ptr to table */
} __mpz_struct;

unsigned char first[1024];
unsigned char second[1024];
unsigned char result[1025];
unsigned char carry = 0;
unsigned int sum = 0;

for (size_t i=0; i<1024; ++i) {
  sum = first[i] + second[i] + carry;
  carry = sum-255;
}

d(a,b,c) {
  if(a>0^b>0)a=-a,printf("-");for(printf("%d.",a/b);
    c--;putchar(a/b+48))a=a%b*10;}



d(a,b,c){
  for (printf("%d.", a/b); c--; putchar((a=abs(a)%b*10)/abs(b)+48));
}


Fundamental Problems of Algorithmic Algebra by Chee Yap
