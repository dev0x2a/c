#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ODD(x) (x & 1)
#define MAX_MEMO 1000000ull

uint32_t mem[MAX_MEMO] = {0};

uint32_t
chain(uint64_t n)
{
  if (n<=1) return(1);
  if (n<MAX_MEMO) {
    if (!mem[n])
      mem[n] = 1 + chain(ODD(n) ? 3 * n + 1 : n / 2);
    return(mem[n]);
  }
  return 1 + chain(ODD(n) ? 3 * n + 1 : n / 2);
}

int
main(int argc, char *argv[])
{
  uint64_t i;
  uint32_t max = 0;
  uint64_t maxi = 0;

  for (i=1; i<1000000ull; i++) {
    uint32_t res = chain(i);
    if (res>max) {
      max = res;
      maxi = i;
    }
  }
  printf ("%llu\n", (unsigned long long)maxi);
  return(EXIT_SUCCESS);
}

