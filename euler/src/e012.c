#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

typedef uint64_t u64;

int
factor(u64 n)
{
  int c = 0;
  for (int i=1; i<=n; ++i) {
    if (n%i == 0)
      ++c;
  }
  return c;
}

int
main(int argc, char *argv[])
{ 
  int init = 0;
  int count = -1;
  u64 num;

  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  num = atoll(argv[1]);

  for (int k=0 ;; ++k) {
    int t;
    ++count;
    if (k%2 == 0)
      t = factor(k+1);
    else
      t = factor((k+1)/2);
    int total = init*t;
    if (total > 500) {
      printf("%d, t(%d)\n", (k*(k+1))/2, count);
      break;
    }
    init = t;
  }
  return 0;
}

