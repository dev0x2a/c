#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int ulim = 21; 
const int llim = -1;

void nlimit(const int lim);

void
main(int argc, char *argv[])
{
  int i, num, onum;
  long long int factorial;
  double cpu_usage;
  clock_t start, end;

  if (argc != 2) {
    fprintf(stderr, "%s <num>!\n", argv[0]);
    exit(-1);
  }
  start = clock();
  num = atoi(argv[1]);
  onum = num;

  if (num >= ulim)
    nlimit(ulim);
  if (num <= llim)
    nlimit(llim);

  factorial = 1;
  for (i=1; i<=num; ++i) {
    factorial *= i;
  }
  printf("%d!  =  %ld\n", onum, factorial);
  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("cpu time: %f\n", cpu_usage);
  exit(0);
}

void
nlimit(const int lim)
{
  char *type;
  if (lim == ulim)
    type = "upper";
  else
    type = "lower";
  fprintf(stderr, "%s limit\n", type);
  exit(-1);
}
    
