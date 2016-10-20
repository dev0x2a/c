#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
//#include <unistd.h>
//#include <math.h>
typedef uint64_t u64;

int 
main(int argc, char *argv[]) 
{
  u64 num;
  int count, prev;

  clock_t start, end;
  double cpu_usage;

  if (argc != 2) {
    printf("%s <num> to print collatz seq\n", argv[0]);
    return(-1);
  }
  start = clock();
  num = atol(argv[1]);
  count = 0;
  printf("%2"PRIu64" ", num);

  while (num != 1) {
    if (num&0x01) {
      prev = num;
      num = 3*num+1;
      printf("o %2"PRIu64" ", num);
      ++count;
    } else {
      num /= 2;
      if (prev&0x01) { 
        printf("\n     /\n e__/\n |\n%2"PRIu64" ", num);
        prev = num;
      } else {
        printf("\n |\n e\n |\n%2"PRIu64" ", num);
        prev = num;
      }
      ++count;
    }
  }
  //printf("1\n");
  printf("\n\ncount = %d", count);
  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time: %1f\n", cpu_usage);
  return 0;
}

