/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

void rn_2exp(rni *a, int b)
{
  zero(a);
  if (b < 0)
    return;
  int z = b/DGT_BIT;
  if (z >= RN_SIZ)
    return;
  a->u = z+1;
  a->dp[z] = ((rnd)1)<<(b%DGT_BIT);
}

static int s_ispow2(rnd b, int *p)
{
  if ((b==0) || (b&(b-1)))
    return 0;
  int x;
  for (x=0; x<DGT_BIT; ++x) {
    if (b == (((rnd)1)<<x)) {
      *p = x;
      return 1;
    }
  }
  return 0;
}

