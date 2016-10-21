#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int 
main(int argc, char *argv[]) 
{
  if (argc!=2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  unsigned long long N;
  int c;

  N = atoi(argv[1]);
  if ((signed)N<1) {
    printf("%s: input < 1\n", argv[0]);
    return(-1);
  }
  c = 0;
  while (N!=1) {
    //printf("%llu ", N);
    
    if (N&1) {
      N=(((N<<1)+N)+1)>>1;
      //N=(3*N+1)>>1;
      c+=2;
    } else {
      N>>=1;
      ++c;
    }
  }
  //printf("1");
  printf("\n\033[0;31mcount = %d\033[0m\n\n", c);
  return(0);
}

