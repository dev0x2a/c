#include <stdio.h>

int deci_whl[11] = {
  0,3,3,5,4,4,3,5,5,4,3
};
int spec_whl[9] = {
  6,6,8,8,7,7,9,8,8
};
int tens_whl[8] = {
  6,6,5,5,5,7,6,6
};

int main(void)
{
  int i;
  unsigned long long s=0;

  for (i=0; i<11; ++i) {
    s+=deci_whl[i];
  }
  for (i=0; i<9; ++i) {
    s+=spec_whl[i];
  }
  for (i=0; i<8; ++i) {
    s+=10*tens_whl[i];
  }
  s+=8*36;
  s*=10;
  s+=3600+(90*99)+74;

  printf("-> %llu\n", s);
  return(0);
}

