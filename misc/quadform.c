/*
 * quadform.c
 * quadratic formula solver
 * produces two results from input in the form of:
 *
 *    ax^2 + bx + c = 0
 *
 *  where a, b, & c are given via input, and
 *    x1 & x2 are outputs
 *
 *  answers on the complex plane not yet supported
 *    -nan => not a number
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int a;
static int b;
static int c;

int main()
{
  float numerator, denominator, x1, x2, real, i;  
  int type;

  printf("\nfor\t\tax^2 + bx + c\ninput\t\ta, b, c\noutput\t\tx1, x2\n\n");
  
  printf("a\t\t");
  scanf("%d", &a);

  printf("b\t\t");
  scanf("%d", &b);

  printf("c\t\t");
  scanf("%d", &c);

  numerator = (b * b) - (4 * a * c);
  denominator = 2 * a;

  if (numerator == 0)
    type = 1;

  else if (numerator > 0)
    type = 2;

  else if (numerator < 0)
    type = 3;

  switch(type)
  {
    case 1:   x1 = -b / denominator;
              x2 = x1;
              break;
    case 2:   x1 = (-b + sqrt(numerator)) / denominator;
              x2 = (-b - sqrt(numerator)) / denominator;
              break;
    case 3:   printf("\nroots are on the complex plane");
              real = -b / denominator;
              i = sqrt(fabs(numerator)) / denominator;
              printf("\nx1\t\t%f + %fi", real, i);
              printf("\nx2\t\t%f - %fi\n\n", real, i);
              return 0;
              break;
    default:  return (-1);
  }

  printf("\nx1\t\t%f\nx2\t\t%f\n\n", x1, x2);

  return 0;
}

