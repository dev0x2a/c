#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define S 40
#define N 5

int dec_whl[S] = {
  3,3,5,4,4,3,5,5,4,3
};
int spec_whl[S] = {
  6,6,8,8,7,7,9,9,8
};
int tens_whl[S] = {
  6,6,6,5,5,7,6,6
};

int
main(int argc, char *argv[])
{
  if (argc!=2) {
    printf("%s <lim>\n", argv[0]);
    return(-1);
  }
  clock_t start, end;
  double cpu_usage;
  int lim;
  unsigned long long s;

  start = clock();
  lim = atoi(argv[1]);
  if (lim<1) {
    printf("%s lim < 1\n", argv[0]);
    return(-1);
  }

  //lim = N;
  s = 0;
  int i = 0;

  while (i<20) {
    for (int m=0; m<10,m<lim; ++m) {
      if (lim==i) exit(0);
      ++i;
      s += dec_whl[m];
      printf("%d\n",s);
    }
    for (int n=0; n<9; ++n) {
      if (lim==i) exit(0);
      ++i;
      s += spec_whl[n];
      printf("%d\n",s);
    }
  }

  if (lim>=20) {
    int j = 0;
    s += tens_whl[0];
      int k = 0;
    do {
      ++i;
      if (lim==i) exit(0);
      if (j>10) {
        j = 0;
        ++k;
      } else ++j;
      s += (tens_whl[0]+dec_whl[j]);
      printf("%d\n",s);
    } while (j!=9 && !lim);
  }
//  printf("%llu\n", s);
  
  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time: %1f\n", cpu_usage);
  return(0);
}

