#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[]){
  long int n,N,f1,f2;
  N=atoi(argv[1]);
  f1=0;
  f2=1;
  printf("%d\n%d\n",f1,f2);
  for(int i=0; i<=N; ++i){
    n=f1+f2;
    f1=f2;
    f2=n;
    printf("%ld\n",n);
  }
  return(0);
}

