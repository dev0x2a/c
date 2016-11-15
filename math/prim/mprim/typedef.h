typedef unsigned char       u8;   /*              0 : 225           */
typedef signed char         s8;   /*           -128 : 127           */
typedef unsigned short      u16;  /*              0 : 65535         */
typedef signed short        s16;  /*         -32768 : 32767         */
typedef unsigned long       u32;  /*              0 : 4.294967295e9 */
typedef signed long         s32;  /* -2.147483648e9 : 2.147483647e9 */
typedef signed long long    s64;
typedef unsigned long long  u64;
typedef unsigned int        uint;

typedef u_int32_t ubig;
#define LNUM 0xffffffffU

/* sieve byte table, ( > 3*5*7*11 ) */
#define TSIZE 256*1024

