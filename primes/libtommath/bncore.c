#include <tommath_private.h>
#ifdef BNCORE_C

/* Known optimal configurations

 CPU                    /Compiler     /MUL CUTOFF/SQR CUTOFF
-------------------------------------------------------------
 Intel P4 Northwood     /GCC v3.4.1   /        88/       128/LTM 0.32 ;-)
 AMD Athlon64           /GCC v3.4.4   /        80/       120/LTM 0.35

*/
int KARATSUBA_MUL_CUTOFF = 80, /* Min number of digits before Karatsuba
                                  multiplication is used */
    KARATSUBA_SQR_CUTOFF = 120, /* Min number of digits before Karatsuba
                                   squaring is used */
    TOOM_MUL_CUTOFF = 350, /* no optimal values of these are known yet
                              so set em high */
    TOOM_SQR_CUTOFF = 400;
#endif

