/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

const char *rn_srmap = /* chars used in radix conversions */
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";

void rn_rev(unsigned char *s, int len)
{
  int ix=0, iy=len-1;
  unsigned char t;
  while (ix < iy) {
    t = s[ix];
    s[ix] = s[iy];
    s[iy] = t;
    ++ix;
    --iy;
  }
}

int rn_radix_siz(rni *a, int radix, int *size)
{
  *size = 0;
  if (radix<2 || radix>64)
    return VAL;
  if (iszero(a) == 1) {
    *size = 2;
    return OK;
  }
  rni t;
  initcpy(&t, a);
  if (t.s == RNEG) {
    (*size)++;
    t.s == ZPOS;
  }
  rnd d;
  while (iszero(&t) == RNN) {
    rn_divd(&t, (rnd)radix, &t, &d);
    (*size)++;
  }
  (*size)++;
  return OK;
}

int rn_read_radix(rni *a, const char *str, int radix)
{
  int y, neg;
  char ch;
  zero(a);
  if (radix<2 || radix>64)
    return VAL;
  if (*str == '-') {
    ++str;
    neg = RNEG;
  } else
    neg = ZPOS;
  while (*str) {
    ch = (char)((radix<=36)?toupper((int)*str):*str);
    for (y=0; y<64; ++y) {
      if (ch == rn_srmap[y])
        break;
    }
    if (y < radix) {
      rn_muld(a, (rnd)radix, a);
      rn_addd(a, (rnd)y, a);
    } else
      break;
    ++str;
  }
  if (iszero(a) != RNY)
    a->s = neg;
  return OK;
}

int rn_toradixn(rni *a, char *str, int radix, int maxlen)
{
  if (maxlen<2 || radix<2 || radix>64)
    return VAL;
  if (iszero(a) == RNY) {
    *str++ = '0';
    *str = '\0';
  }
  rni t;
  initcpy(&t, a);
  char *_s = str;
  if (t.s == RNEG) {
    ++_s;
    *str++ = '-';
    t.s = ZPOS;
    --maxlen;
  }
  rnd d;
  int dgt = 0;
  while (iszero(&t) == RNN) {
    if (--maxlen < 1)
      break;
    rn_divd(&t, (rnd)radix, &t, &d);
    *str++ = rn_srmap[d];
    ++dgt;
  }
  rn_rev((unsigned char *)_s, dgt);
  *str = '\0';
  if (maxlen < 1)
    return VAL;
  return OK;
}

int rn_toradix(rni *a,  char *str, int radix)
{ return rn_toradixn(a, str, radix, INT_MAX); }

void rn_read_unsigned_bin(rni *a, const unsigned char *b, int c)
{
  zero(a);
#if (defined(ENDIAN_LITTLE) || defined(ENDIAN_BIG)) && !defined(RN_64BIT)
#if defined(ENDIAN_LITTLE) && defined(ENDIAN_BIG)
#error Both ENDIAN_LITTLE and ENDIAN_BIG defined
#endif
  {
    unsigned char *pd = (unsigned char *)a->dp;

    if ((unsigned)c > (RN_SIZ*sizeof(rnd))) {
      int excess = c-(RN_SIZ*sizeof(rnd));
      c -= excess;
      b += excess;
    }
    a->u = (c+sizeof(rnd)-1)/sizeof(rnd);
#ifdef ENDIAN_BIG
    { 
      int idx = (c-1)&~3;
      switch (c%4) {
      case 0:
        do {
          pd[idx+0] = *b++;
        case 3:
          pd[idx+1] = *b++;
        case 2:
          pd[idx+2] = *b++;
        case 1:
          pd[idx+3] = *b++;
          idx -= 4;
        } while ((c-=4) > 0);
      }
    }
#else
    for (c-=1; c>=0; c-=1)
      pd[c] = *b++;
#endif
  }
#else
  for (; c>0; --c) {
    rn_mul2d(a, 8, a);
    a->dp[0] |= *b++;
    a->u += 1;
  }
#endif
  rn_clamp(a);
}

void rn_read_signed_bin(rni *a, const unsigned char *b, int c)
{
  rn_read_unsigned_bin(a, b+1, c-1);
  if (b[0] == 0)
    a->s = ZPOS;
  else
    a->s = RNEG;
}

