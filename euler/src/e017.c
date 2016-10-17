#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dec_wheel[20] = {
  3,3,5,4,4,3,5,5,4,3,0,
};

int spec_wheel[20] = {
  6,6,7,7,7,7,9,9,8,0,
};

int tens_wheel[20] = {
  6,6,6,5,5,7,6,6,1,0,
};


int
main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("%s <lim>\n", argv[0]);
    return(-1);
  }
  int lim, s;
  clock_t start, end;
  double cpu_usage;

  start = clock();
  lim = atoi(argv[1]);

  if (lim < 1) {
    printf("%s lim < 1\n", argv[0]);
    return(-1);
  }

  s = 0;
  for (int i=0; i<lim; ++i) {
    int m, n, k, j;
    for (m=0; dec_wheel[m]!=0, m<lim; ++m) {
      s += dec_wheel[m];
    }
    if (lim<11) break;
    for (n=0; spec_wheel[n]!=0, n<lim-10; ++n) {
      s += spec_wheel[n];
    }
    if (lim<21) break;
    for (k=0, j=0;; ++j) {

      s += tens_wheel[k] + dec_wheel[j];
      if (j>9) {
        j = 0;
        ++k;
      }
    }
  }
  printf("%d\n", s);
  
  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time: %1f\n", cpu_usage);
  return 0;
}

