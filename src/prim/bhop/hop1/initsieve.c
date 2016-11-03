/* init a pre-allocated sieve structure to start at n0 */
void initsieve(hopsieve_t *sv,int n0,int size,int *primes)
{ int m,p,tmp;
  
  sv->n=sv->n0=n0;
  for(sv->S=1; sv->S<=size; sv->S++){
    p=primes[sv->S-1];
    m=n0+(p-n0%p)%p;
    while(m<n0+sv->S-1){
      tmp=p;
      p=P(sv,m);
      P(sv,m)=tmp;
      m+=p-m%p;
    }
    P(sv,n0+sv->S-1)=p;
  }
  sv->S=size;
}

