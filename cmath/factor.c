#include <stdio.h>

/*
 *  problem: factor 220            output tape
 * --------------------------------------------
 *  2 divides 220, quotient 110    2
 *  2 divides 110, quotient 55     2 2
 *  2 does not divide 110          2 2
 *  3 does not divide 110          2 2
 *  4 does not divide 110          2 2
 *  5 divides 110, quotient 11     5 2 2
 *  5 does not divide 11           5 2 2
 *  6 does not divide 11           5 2 2
 *  7 does not divide 11           5 2 2
 *  8 does not divide 11           5 2 2
 *  9 does not divide 11           5 2 2
 *  10 does not divide 11          5 2 2
 *  11 divides 11, quotient 1      11 5 2 2
 *  stop: quotient is 1            11 5 2 2
 */
/* 1) set d, the trial divisor, to 2
 * 2) compute the remainder r of division of n by d
 *    (denoted n%d, or "n modulo d")
 * 3) if r=0, then (a) print d on tape and move it one
 *                     unit to the right
 *                 (b) replace n by n/d
 *                
 *                Otherwise, replace d by d+1
 * 4) if n=1, then no more factors, so stop. Otherwise,
 *          go back to (2)
 */
/*
 * factor an integer n
 *
 * 1: d <- 2
 * 2: r <- n%d
 * 3: if r=0 then
 *      print d;
 *      n <- n/d;
 *      else
 *        d <- d+1
 * 4: if n=1
 *      then stop
 *      else goto line 2
 */
/*
 * if r=0
 *    then print d;
 *         n <- n/d;
 *    else if d^2 > n
 *         then print n;
 *              n = 1;
 *          else
 *            d = d+1
 */

int main(void)
{
  int n, d, r;
  printf("enter n ");
  scanf("%d", &n);

  d = 2;
  do {
    r = n%d;
    if (r == 0) {
      printf("%d ", d);
      n /= d;
    }
    else
      d += 1;
  } while (n > 1);
  printf("\n");
  return 0;
}

