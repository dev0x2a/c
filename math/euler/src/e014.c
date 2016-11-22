#include <stdio.h>

int main(void)
{
  int c, lim, max, thismax;
  long i, n, maxn, tmp;

  lim=1000000;
  c=max=0;

  for (i=3; i<ulim; i+=2) {
    n=tmp=i;
    do {
      if (tmp&1) {
        tmp=3*tmp+1;
        ++c;
      } else {
        tmp/=2;
        ++c;
      }
    } while (tmp!=1);
    thismax=c;
    if (thismax>max) {
      max=thismax;
      maxn=n;
    }
    c=0;
  }
  printf("%ld    %d\n", maxn,max);
  return(0);
}

