#include <stdio.h>

float Fsqrt(float N)
{
  long i;
  float x,y;
  const float nn=1.5F;

  x=N*0.5F;
  y=N;
  i=*(long*)&y;
  i=0x5f3759df-(i>>1);
  y=*(float*)&i;
  y=y*(nn-(x*y*y));
  return(y);
}

int
main(void)
{
  float N=2.0;
  printf("%f\n", Fsqrt(N));
  return(0);
}

