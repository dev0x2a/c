#ifndef TYPEDEF_H
#define TYPEDEF_H

#define BASE 65536

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef unsigned int uint;

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
  size_t *_mp_d; /* ptr to table */
} __mpz_struct;

#ifndef BMAX
#define BMAX(a,b) (((a) > (b)) ?(a):(b))
#endif

#ifndef BMIN
#define BMIN(a,b) (((a) < (b)) ?(a):(b))
#endif

#endif /* TYPEDEF_H */
