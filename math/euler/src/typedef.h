#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef unsigned char       u8;
typedef signed char         s8;
typedef unsigned short      u16;
typedef signed short        s16;
typedef unsigned long       u32;
typedef signed long         s32;
typedef signed long long    s64;
typedef unsigned long long  u64;
typedef unsigned int        uint;

typedef u_int32_t ubig;
#define LNUM 0xffffffffU

#ifndef EMIN
#define EMIN(a,b) ((a<b)?a:b)
#endif /* EMIN */

#ifndef EMAX
#define EMAX(a,b) ((a>b)?a:b)
#endif /* EMAX */


/* sieve byte table, ( > 3*5*7*11 ) */
#define TSIZE 256*1024

/* random max */
#define ERAND_MAX 2147483647

static u32 enext = 1;
u8 bittab[8] = {
  1,2,4,8,16,32,64,128
};

u8 ptab[9] = {
  2,3,5,7,11,13,17,19,23
};

#endif /* TYPEDEF_H */
