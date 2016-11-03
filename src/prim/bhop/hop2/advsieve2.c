int advsieve(hopsieve_t *sv)
{ int tmp,p,d;
  int mindex,dist;
  int rslt;
  
  dist=sv->S;
  mindex=sv->nindex;
  p=sv->pbuf[mindex];
  d=sv->dbuf[mindex];

  if(d==p)rslt=0;
  else rslt=1;

  while(d<dist){
    dist-=d;
    mindex+=d;
    if(mindex>=sv->S)mindex-=sv->S;
    tmp=p;
    p=sv->pbuf[mindex];
    sv->pbuf[mindex]=tmp;
    d=sv->dbuf[mindex];
    sv->dbuf[mindex]=tmp;
  }
  sv->pbuf[sv->nindex]=p;
  d-=dist;
  if(d==0)d=p;
  sv->dbuf[sv->nindex]=d;

  sv->n++;
  sv->nindex++;
  if(sv->nindex==sv->S)sv->nindex=0;
  return(rslt);
}

