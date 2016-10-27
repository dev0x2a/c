/*
 * p001.c
 * 09.28.2016
 */
#include <stdio.h>

int i,j,s,c,g;
int a[2801]={[0 ... 2800]=2e3};
int S=1e4;

int main(){
  for(i=2800; i; i-=14){
    s=0;
    for(j=i; j; --j){
      s=s*j+S*a[j];
      g=j*2-1;
      a[j]=s%g;
      s/=g;
    }
    printf("%04d",(c+s/S));
    c=s%S;
  }
  puts("");
  return(0);
}

