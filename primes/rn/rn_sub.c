/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

void s_rn_sub(rni *a, rni *b, rni *c)
{
  int x, ou=c->u, obu=b->u;
  rnw t=0;
  c->u = a->u;
  for (x=0; x<obu; ++x) {
    t = ((rnw)a->dp[x])-(((rnw)b->dp[x])+t);
    c->dp[x] = (rnd)t;
    t = (t>>DGT_BIT)&1;
  }
  for (; x<ou; ++x)
    c->dp[x] = 0;
  rn_clamp(c);
}

void rn_sub(rni *a, rni *b, rni *c)
{
  int sa=a->s, sb=b->s;
  if (sa != sb) {
    c->s = sa;
    s_rn_add(a, b, c);
  } else {
    if (rn_cmp_mag(a,b) != RN_LT) {
      c->s = sa;
      s_rn_sub(a, b, c);
    } else {
      c->s = (sa==ZPOS) ? RNEG : ZPOS;
      s_rn_sub(b, a, c);
    }
  }
}

void rn_subd(rni *a, rnd b, rni *c)
{
  rni tmp;
  rn_set(&tmp, b);
  rn_sub(a, &tmp, c);
}

