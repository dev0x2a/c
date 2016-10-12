#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <gmp.h>

typedef uint64_t u64;

u64 factorial(int n);
u64 C(int n, int r);

int
main(int argc, char *argv[])
{
  int i, k, n, r;
  clock_t start, end;
  double cpu_usage;

  if (argc != 3) {
    printf("%s <num> <num>\n", argv[0]);
    return(-1);
  }
  start = clock();
  i = atoi(argv[1]);
  k = atoi(argv[2]);

  n = i+k;
  r = k;


  printf("%"PRIu64"\n", C(n,r));
  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time: %1f\n", cpu_usage);
  return 0;
}

u64
factorial(int n)
{
  int i;
  u64 ret;
  ret = 1;
  for (i=1; i<=n; ++i) {
    ret *= i;
  }
  return ret;
}

u64
C(int n, int r)
{
  u64 a, b, c, ret;
  a = factorial(n);
  b = factorial(r);
  c = factorial(n-r);
  ret = a/(b*c);
  return ret;
}

