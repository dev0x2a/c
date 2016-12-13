#ifndef TYPEDEF_H
#define TYPEDEF_H
typedef signed char        s8;
typedef unsigned char      u8;
typedef signed short       s16;
typedef unsigned short     u16;
typedef signed long        s32;
typedef unsigned long      u32;
typedef signed long long   s64;
typedef unsigned long long u64;

#ifndef MIN
#define MIN(a,b) ((a<b)?a:b)
#endif /* MIN */

#ifndef MAX
#define MAX(a,b) ((a>b)?a:b)
#endif /* MAX */

/* (>3*5*7*11) */
#define LNUM 0xffffffffu
#define TSIZE 256*1024
#define CRAND_MAX 2147483647

#define FILENM __FILE__
#define LINENO __LINE__
#define EF EXIT_FAILURE
#define ES EXIT_SUCCESS

u8 bittab[8] = {1,2,4,8,16,32,64,128};
u8 ptab[9] = {2,3,5,7,11,13,17,19,23};

#endif /* TYPEDEF_H */
