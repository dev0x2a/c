/*
 * p002.c
 * 10.27.2016
 */
#include<stdio.h>

int fact(int n){
  if(n==0)return(1);
  return(n*fact(n-1));
}

int main(){
  int n;
  double s;
  for(n=s=0;n<34;++n){
    s+=(1.0/fact(n));
  }
  printf("%.50f\n",s);
  return(0);
}

