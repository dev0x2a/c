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



#endif
