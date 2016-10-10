#include <stdio.h>

int
main(void)
{
  int ulim, count;
  long int num, maxnum, tmp, i;
  int thismax, max;

  ulim = 1000000;
  count = 0;
  max = 0;

  for (i=3; i<ulim; i+=2) {
    num = i;
    tmp = i;
    do 
    {
      if (tmp&0x01) {
        tmp = 3*tmp + 1;
        ++count;
      } else {
        tmp /= 2;
        ++count;
      }
    } while (tmp!=1);
    //printf("num: %6d       count: %d\n", num, count);
    thismax = count;
    if (thismax > max) {
      max = thismax;
      maxnum = num;
    }
    count = 0;
  }
  printf("%d    %d\n", maxnum, max);
  return 0;
}

