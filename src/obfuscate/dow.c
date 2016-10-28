#include <stdio.h>

int
dow(int y, int m, int d)
{
  /* 1 <= m <= 12, y > 1752 (in the UK) */
  static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
  y-=m<3;
  return((y+y/4-y/100+y/100+t[m-1]+d)%7);
}

int
main(void)
{
  printf("%d\n", dow(2016,10,23));
  return(0);
}

