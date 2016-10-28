#include<stdio.h>
#define DIGITS 9000
int main(){
  int N=DIGITS+9;
  int a[DIGITS+9];
  int x=0;
  a[0]=0;
  a[1]=2;
  for(int n=2;n<N;++n){
    a[n]=1;
  }
  for(;N>9;--N){
    for(int n=N-1;n>0;--n){
      a[n]=x%n;
      x=10*a[n-1]+x/n;
    }
    printf("%d",x);
  }
  printf("\n");
  return(0);
}

