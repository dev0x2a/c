#include"hopsieve2.h"
#include"advsieve2.c"
#include"initsieve2.c"

int primes[11]={2,3,5,7,11,13,17,19,23,29,31};

int main(int argc,char*argv[])
{ int pcount;
  int pbuf[11],dbuf[11];
  hopsieve_t sieve;
  
  pcount=0;
  sieve.pbuf=pbuf;
  sieve.dbuf=dbuf;
  initsieve(&sieve,36,11,primes);
  while(sieve.n<=1000){
    if(advsieve(&sieve))pcount++;
  }
  printf("%u primes in interval [36,1000]\n",pcount);
  return(0);
}

