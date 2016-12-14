/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"
#define PUT_LF 

void rn_printf(rni *a, int radix, FILE *o)
{
  int x;
  char buf[4096];
  rn_toradixn(a, buf, radix, INT_MAX);
  for (x=a->u-1; x>=0; --x) {
    fprintf(o, "%c", buf[x]);
  }
#ifdef PUT_LF
  putchar('\n');
#endif
  return;
}


void rn_set(rni *a, rnd b)
{
  zero(a);
  a->dp[0] = b;
  a->u = a->dp[0] ? 1 : 0;
}

int sys_main(int argc, char *argv[])
{
  unsigned long len1;
  volatile void *out;
  size_t len2, outlen;
  const void *a, *b;

  len2 = 2;
  a=b;
  printf("%d\n", mem_neq(a, b, len2));
  return 0;
}

/* Burn some stack memory
   @param len amount of stack to burn in bytes */
void burn_stack(unsigned long len)
{
   unsigned char buf[32];
   zeromem(buf, sizeof(buf));
   if (len > (unsigned long)sizeof(buf))
      burn_stack(len - sizeof(buf));
}

/* Compare two blocks of memory for inequality

   The usage is similar to that of standard memcmp(), but you can only test
   if the memory is equal or not - you can not determine by how much the
   first different byte differs.

   @param a     The first memory region
   @param b     The second memory region
   @param len   The length of the area to compare (octets)

   @return 0 when a and b are equal for len bytes, else they are not equal */
int mem_neq(const void *a, const void *b, size_t len)
{
   unsigned char ret = 0;
   const unsigned char *pa;
   const unsigned char *pb;

   pa = a;
   pb = b;
   while (len-- > 0) {
      ret |= *pa ^ *pb;
      ++pa;
      ++pb;
   }
   ret |= ret >> 4;
   ret |= ret >> 2;
   ret |= ret >> 1;
   ret &= 1;

   return ret;
}

/* Zero a block of memory
   @param out    The destination of the area to zero
   @param outlen The length of the area to zero (octets) */
void zeromem(volatile void *out, size_t outlen)
{
   volatile char *mem = out;
   while (outlen-- > 0) {
      *mem++ = '\0';
   }
}

