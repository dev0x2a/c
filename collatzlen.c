#include <stdio.h>

#define LIM 500000
typedef unsigned int uint;

uint step(uint x)
{
  if (x&1)
    return (3*x+1);
  else
    return (x/2);
}

uint nseq(uint x0)
{
  uint i=1, x;

  if (x0==1 || x0==0)
    return i;

  x = step(x0);

  while (x!=1 && x!=0) {
    x = step(x);
    i++;
  }
  return i;
}

int main(void)
{
  uint i, m=0, im=0;

  for (i=1; i<LIM; ++i) {
    uint k = nseq(i);
    
    if (k > m) {
      m = k;
      im = i;
      printf("sequence length = %u for %u\n", m,im);
    }
  }
  return 0;
}

