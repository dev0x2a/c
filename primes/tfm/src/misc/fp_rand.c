#include <tfm_private.h>

/* makes a pseudo-random int of a given size */
void fp_rand(fp_int *a, int digits)
{
  fp_digit d;
  fp_zero(a);
  if (digits <= 0)
    return;

  /* first place a random non-zero digit */
  do {
    d = ((fp_digit)abs(rand())) & FP_MASK;
  } while (d == 0);

  fp_add_d(a, d, a);
  while (--digits > 0) {
    fp_lshd(a, 1);
    fp_add_d(a, ((fp_digit)abs(rand())), a);
  }
  return;
}

