#include <stdio.h>
#define S 40

int dec_whl[S] = {
  3,3,5,4,4,3,5,5,4,3
};
int spec_whl[S] = {
  6,6,8,8,7,7,9,9,8
};
int tens_whl[S] = {
  6,6,6,5,5,7,6,6
};

int
main(void)
{
  int i;
  unsigned long long s;

  s = 0;
  i = 0;
  for (int n=0; n<10; ++n,++i) {
    s += dec_whl[n];
    printf("%llu\n",s);
  }
  for (int n=0; n<9; ++n,++i) {
    s += spec_whl[n];
    printf("%llu\n",s);
  }
  for (int n=0; n<8; ++n,++i) {
    s += tens_whl[n];
    printf("%llu\n",s);
  }
  printf("sum = %llu\n", s);
  return(0);
}

