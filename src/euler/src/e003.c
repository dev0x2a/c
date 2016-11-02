#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char *argv[])
{ if(argc!=2){
    printf("%s <num> to print prime factors\n",argv[0]);
    return(-1);
  }
  unsigned long n;
  n=atol(argv[1]);
  while (n%2==0){
    printf("%d\n",2);
    n/=2;
  }
  for(int i=3; i<=sqrt(n); i+=2){
    while(n%i==0){
      printf("%d\n",i);
      n/=i;
    }
  }
  if(n>2)printf("%lu\n",n);
  return(0);
}

