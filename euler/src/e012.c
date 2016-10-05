#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

//#define MAX 10000

typedef uint64_t u64;

int 
num_t(u64 n)
{
  u64 result = (n*(n + 1))/2;
  return result;
}

int
factor(u64 num)
{
  int num_factors = 0;
  for (u64 i=1; i<=num; ++i) {
    if (num%i == 0) {
      //printf("%"PRIu64" ", i);
      ++num_factors;
    }
    if (num_factors == 500) {
      //printf("factor 500""%"PRIu64" ", num_factors);
      exit(0);
    } 
  }
  return num_factors;
}

int
main(int argc, char *argv[])
{ 
  u64 num;
  int count;

  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  num = atoll(argv[1]);
  count = -1;

//  for (int i=0; i<=num; ++i) {
//    num_t(i);
//    ++count;
//    printf("%d\t%d\n", num_t(i), count);
//  }
  printf("\nnum: %d, (%d)triangle\n", num_t(num), num);

  num = num_t(num);
  //factor(num);
  printf("\nnum_factors: %d\n", factor(num));
  return 0;
}

