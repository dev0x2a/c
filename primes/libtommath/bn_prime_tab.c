#include <tommath_private.h>
#ifdef BN_PRIME_TAB_C
/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place
 *
 * The library is free for all purposes without any express
 * guarantee it works
 *
 * Tom St Denis, tstdenis82@gmail.com, http://libtom.org */
const mp_digit ltm_prime_tab[] = {
  0x0002, 0x0003, 0x0005, 0x0007, 0x000b, 0x000d, 0x0011, 0x0013, 0x0017,
  0x001d, 0x001f, 0x0025, 0x0029, 0x002b, 0x002f, 0x0035, 0x003b, 0x003d,
  0x0043, 0x0047, 0x0049, 0x004f, 0x0053, 0x0059, 0x0061, 0x0065, 0x0067,
  0x006b, 0x006d, 0x0071, 0x007f,
#ifndef MP_8BIT
  0x0083, 0x0089, 0x008b, 0x0095, 0x0097, 0x009d, 0x00a3, 0x00a7, 0x00ad,
  0x00b3, 0x00b5, 0x00bf, 0x00c1, 0x00c5, 0x00c7, 0x00d3, 0x00df, 0x00e3,
  0x00e5, 0x00e9, 0x00ef, 0x00f1, 0x00fb, 0x0101, 0x0107, 0x010d, 0x010f,
  0x0115, 0x0119, 0x011b, 0x0125, 0x0133, 0x0137,

  0x0139, 0x013d, 0x014b, 0x0151, 0x015b, 0x015d, 0x0161, 0x0167, 0x016f,
  0x0175, 0x017b, 0x017f, 0x0185, 0x018d, 0x0191, 0x0199, 0x01a3, 0x01a5,
  0x01af, 0x01b1, 0x01b7, 0x01bb, 0x01c1, 0x01c9, 0x01cd, 0x01cf, 0x01d3,
  0x01df, 0x01e7, 0x01eb, 0x01f3, 0x01f7, 0x01fd, 0x0209, 0x020b, 0x021d,
  0x0223, 0x022d, 0x0233, 0x0239, 0x023b, 0x0241, 0x024b, 0x0251, 0x0257,
  0x0259, 0x025f, 0x0265, 0x0269, 0x026b, 0x0277, 0x0281, 0x0283, 0x0287,
  0x028d, 0x0293, 0x0295, 0x02a1, 0x02a5, 0x02ab, 0x02b3, 0x02bd, 0x02c5,
  0x02cf,

  0x02d7, 0x02dd, 0x02e3, 0x02e7, 0x02ef, 0x02f5, 0x02f9, 0x0301, 0x0305,
  0x0313, 0x031d, 0x0329, 0x032b, 0x0335, 0x0337, 0x033b, 0x033d, 0x0347,
  0x0355, 0x0359, 0x035b, 0x035f, 0x036d, 0x0371, 0x0373, 0x0377, 0x038b,
  0x038f, 0x0397, 0x03a1, 0x03a9, 0x03ad, 0x03b3, 0x03b9, 0x03c7, 0x03cb,
  0x03d1, 0x03d7, 0x03df, 0x03e5, 0x03f1, 0x03f5, 0x03fb, 0x03fd, 0x0407,
  0x0409, 0x040f, 0x0419, 0x041b, 0x0425, 0x0427, 0x042d, 0x043f, 0x0443,
  0x0445, 0x0449, 0x044f, 0x0455, 0x045d, 0x0463, 0x0469, 0x047f, 0x0481,
  0x048b,

  0x0493, 0x049d, 0x04a3, 0x04a9, 0x04b1, 0x04bd, 0x04c1, 0x04c7, 0x04cd,
  0x04cf, 0x04d5, 0x04e1, 0x04eb, 0x04fd, 0x04ff, 0x0503, 0x0509, 0x050b,
  0x0511, 0x0515, 0x0517, 0x051b, 0x0527, 0x0529, 0x052f, 0x0551, 0x0557,
  0x055d, 0x0565, 0x0577, 0x0581, 0x058f, 0x0593, 0x0595, 0x0599, 0x059f,
  0x05a7, 0x05ab, 0x05ad, 0x05b3, 0x05bf, 0x05c9, 0x05cb, 0x05cf, 0x05d1,
  0x05d5, 0x05db, 0x05e7, 0x05f3, 0x05fb, 0x0607, 0x060d, 0x0611, 0x0617,
  0x061f, 0x0623, 0x062b, 0x062f, 0x063d, 0x0641, 0x0647, 0x0649, 0x064d,
  0x0653
#endif
};
#endif
