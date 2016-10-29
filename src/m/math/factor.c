/*
 * factor.c
 * print the factorization of n
 */
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char*argv[])
{ if(argc!=2){
    printf("%s <num>\n",argv[0]);
    return(-1);
  }
  int n,d,r;
  n=atol(argv[1]);
  d=2;
  do{
    r=n%d;
    if(r==0){
      printf("%d ",d);
      n/=d;
    }else d+=1;
  }while(n>1);
  printf("\n");
  return(0);
}

