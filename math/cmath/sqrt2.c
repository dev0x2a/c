#include <stdio.h>
#include <math.h>

int main(void)
{
  /* 
   * compute (2)^(1/2)
   *
   * 1: X <- 1
   * 2: Y <- 2/X
   * 3: Z <- (X+Y)/2
   * 4: X <- Z
   * 5: if |X-Y| > eps, then goto line 2
   * 6: stop
   */
  /*  Line   X       Y       Z       Remarks
   * ------------------------------------------------
   *   1     1       *       *     X <- 1
   *
   *   2     1       2       *     Y <- 2/X
   *   3     1       2      3/2    Z <- (X+Y)/2
   *   4    3/2      2       2     X <- Z
   *   5    3/2      2       2     goto 2
   *
   *   2    3/2     4/3      2     Y <- 2/X
   *   3    3/2     4/3    17/12   Z <- (X+Y)/2
   *   4   17/12    4/3    17/12   X <- Z
   *   5   17/12    4/3    17/12   goto 2
   *
   *   2   17/12   24/17   17/12   Y <- 2/X
   *   3   17/12   24/17  577/408  Z <- (X+Y)/2
   *   4  577/408  24/17  577/408  X <- Z
   *   5  577/408  24/17  577/408  0 < X-Y < 0.003
   *
   *   6  577/408  24/17  577/408  stop
   */
  /* simplified alg
   *
   * 1: X <- 1
   * 2: Y <- 2/X
   * 3: X <- (X+Y)/2
   * 4: if |X-Y| > eps, then goto line 2
   * 5: stop
   */
  /*
   * X <- 1
   * do
   *   Y <- 2/X
   *   X <- (X+Y)/2
   * while |X-Y| > eps
   */

  float X, Y, eps;
  printf("enter epsilon ");
  scanf("%f", &eps);

  X = 1;
  do {
    Y = 2/X;
    X = (X+Y)/2;
  } while (fabs(X-Y) > eps);

  printf("approx (2)^(1/2) = %f\n", X);
  return 0;
}

