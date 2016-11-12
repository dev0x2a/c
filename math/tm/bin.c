#include <stdio.h>
#include <stdlib.h>
int main(int argc,char*argv[])
{
  if(argc!=2){
    printf("%s <num> b10->b2\n",argv[0]);
    return(-1);
  }
  int n,u;
  n=atol(argv[1]);
  if(n>255)u=31;
  else u=7;
  for(int i=u;i>=0;--i){
    if((n>>i)&1)printf("1");
    else printf("0");
  }
  printf("\n");
  return(0);
}

