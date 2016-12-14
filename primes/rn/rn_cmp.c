/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

int rn_cmp(rni *a, rni *b)
{
  if (a->s==RNEG && b->s==ZPOS)
    return RN_LT;
  else if (a->s==ZPOS && b->s==RNEG)
    return RN_GT;
  else {
    if (a->s == RNEG)
      return rn_cmp_mag(b,a);
    else
      return rn_cmp_mag(a,b);
  }
}

int rn_cmpd(rni *a, rnd b)
{
  if ((b && a->u==0) || a->s==RNEG)
    return RN_LT;
  if (a->u > 1)
    return RN_GT;
  if (a->dp[0] > b) {
    return RN_GT;
  } else if (a->dp[0] < b) {
    return RN_LT;
  } else
    return RN_EQ;
}

int rn_cmp_mag(rni *a, rni *b)
{
  if (a->u > b->u) {
    return RN_GT;
  } else if (a->u < b->u) {
    return RN_LT;
  } else {
    int x;
    for (x=a->u-1; x>=0; --x) {
      if (a->dp[x] > b->dp[x])
        return RN_GT;
      else if (a->dp[x] < b->dp[x])
        return RN_LT;
    }
  }
  return RN_EQ;
}

