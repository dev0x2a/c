/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

void rn_rshd(rni *a, int x)
{
  if (x >= a->u) {
    zero(a);
    return;
  }
  int y;
  for (y=0; y<a->u-x; ++y)
    a->dp[y] = a->dp[y+x];
  for (; y<a->u; ++y)
    a->dp[y] = 0;
  a->u -= x;
  rn_clamp(a);
}

void rn_lshd(rni *a, int x)
{
  int y = MIN(a->u+x-1, (int)(RN_SIZ-1));
  a->u = y+1;
  for (; y>=x; --y)
    a->dp[y] = a->dp[y-x];
  for (; y>=0; --y)
    a->dp[y] = 0;
  rn_clamp(a);
}

int rn_cntbit(rni *a)
{
  if (a->u == 0)
    return 0;
  int r = (a->u-1)*DGT_BIT;
  rnd q = a->dp[a->u-1];
  while (q > ((rnd)0)) {
    ++r;
    q >>= ((rnd)1);
  }
  return r;
}

int rn_cntlsb(rni *a)
{
  if (iszero(a) == 1)
    return 0;
  int x;
  for (x=0; x<a->u && a->dp[x]==0; ++x);
  rnd qq, q=a->dp[x];
  x *= DGT_BIT;
  if ((q&1) == 0) {
    do {
      qq = q&15;
      x += lnz[qq];
      q >>= 4;
    } while (qq == 0);
  }
  return x;
}

