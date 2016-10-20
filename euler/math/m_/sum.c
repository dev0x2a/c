#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void
main(int argc, char *argv[])
{
  int i, num, lim;
  double cpu_usage;
  clock_t start, end;

  if (argc != 3) {
    fprintf(stderr, "%s sum Σ <num> <lim>\n", argv[0]);
    exit(-1);
  }
  start = clock();
  num = atoi(argv[1]);
  lim = atoi(argv[2]);

  int sum = 0;
  for (i=num; i<=lim; ++i) {
    sum += i;
  }
  printf(" %d\n", lim); 
  printf(" Σi = %d\n", sum);
  printf("i=%d\n", num);
  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("cpu time: %f\n", cpu_usage);
  exit(0);
}

