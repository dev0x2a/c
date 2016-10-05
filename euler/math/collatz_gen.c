#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
//#include <math.h>

/*  
 *  do not use on other systems
 */

typedef uint64_t u64;

int 
main(int argc, char *argv[]) 
{
  const char *of;
  const char *args[] = {"./" argv[0], argv[1], " >> ", of};
  char out[1000];

  u64 num;
  int count;

  if (argc != 2) {
    printf("%s <num> to print collatz seq\n", argv[0]);
    return(-1);
  }


  num = atol(argv[1]);
  count = 0;
  printf("%"PRIu64" ", num);

  while (num != 1) {
    
    if (num&0x01) {
      num = 3*num + 1;
      printf("- %"PRIu64" ", num);
      ++count;
    } else {
      num /= 2;
      printf("\n|\n%"PRIu64" ", num);
      ++count;
    }
  }
  //printf("1\n");
  printf("\n\ncount:\t%d\n", count);
  return 0;
}

