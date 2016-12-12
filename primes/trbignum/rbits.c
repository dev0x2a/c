#ifndef RBITS_H
#define RBITS_H
#include <stdint.h>

#ifndef BMAX
#define BMAX(a,b) (((a) > (b)) ?(a):(b))
#endif

#ifndef BMIN
#define BMIN(a,b) (((a) < (b)) ?(a):(b))
#endif

#define TESTBITS 1

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
 * b=bit num to act upon 0-n */
#define BIT_SET(a,b) ((a) |= ((uintmax_t)1<<(b)))
#define BIT_CLR(a,b) ((a) &= ~((uintmax_t)1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= ((uintmax_t)1<<(b)))
#define BIT_CHK(a,b) ((a) & ((uintmax_t)1<<(b)))

/* x=target var
 * y=mask */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK(x,y) (((x) & (y)) == (y))

typedef enum {ERROR = -1, FALSE, TRUE } LOGICAL;
#define BOOL(x) (!(!(x)))

#define BITOP(a,b,op) \
  ((a)[(size_t)(b)/(8*sizeof *(a))] op ((size_t)1<<((size_t)(b)%(8*sizeof *(a)))))

#define BITS_ CHAR_BIT //8
#define BIT_SET_(p,n) (p[(n)/CHAR_BIT] |= (0x80>>((n)%CHAR_BIT)))
#define BIT_CLR_(p,n) (p[(n)/CHAR_BIT] &= ~(0x80>>((n)%CHAR_BIT)))
#define BIT_ISSET_(p,n) (p[(n)/CHAR_BIT] & (0x80>>((n)%CHAR_BIT)))

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

#endif /* RBITS_H */
