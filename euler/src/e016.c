#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long power(unsigned long long n, unsigned long long e);

int
main(int argc, char *argv[])
{
  unsigned long long b, n;
  clock_t start, end;
  double cpu_usage;

  if (argc != 3) {
    printf("%s <base> <exp>\n", argv[0]);
    return(-1);
  }
  start = clock();
  b = atoi(argv[1]);
  n = atoi(argv[2]);

  printf("%d^%d = %lld\n", b, n, power(b,n));

  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("cpu time: %1f\n", cpu_usage);
  return 0;
}

unsigned long long 
power(unsigned long long n, unsigned long long e)
{
  unsigned long long r;
  r = 1;
  while (e > 0) {
    if ((e&1) != 0)
      r *= n;
    n *= n;
    e >>= 1;
  }
  return r;
}
  
