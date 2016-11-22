#include <stdio.h>
#define S 40

int dec_whl[S] = {
  3,3,5,4,4,3,5,5,4,3
};
int spec_whl[S] = {
  6,6,8,8,7,7,9,9,8,6
};
int tens_whl[S] = {
  6,6,6,5,5,7,6,6
};
int hund_whl[S] = {0,7};

int
main(void)
{
  int i, n, h;
  unsigned long long s;

  while (i<1001) {
    i=h=s=0;
A:  for (n=0; n<10; ++n,++i) {
      s+=dec_whl[n]+hund_whl[h];
    }
    for (n=0; n<10; ++n,++i) {
      s+=spec_whl[n];
    }
    for (n=0,k=0; n<8; ++k,++i) {
      if (k>9) { 
        k=0;
        ++n;
      }
      s+=tens_whl[n]+dec_whl[k];
    }
    if (i>=1000) {
      s+=8+dec_whl[0];
      break;
    }
    if (i%100) {
      s+=3*99;
      h=1;
      goto A;
    }  
    for (n=0; n<9; ++n) {
      s+=dec_whl[n]+7;
    }
  }
  printf("sum = %llu\n", s);
  return(0);
}

