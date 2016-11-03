#include"hopsieve.h"
#include"advsieve.c"
#include"initsieve.c"

int primes[11]={2,3,5,7,11,13,17,19,23,29,31};

int main(int argc,char*argv[])
{ int pcount;
  int pbuf[11];
  hopsieve_t sieve;
  
  pcount=0;
  sieve.pbuf=pbuf;
  initsieve(&sieve,36,11,primes);
  while(sieve.n<=1000){
    if(advsieve(&sieve))pcount++;
  }
  printf("%d primes in interval [36,1000]\n",pcount);
  return(0);
}

