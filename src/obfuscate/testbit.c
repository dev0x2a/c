#include <stdio.h>
int _atoi(const char *s)
{
  int i, n=0;
  for (i=0; s[i]>='0' && s[i]<='9'; ++i)
    n = 10*n+(s[i]-'0');
  return n;
}
#if 0
///{{{
int _lower(int c)
{
  if (c >= 'A' && c <= 'Z')
    return c+'a'-'A';
  else
    return c;
}

unsigned long int next = 1;
int _rand(void)
{
  next = next*1103515245+12345;
  return (unsigned int)(next/65536)%32768;
}

void _srand(unsigned int seed)
{
  next = seed;
}

/* squeeze: delete all c from s */
void _squeeze(char s[], int c)
{
  int i, j;

  for (i=j=0; s[i]!='\0'; ++i)
    if (s[i] != c)
      s[j++] = s[i];
  s[j] = '\0';
}

/* strcat: concatenate t to end of s; s must be big enougb */
void _strcat(char s[], char t[])
{
  int i, j;

  i = j = 0;
  while (s[i] != '\0') /* find end of s */
    i++;
  while ((s[i++] = t[j++]) != '\0') /* copy t */
    ;
}

/* sets to zero all but the low-order 7 bits of n */
//n = n & 0177;

/* turns bits on */
//x = x | SET_ON;

/* converts each 1-bit into a 0-bit and vice versa */
//x = x & ~077;

//z = (a > b) ? a : b; /* z = max(a, b) */

#include <stdint.h>

#ifndef BMAX
#define BMAX(a,b) (((a) > (b)) ?(a):(b))
#endif

#ifndef BMIN
#define BMIN(a,b) (((a) < (b)) ?(a):(b))
#endif
#endif
#if 0
struct bits {
  unsigned a:1,b:1,c:1;
};
enum bitflags = {
  bitmask = 0x0000,
  bitflag0 = 1 << 0;
  bitflag1 = 1 << 1;
  biterr = 1 << 8;
};
/* bitstate |= bitflag1;
 * bitstate &= ~bitflag0;
 * if (bit & biterr) {...}
 *//* a=target var
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
//}}}
#define SETBIT(b,n) ((n) |= 1 << (b))
#define CLRBIT(b,n) ((n) &= ~(1 << (b)))
#define TOGBIT(b,n) ((n) ^= 1 << (b))
#define NTHBIT(b,n) ((n) ^= (-(b) ^ (n)) & (1 << (n)))
#define CHKBIT(b,n,x) ((x) = ((n) >> (b)) & 1)
/* getbits: get n bits from position p */
unsigned _getbits(unsigned x, int p, int n)
{ return (x >> (p+1-n)) & ~(~0 << n); }

/* bitcount: count 1 bits in x */
int _bitcount(unsigned x)
{ int b;
  for (b=0; x!=0; x>>=1)
    if (x & 01) b++;
  return b;}

int main(int argc, char *argv[])
{
  const int cb = _atoi(argv[1]);
#if 0
  const int cn = _atoi(argv[2]);
  const int cx = _atoi(argv[3]);
  int b,n,x;
  b=cb;n=cn;
  printf("SETBIT(%d,%d) = %d\n", b,n,SETBIT(b,n));
  b=cb;n=cn;
  printf("CLRBIT(%d,%d) = %d\n", b,n,CLRBIT(b,n));
  b=cb;n=cn;
  printf("TOGBIT(%d,%d) = %d\n", b,n,TOGBIT(b,n));
  b=cb;n=cn;
  printf("NTHBIT(%d,%d) = %d\n", b,n,NTHBIT(b,n));
  b=cb;n=cn;x=2;
  printf("CHKBIT(%d,%d,%d) = %d\n", b,n,x,CHKBIT(b,n,x));
  printf("%d\n", _bitcount(11));
#endif
  int b=cb,u=_atoi(argv[2]);
  
  printf("%d | %d\t= %d\n", b,u,b|1);
  b=cb;
  printf("%d & %d\t= %d\n", b,u,b&1);
  b=cb;
  printf("%d ^ %d\t= %d\n", b,u,b^1);
  b=cb;
  printf("%d >> %d\t= %d\n", b,u,b>>1);
  b=cb;
  printf("%d << %d\t= %d\n", b,u,b<<1);
  b=cb;
  printf("~%d\t= %d\n", b,~b);
  b=cb;
  printf("!%d\t= %d\n", b,!~b);
  return 0;
}

