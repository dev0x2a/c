/*
 * project001.c
 * 001
 *
 * 09.28.2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 4.0 * atan(1.0);

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("<num> digits of pi\n");
    return(-1);
  }

  int long num = atol(argv[1]);



  printf("%lf\n", pi);

  printf("\n");
  return 0;
}
