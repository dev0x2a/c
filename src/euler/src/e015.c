#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(int argc, char *argv[])
{
  int n;
  clock_t start, end;
  double cpu_usage;

  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  start = clock();
  n = atoi(argv[1]);
  ++n;

  unsigned long long a[n][n];
  for (int i=0; i<n; ++i) {
    a[i][0] = 1;
    a[0][i] = 1;
  }
  for (int i=1; i<n; ++i) {
    for (int j=1; j<n; ++j) {
      a[i][j] = a[i-1][j] + a[i][j-1];
    }
  }
  printf("%lld\n", a[n-1][n-1]);

  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time: %1f\n", cpu_usage);
  return 0;
}
