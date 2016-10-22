/*
 * quadform.c
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
main(int argc, char *argv[])
{
  if (argc!=4) {
    printf("%s <a> <b> <c>\n", argv[0]);
    return(-1);
  }
  float numtr,denom,x1,x2;
  int a=atol(argv[1]);
  int b=atol(argv[2]);
  int c=atol(argv[3]);

  numtr=(b*b)-(4*a*c);
  denom=2*a;
  if (numtr==0) {
    x1=-b/denom;
    x2=x1;
  } else if (numtr>0) {
    x1=(-b+sqrt(numtr))/denom;
    x2=(-b-sqrt(numtr))/denom;
  } else if (numtr<0) {
    float r=-b/denom;
    float i=sqrt(fabs(numtr))/denom;
    printf("\nx₁\t%f + %fi", r,i);
    printf("\nx₂\t%f - %fi\n", r,i);
    return(0);
  }
  printf("\nx₁\t%f\nx₂\t%f\n", x1,x2);
  return(0);
}

