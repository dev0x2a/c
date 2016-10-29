/*
 * calc.c
 * rudimentary calculator
 */
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char*argv[])
{ if(argc!=4){
    printf("%s <num> <+,-,x,/> <num>\n",argv[0]);
    return(-1);
  }
  float m, n, k;
  char op;
  m=atof(argv[1]);
  op=argv[2][0];
  n=atof(argv[3]);
  for(int i=0;i<=0;++i){
    switch(op){
      case '+':k=m+n;break;
      case '-':k=m-n;break;
      case 'x':k=m*n;break;
      case '/':k=m/n;break;
      default:printf("error\n");break;
    }
    printf("%f\n",k);
  }
  return(0);
}

