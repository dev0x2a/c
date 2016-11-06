#include<stdio.h>
#include<stdlib.h>

int
main(int argc,char *argv[])
{
  if(argc<2){
    fprintf(stderr,"usage: %s [FILE]\n",argv[0]);
    return(-1);
  }
  FILE *fp;
  int **a,**b;

  fp=argv[1];

