#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define LIM 1000
int wheel[10] = {
  3,3,5,4,4,3,5,5,4,3
};

int
main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("%s <llim> <ulim>\n", argv[0]);
    return(-1);
  }
  int l, u, s;
  clock_t start, end;
  double cpu_usage;

  start = clock();
  l = atoi(argv[1]);
  u = atoi(argv[2]);

  if (l > u) {
    printf("%s llim > ulim\n", argv[0]);
    return(-1);
  }

  s = 0;
  for (int i=l; i<u; ++i) {
    s += wheel[j];
    printf("%d ", s);

  
  }


  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time: %1f\n", cpu_usage);
  return 0;
}

