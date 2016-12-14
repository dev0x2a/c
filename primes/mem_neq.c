/*
   Compare two blocks of memory for inequality.

   The usage is similar to that of standard memcmp(), but you can only test
   if the memory is equal or not - you can not determine by how much the
   first different byte differs.

   @param a     The first memory region
   @param b     The second memory region
   @param len   The length of the area to compare (octets)

   @return 0 when a and b are equal for len bytes, else they are not equal
*/
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
