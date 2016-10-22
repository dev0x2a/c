#include <stdio.h>
#include <stdlib.h>
/* computation of primes S.Keleti Feb 26, 2016 */

int
main(void)
{
  int i,j,k;
  int n,m,p;
  int prim[15] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
  const unsigned char off[8] = {1,7,11,13,17,19,23,29};
  const unsigned char del[8] = {2,6,4,2,4,2,4,6};
  /* each bit position: 29, 23, 19, 17, 13, 11, 7, 1 */
  const unsigned char bitpos[30] = {
    0,0,1,1,1,1,1,1,2,2,
    2,2,3,3,4,4,4,4,5,5,
    6,6,6,6,7,7,7,7,7,7};
  const unsigned char primemask[30] = {
    0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xfd,0xff,0xff,
    0xff,0xfb,0xff,0xf7,0xff,0xff,0xff,0xef,0xff,0xdf,
    0xff,0xff,0xff,0xbf,0xff,0xff,0xff,0xff,0xff,0x7f};
  long int prime,primek,primes;
#define NHIST 256
#define PATNUM 10 
  int hist[NHIST];
  unsigned char *pat,sav,bitmask[8],delta;
  int bitsoff,byteoff[8];
  int pbyte,pbit;
  int kbyte,kbit;
  long int fbyte,fbit;
  long int lbyte,lbit;
  unsigned int twins,triples,quads,quints,sexts,tot,patsize;
  int max;
  long double twinfreq,tripfreq,quadfreq,quintfreq,sextfreq;

  /* get space for initial pattern */
  patsize=1;
  for (i=3; i<PATNUM; ++i) patsize*=prim[i];
  printf("allocating %d bytes\n", patsize);
  pat=(unsigned char*)malloc(patsize);
  if (pat==NULL) {
    printf("malloc failed\n");
    exit(-1);
  }
  printf("start\n");
  max=2;
  /* compute theoretical frequency of twin primes */
  twinfreq=1.0;
  tripfreq=1.0;
  quadfreq=1.0;
  quintfreq=1.0;
  sextfreq=1.0;
  for (p=1; p<2; ++p) {
    twinfreq*=(long double)(prim[p]-2)/(long double)(prim[p]-1);
    printf("after prime = %d: (twin prob = %8.5f%%)\n",
        prim[p],(double)(100.0*twinfreq));
  }
  for (; p<3; ++p) {
    twinfreq*=(long double)(prim[p]-2)/(long double)(prim[p]-1);
    printf("after prime = %d: (twin prob = %8.5f%%)\n",
        prim[p],(double)(100.0*twinfreq));
    tripfreq*=(long double)(prim[p]-3)/(long double)(prim[p]-1);
    printf("after prime = %d: (trip prob = %8.5f%%)\n",
        prim[p],(double)(100.0*tripfreq));
    quadfreq*=(long double)(prim[p]-4)/(long double)(prim[p]-1)/2;
    printf("after prime = %d: (quad prob = %8.5f%%)\n",
        prim[p],(double)(100.0*quadfreq));
    quintfreq*=(long double)(prim[p]-4)/(long double)(prim[p]-1);
    printf("after prime = %d: (quint prob = %8.5f%%)\n",
        prim[p],(double)(100.0*quintfreq));
    sextfreq*=(long double)(prim[p]-4)/(long double)(prim[p]-1)/2;
    printf("after prime = %d: (sext prob = %8.5f%%)\n",
        prim[p],(double)(100.0*sextfreq));
  }
  for (i=0; i<patsize; ++i) pat[i]=0xff;
  lbyte=0;
  /* generate more primes */
  prime=1; /* last prime filtered for */
  pbyte=0; /* byte of last prime */
  pbit=0; /* bit of last prime */
  primek=5;
  kbyte=0; /* byte of last prime of range */
  kbit=1; /* bit of last prime of range */
  primes=3;
  fbit=primek*primek; /* next prime squared */
  fbyte=fbit/30; /* next prime squared / 30 */
  fbit=bitpos[fbit-30*fbyte];  
  for (p=3; p<PATNUM+20; ++p) {
    do { /* get next prime */
      if (++pbit>=8) { pbit=0; ++pbyte; } /* next byte */
      prime+=del[pbit];
    } while (!(pat[pbyte]&(1<<pbit))); 
#if 0
printf("prime=%ld, pbyte=%d, pbit=%d %02x\n",prime,pbyte,pbit,pat[pbyte]);
#endif
  twinfreq*=(long double)(prime-2)/(long double)(prime-1);
  tripfreq*=(long double)(prime-3)/(long double)(prime-1);
  quadfreq*=(long double)(prime-4)/(long double)(prime-1);
  quintfreq*=(long double)(prime-5)/(long double)(prime-1);
  sextfreq*=(long double)(prime-6)/(long double)(prime-1);
  /* set up pattern */
  for (i=0; i<8; ++i) {
    bitsoff=off[i]*prime;
    byteoff[i]=bitsoff/30;
    bitmask[i]=primemask[bitsoff-byteoff[i]*30];
#if 0
printf("bitsoff=%d, byteoff[%d]=%d, bitmask[%d]=%02x\n",bitsoff,i,byteoff[i],i,bitmask[i]);
#endif
  }
  sav=pat[lbyte+byteoff[0]];
  /* remove multiples of prime */
  for (i=prime*(lbyte/prime); i<patsize-prime; i+=prime) {
    pat[i+byteoff[0]]&=bitmask[0]; /* n*30*prime + ( 1*prime) */
    pat[i+byteoff[1]]&=bitmask[1]; /* n*30*prime + ( 7*prime) */
    pat[i+byteoff[2]]&=bitmask[2]; /* n*30*prime + (11*prime) */
    pat[i+byteoff[3]]&=bitmask[3]; /* n*30*prime + (13*prime) */
    pat[i+byteoff[4]]&=bitmask[4]; /* n*30*prime + (17*prime) */
    pat[i+byteoff[5]]&=bitmask[5]; /* n*30*prime + (19*prime) */
    pat[i+byteoff[6]]&=bitmask[6]; /* n*30*prime + (23*prime) */
    pat[i+byteoff[7]]&=bitmask[7]; /* n*30*prime + (29*prime) */
  }
  for (j=0; j<8; ++j) { /* finish off the end */
    if (i+byteoff[j]>=patsize) break;
    pat[i+byteoff[j]]&=bitmask[j];
  }
  pat[lbyte+byteoff[0]]=sav; /* restore prime itself */
  /* get stats on new primes */
  twins=0;
  triples=0;
  quads=0;
  quints=0;
  sexts=0;
  tot=0;
  lbit=prime*prime;
  lbyte=lbit/30;
  if (lbyte>=patsize) break; /* do not have full range, done */
  lbit=bitpos[lbit-30*lbyte];  
#if 0
  for (i=fbyte; i<=lbyte; i++) {
#else
  for (i=0; i<patsize-1; ++i) {
#endif
    delta=pat[i]&((pat[i]>>1)|(pat[i+1]<<7)); /* get pattern of adjacent primes */
#if 0
    if (i==fbyte) delta &= 0xff<<fbit;
    else if (i==lbyte) delta &= ~(0xff<<lbit);
#endif
    /* delta per bit position 26424246 */
    if (delta&0x04) ++twins;
    if (delta&0x10) ++twins;
    if (delta&0x80) ++twins;
    delta=0x0f&((delta>>2)&(delta>>1)); /* get pattern of three primes */
    /* delta per bit position xxxxtttt */
    static char tripcnt[16] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
    triples+=tripcnt[delta];
    if (delta==0x06) ++quads;
    else if (delta==0x07) { ++quints; ++quads; }
    else if (delta==0x0e) { ++quints; ++quads; }
    else if (delta==0x0f) {
      ++sexts;
#if 0
      printf("sext starting @ %ld\n",(long int)i*30+7);
#endif
      quints+=2;
      ++quads;
    }
    /* get number of primes to tally */
    delta=pat[i];
#if 0
    if (i==fbyte) delta &= 0xff<<fbit;
    else if (i==lbyte) delta &= ~(0xff<<lbit);
#endif
    tot+=tripcnt[0x0f&delta];
    tot+=tripcnt[0x0f&(delta>>4)];
  }
  /* print primes */
  kbyte=fbyte;
  kbit=fbit;
  while (kbyte<patsize) {
    do { /* get next prime */
      if (++kbit>=8) { kbit=0; ++kbyte; } /* next byte */
      primek+=del[kbit];
    } while (!(pat[kbyte]&(1<<kbit))); 
#if 0
    printf("%d,",primek);
#endif
    ++primes;
    if (primek>=prime*prime) break;
  }
#if 0
  printf("\n");
#endif
  do { /* get previous prime */
    primek-=del[kbit];
    if (--kbit<0) { kbit=7; --kbyte; } /* prev byte */
  } while (!(pat[kbyte]&(1<<kbit))); 
  fbyte=lbyte;
  fbit=lbit;
  printf("primes=%ld, lbyte=%ld, %ld=%ld^2-%d, %d twin in %d (%9.7f%%, t=%9.7f%%) %d trip, %d quad, %d quin, %d sext\n",
    primes,lbyte,primek,prime,(int)(prime*prime-primek),twins,tot,100.0*twins/tot,
    (double)(100.0*twinfreq),triples,quads,quints,sexts);
  printf("%d triples in %d (%9.7f%%, t=%9.7f%%)\n",triples,tot,100.0*triples/tot,(double)(100.0*tripfreq));
  printf("%d quad in %d (%9.7f%%, t=%9.7f%%)\n", quads,tot,100.0*quads/tot,(double)(100.0*quadfreq));
  printf("%d quint in %d (%9.7f%%, t=%9.7f%%)\n", quints,tot,100.0*quints/tot,(double)(100.0*quintfreq));
  printf("%d sext in %d (%9.7f%%, t=%9.7f%%)\n", sexts,tot,100.0*sexts/tot,(double)(100.0*sextfreq));
  if (lbyte>=patsize) break; 
#if 1
  if (p%200==0) {
    printf("hist of %d in pattern:\n",patsize);
    for (i=0; i<NHIST; ++i) {
      hist[i]=0;
    }
    for (i=0; i<patsize; ++i) {
      ++hist[pat[i]];
    }
    for (i=0; i<NHIST; i+=8) {
      printf("hist[%02x]: %8d %8d %8d %8d %8d %8d %8d %8d\n",i,
          hist[i],hist[i+1],hist[i+2],hist[i+3],hist[i+4],hist[i+5],hist[i+6],hist[i+7]);
    }
  }
#endif
  }
  printf("done\n");
  free(pat);
  return(0);
}

