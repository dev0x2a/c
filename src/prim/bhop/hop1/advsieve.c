int advsieve(hopsieve_t *sv)
{ int m,p,tmp,rslt;
  
  m=sv->n;
  p=P(sv,m);
  if(m%p==0)rslt=0;
  else rslt=1;

  while(1){
    m+=p-m%p;
    if(m>=sv->n+sv->S)break;
    /* p hops into place, displaces prev prime */
    tmp=p;
    p=P(sv,m);
    P(sv,m)=tmp;
  }
  P(sv,sv->n)=p;
  sv->n++;
  return(rslt);
}

