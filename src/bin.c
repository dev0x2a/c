#include<stdio.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{ if(argc!=2){
    printf("%s <num> b10->b2\n",argv[0]);
    return(1);}
  int n=atol(argv[1]),k,u,i;
  if(n>255)u=31;
  else u=7;
  for(i=u; i>=0; --i){
    k=n>>i;
    if(k&1)putchar('1');
    else putchar('0');
  }
  putchar('\n');
  return(0);
}
