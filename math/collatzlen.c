#include <stdio.h>
#include <stdlib.h>
#define LIM 500000

unsigned step(unsigned x)
{
  if (x&1)
    return (3*x+1);
  else
    return (x/2);
}

unsigned nseq(unsigned x0)
{
  unsigned i=1, x;

  if (x0==1 || x0==0)
    return i;

  x = step(x0);
  while (x!=1 && x!=0) {
    x = step(x);
    i++;
  }
  return i;
}

int main(int argc, char *argv[])
{
  unsigned i, lim, m=0, im=0;

  if (argc < 2)
    lim = LIM;
  else
    lim = atoi(argv[1]);

  for (i=1; i<lim; ++i) {
    unsigned k = nseq(i);
    
    if (k > m) {
      m = k;
      im = i;
      printf("sequence length = %u for %u\n", m,im);
    }
  }
  return 0;
}

