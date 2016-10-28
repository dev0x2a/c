#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main(int argc, char *argv[])
{
  double X, Y, epsilon;

  if (argc != 2) {
    printf("%s <epsilon>\n", argv[0]);
    return(-1);
  }
  epsilon = atof(argv[1]);
  X = 1;
  
  do {
    Y = 2/X;
    X = (X+Y)/2;
  } while (fabs(X-Y) > epsilon);

  printf("sqrt(2) approx %e\n", X);
  return 0;
}

