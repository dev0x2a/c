#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long u64;

int factor(u64 n)
{
  int i, c=0;
  for (i=1; i<=n; ++i) {
    if (n%i==0)
      ++c;
  }
  return(c);
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  int k, init=0, c=-1;
  u64 num = atoll(argv[1]);

  for (k=0 ;; ++k) {
    int t;
    ++c;
    if (k%2==0)
      t=factor(k+1);
    else
      t=factor((k+1)/2);
    int total=init*t;
    if (total>500) {
      printf("%d, t(%d)\n", (k*(k+1))/2,c);
      break;
    }
    init=t;
  }
  return(0);
}

