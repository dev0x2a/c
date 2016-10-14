#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  long int i,j,f1,f2,up,sum,all;
  f1 = 0;
  f2 = 1;
  j = atoi(argv[1]);

  printf("fibonacci seq [0,%ld], summation of evens & of all\n", j);

  for (i=0; i<j; ++i) {
    if (i<=1) up = i;
    else {
      up = f1+f2;
      f1 = f2;
      f2 = up;
    }
    printf("%2ld ", up);
    if (up%2==0)
      sum += up;
    all += up;
  }
  printf("\nsum = (evens) %ld, (all) %ld\n", sum, all);
  return 0;
}

