#include <stdio.h>
#define BITFLAG1 (1)
#define BITFLAG2 (2)
#define BITFLAG3 (4)
int main(void)
{ unsigned bitbucket=0U;
  bitbucket|=BITFLAG1;
  bitbucket&=~BITFLAG2;
  bitbucket^=BITFLAG3;
  if(bitbucket&BITFLAG3){
    return(1);
  }else{
    return(2);
  }
  return(0);
}

