#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include <math.h>
//#include <gmp.h>

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  clock_t start, end;
  double cpu_usage;

  start = clock();



  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time: %1f\n", cpu_usage);
  return 0;
}

