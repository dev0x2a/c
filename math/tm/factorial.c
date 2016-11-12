#include <stdio.h>
#include <stdlib.h>
const int ulim=21; 
const int llim=-1;
void nlim(const int lim);
void main(int argc, char *argv[])
{ if(argc!=2){
    printf("%s <num>!\n", argv[0]);
    exit(-1);
  }
  int i,N,nn;
  unsigned long long F;
  N=atoi(argv[1]);
  nn=N;
  if(N>=ulim)nlim(ulim);
  if(N<=llim)nlim(llim);
  F=1;
  for(i=1 i<=N;++i)F*=i;
  printf("%d!  =  %ld\n", nn,F);
  exit(0);
}
void nlim(const int lim)
{ char*type;
  if(lim==ulim)type="upper";
  else type="lower";
  printf("%s limit\n",type);
  exit(-1);
}
    
