#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int
main(int argc, char *argv[])
{
  clock_t start, end;
  double cpu_usage;

  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  start = clock();






  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("cpu time: %1f\n", cpu_usage);
  return 0;
}

