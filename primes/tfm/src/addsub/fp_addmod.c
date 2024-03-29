#include <tfm_private.h>

/* d = a + b (mod c) */
int fp_addmod(fp_int *a, fp_int *b, fp_int *c, fp_int *d) {
  fp_int tmp;
  fp_zero(&tmp);
  fp_add(a, b, &tmp);
  return fp_mod(&tmp, c, d);
}

