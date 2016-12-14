/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

void s_rn_add(rni *a, rni *b, rni *c)
{
  int x, y=MAX(a->u, b->u), ou=MIN(c->u, RN_SIZ);
  register rnw t=0;
  c->u = y;
  for (x=0; x<y; ++x) {
    t += ((rnw)a->dp[x])+((rnw)b->dp[x]);
    c->dp[x] = (rnd)t;
    t >>= DGT_BIT;
  }
  if (t!=0 && x<RN_SIZ) {
    c->dp[c->u++] = (rnd)t;
    ++x;
  }
  c->u = x;
  for (; x<ou; ++x)
    c->dp[x] = 0;
  rn_clamp(c);
}

void rn_add(rni *a, rni *b, rni *c)
{
  int sa=a->s, sb=b->s;
  if (sa == sb) {
    c->s = sa;
    s_rn_add(a, b, c);
  } else {
    if (rn_cmp_mag(a,b) == RN_LT) {
      c->s = sb;
      s_rn_sub(b, a, c);
    } else {
      c->s = sa;
      s_rn_sub(a, b, c);
    }
  }
}

void rn_addd(rni *a, rnd b, rni *c)
{
  rni tmp;
  rn_set(&tmp, b);
  rn_add(a, &tmp, c);
}

