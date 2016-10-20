#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <inttypes.h>
#include <time.h>
//#include <gmp.h>

int 
main(int argc, char *argv[]) 
{
  if (argc!=2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  clock_t start, end;
  double cpu;
  unsigned long long N;
  int c;

  start = clock();
  N = atoi(argv[1]);
  if ((signed)N<1) {
    printf("%s: input < 1\n", argv[0]);
    return(-1);
  }
  c = 0;
  while (N!=1) {
    printf("%llu ", N);
    
    if (N&0x01) {
      N = (3*N+1)/2;
      c+=2;
    } else {
      N /= 2;
      ++c;
    }
  }
  printf("1");
  printf("\n\033[0;31mcount = %d\n", c);
  end = clock();
  cpu = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time  %1f\033[0m\n", cpu);
  return(0);
}

