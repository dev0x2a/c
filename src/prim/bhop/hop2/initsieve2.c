/* init a pre-allocated sieve structure to start at n0 */
void initsieve(hopsieve_t *sv,int n0,int size,int *primes)
{ int p,d,tmp;
  int mindex;

  sv->n=n0;
  sv->nindex=0;
  for(sv->S=1; sv->S<=size; sv->S++){
    p=primes[sv->S-1];
    mindex=(p-n0%p)%p;
    while(mindex<sv->S-1){
      tmp=p;
      p=sv->pbuf[mindex];
      sv->pbuf[mindex]=tmp;
      d=sv->dbuf[mindex];
      sv->dbuf[mindex]=tmp;
      mindex+=d;
    }
    sv->pbuf[sv->S-1]=p;
    sv->dbuf[sv->S-1]=p-(n0%p+sv->S-1)%p;
  }
  sv->S=size;
}

