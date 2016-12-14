#include <stdio.h>
#include <stdlib.h>

void burn_stack(unsigned long len);
void zeromem(volatile void *out, size_t outlen);
int mem_neq(const void *a, const void *b, size_t len);

int main(int argc, char *argv[])
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

