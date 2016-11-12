#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int 
main(int argc, char *argv[]) 
{

  int long num;
  int count;

  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }

  num = atol(argv[1]);
  count = 0;

  while (num != 1) {
    //printf("%ld ", num);
    
    if (num&0x01) {
      num = 3*num + 1;
      ++count;
    }
    else {
      num /= 2;
      ++count;
    }
  }

  //printf("1\n");
  printf("count:\t%d\n", count);
  return 0;
}

