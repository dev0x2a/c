#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long power(long long n, long long e);
int modular(int b, unsigned int e, unsigned int m);

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
  //b = atoi(argv[1]);
  //n = atoi(argv[2]);

  printf("%lld\n", modular(2,1000,1));

  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("cpu time: %1f\n", cpu_usage);
  return 0;
}

long long 
power(long long n, long long e)
{
  long long r;
  r = 1;
  while (e > 0) {
    if ((e&1) != 0)
      r *= n;
    n *= n;
    e >>= 1;
  }
  return r;
}
  
int
modular(int b, unsigned int e, unsigned int m)
{
  int i;
  int r = 1;
  int p = b%m;

  for (i=0; i<sizeof(int)*8; ++i) {
    int lbit = 0x00000001&(e>>i);
    if (lbit)
      r = (r*p)%m;
  }
  return r;
}
  
