#include <tfm_private.h>

void fp_set(fp_int *a, fp_digit b)
{
  fp_zero(a);
  a->dp[0] = b;
  a->used = a->dp[0] ? 1 : 0;
}

