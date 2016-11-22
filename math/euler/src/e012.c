#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef uint64_t u64;

int factor(u64 n)
{ int c=0;
  for(int i=1; i<=n; ++i){
    if(n%i==0)++c;
  }
  return(c);
}

int main(int argc,char*argv[])
{ if(argc!=2){
    printf("%s <num>\n",argv[0]);
    return(-1);
  }
  int init,c;
  u64 num;

  init=0;
  c=-1;
  num = atoll(argv[1]);
  for(int k=0 ;; ++k){
    int t;
    ++c;
    if(k%2==0)t=factor(k+1);
    else t=factor((k+1)/2);
    int total=init*t;
    if(total>500){
      printf("%d, t(%d)\n",(k*(k+1))/2,c);
      break;
    }
    init=t;
  }
  return(0);
}

