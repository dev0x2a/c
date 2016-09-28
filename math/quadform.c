/*
 * quadform.c
 * quadratic formula solver
 *
 * produces two results from input of (a, b, c) in
 *
 *    ax^2 + bx + c = 0
 *
 *  where a, b, & c are given via input, and
 *    x1 & x2 are outputs
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main(int argc, char **argv)
{
  float numtr, denom, x1, x2, real, i;
  int type;

  if (argc != 4) {
    printf("%s <a> <b> <c>\n", argv[0]);
    return(-1);
  }

  int a = atol(argv[1]);
  int b = atol(argv[2]);
  int c = atol(argv[3]);

  numtr = (b * b) - (4 * a * c);
  denom = 2 * a;

  if (numtr == 0)
    type = 1;
  else if (numtr > 0)
    type = 2;
  else if (numtr < 0)
    type = 3;

  switch(type)
  {
    case 1:   x1 = -b / denom;
              x2 = x1;
              break;
    case 2:   x1 = (-b + sqrt(numtr)) / denom;
              x2 = (-b - sqrt(numtr)) / denom;
              break;
    case 3:   real = -b / denom;
              i = sqrt(fabs(numtr)) / denom;
              printf("\nx1\t%f + %fi", real, i);
              printf("\nx2\t%f - %fi\n", real, i);
              return 0;
    default:  return(-1);
  }

  printf("\nx1\t%f\nx2\t%f\n", x1, x2);
  return 0;
}

