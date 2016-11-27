/*
 * factor-sieve.c: "hopping factor sieve"
 * original timestamp <98/06/19 14:57:38 galway>
 *
 * compile with cc -lm ...
 * http://www.math.uiuc.edu/-galway/SieveStuff
 */
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
/***/
#define B1 0.261497212847643
typedef unsigned int uns32_t;
#define ABITS_PER_WORD 5
#define BITS_PER_WORD 32
#define WORD_AMASK 0x1F
typedef uns32_t word_t;
typedef struct div_entry{
  uns32_t div;
  struct div_ent *next;
}divent_t;
typedef struct factor_entry{
  divent_t *divs;
  divent_t *lovers; /*leftovers*/
}fent_t;
typedef struct factor_sieve{
  uns32_t nn; /*current number*/
  uns32_t ps; /*current location*/
  /* size in units, data & div_tbl
   * have the same size */
  uns32_t size;
  fent_t *data;
  divent_t *divtbl;
}fsieve_t;
/* set bit n in bitarray (type *word) */
#define SET_BIT(bitarray,n)\
{bitarray[n>>ABITS_PER_WORD]|=(1<<(n&WORD_AMASK));}
/* clear bit n in bitarray (type *word) */
#define CLEAR_BIT(bitarray,n)\
{bitarray[n>>ABITS_PER_WORD]^=(1<<(n&WORD_AMASK));}
/* TEST_BIT n in bitarray for 0 or non-0 */
#define TEST_BIT(bitarray,n) (bitarray[n>>ABITS_PER_WORD]&(1<<(n&WORD_AMASK)))
/***/
/*
 * build an array of bits corresponding to the numbers 0..n
 * bits set to 1 correspond to composite numbers <= n
 */
word_t *build_bsieve(uns32_t n)/*build bit sieve*/
{ word_t *rslt,*dptr;/*result,destination pointer*/
  uns32_t N;
  uns32_t m,p;
  /***/
  N=(n+1+(1<<ABITS_PER_WORD))>>ABITS_PER_WORD;
  rslt=malloc(N*sizeof(word_t));
  dptr=rslt;
  while(N--!=0)*dptr++=0;
  /*remove some multiples of primes*/
  for(p=2; p*p<=n; ){
    for(m=2*p; m<=n; m+=p){
      SET_BIT(rslt,m);
    }do{
      p++;
    }while(TEST_BIT(rslt,p)!=0);
  }
  return(rslt);
}
/***/
fsieve_t *create_fsieve(uns32_t srt,uns32_t bound)/*create factor sieve*/
{ word_t *bsieve;
  fsieve_t *rslt;
  divent_t *divtbl,*next;
  fent_t *sdata;
  uns32_t p,k,p_o;/*p_o for p offset*/
  uns32_t c;/*prime count*/
  /***/
  bsieve=build_bsieve(bound);
  c=0;
  for(p=2; p<=bound; p++)if(TEST_BIT(bsieve,p)==0)c++;
  divtbl=malloc(c*sizeof(divent_t));
  /*more space than we need for sdata?*/
  k=0;
  for(p=2; p<=bound; p++){
    if(TEST_BIT(bsieve,p)==0){
      divtbl[k].div=p;
      divtbl[k].next=NULL;
      k++;
  }}
  sdata=malloc(c*sizeof(fent_t));
  for(k=0; k<c; k++){
    sdata[k].divs=NULL;
    sdata[k].lovers=NULL;
  }
  k=0;
  for(p=2; p<=bound; p++){
    if(TEST_BIT(bsieve,p)==0){
      /*compute offset (dist to next multiple of p)*/
      p_o=srt%p;
      if(p_o!=0)p_o=p-p_o;
      if(p_o<c){
        next=sdata[p_o].divs;
        sdata[p_o].divs=&divtbl[k];
        divtbl[k].next=next;
      }else{
        next=sdata[0].lovers;
        sdata[0].lovers=&divtbl[k];
        divtbl[k].next=next;
      }
      k++;
  }}
  free(bsieve);
  rslt=malloc(sizeof(fsieve_t));
  rslt->nn=srt;
  rslt->ps=0;
  rslt->size=c;
  rslt->data=sdata;
  rslt->divtbl=divtbl;
  return(rslt);
}
/*step "factor sieve" by one*/
void adv_fsieve(fsieve_t *s)
{ divent_t *divptr,*ndivptr,*next,*divs,*lovers;
  uns32_t ps,nps;
  uns32_t p,p_o;
  fent_t *sdata;
  /***/
  ps=s->ps;
  sdata=s->data;
  divs=sdata[ps].divs;
  sdata[ps].divs=NULL;
  lovers=sdata[ps].divs;
  sdata[ps].lovers=NULL;
  /*careful!
   *we might modify divptr before divptr->next*/
  divptr=divs;
  while(divptr!=NULL){
    ndivptr=divptr->next;
    p_o=divptr->div;
    if(p_o<=s->size){
      nps=ps+p_o;
      if(nps>=s->size)nps-=s->size;
      next=sdata[nps].divs;
      sdata[nps].divs=divptr;
      divptr->next=next;
    }else{
      /*we've "bumped into" ourselves*/
      next=sdata[ps].lovers;
      sdata[ps].lovers=divptr;
      divptr->next=next;
    }
    divptr=ndivptr;
  }
  /*do similar loop on leftovers*/
  divptr=lovers;
  while(divptr!=NULL){
    ndivptr=divptr->next;
    /***/
    p=divptr->div;
    p_o=(s->nn)%p;
    p_o=p-p_o;
    if(p_o<=s->size){
      nps=ps+p_o;
      if(nps>=s->size)nps-=s->size;
      next=sdata[nps].divs=divptr;
      divptr->next=next;
    }else{
      next=sdata[ps].lovers;
      sdata[ps].lovers=divptr;
      divptr->next=next;
    }
    divptr=ndivptr;
  }
  ps++;
  if(ps>=s->size)ps=0;
  s->ps=ps;
  s->nn+=1;
  return;
}
/***/
void usage(int argc,char*argv[])
{ fprintf(stderr,"%s <lim>\n",argv[0]);
  fprintf(stderr,"factors numbers & collects some stats up to lim\n");
  return;
}
/***/
int main(int argc,char*argv[])
{ unsigned int lim;
  uns32_t bound;
  uns32_t divc,n,p,c;
  double tdivc;
  fsieve_t *fsieve;
  divent_t *divs;
  /***/
  if(argc!=2){
    usage(argc,argv);
    exit(EXIT_FAILURE);
  }
  if(sscanf(argv[1],"%d",&lim)!=1){
    usage(argc,argv);
    exit(EXIT_FAILURE);
  }
  bound=sqrt(lim);
  if(bound*bound<lim)bound+=1;
  tdivc=0.0;
  c=0;
  for(fsieve=create_fsieve(2,bound);fsieve->nn<=lim;adv_fsieve(fsieve)){
    divs=fsieve->data[fsieve->ps].divs;
    if((divs==NULL)||(divs->div==fsieve->nn))c++;
    /*count prime divisors of current number, ignoring multiplicity
     *ie)8 has one prime div, 12 has two*/
    divc=0;
    n=fsieve->nn;
    for(; divs!=NULL; divs=divs->next){
      divc++;
      p=divs->div;
      while(n%p==0)n/=p;
    }
    if(n!=1)divc++;
    tdivc+=divc;
  }
  printf("%u primes in interval [2..%u]\n",c,lim);
  printf(" %.8f = avg number of prime divisors\n",tdivc/(lim-1));
  /*avg val bases of Thm430 of
   *AN INTRODUCTION TO THE THEORY OF NUMBERS, 5th Edition
   *--Hardy & Wright
   */
  printf(" %.8f predicted\n",B1+log(log((double)lim)));
  exit(EXIT_SUCCESS);
}

