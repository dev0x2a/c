#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	tsize (sizeof(tbl)/sizeof(*(tbl+0)))
#define	wsize (sizeof(whl)/sizeof(*(whl+0)))
#define	psize (sizeof(pt)/sizeof(*(pt+0)))
#define tsiz8 (tsize*8)

double N = 9.007199254740992e15;
double whl[] = {
  10,2,4,2,4,6,2,6,4,2,4,6,6,2,6,4,2,6,4,6,8,4,2,4,
  2,4,8,6,4,6,2,4,6,2,6,6,4,2,4,6,2,6,4,2,4,2,10,2
};

unsigned char tbl[1000];
unsigned char bittab[] = {1,2,4,8,16,32,64,128};

int pt[] = {
  2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,
  97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,
  181,191,193,197,199,211,223,227,229
};

void mark(double n, long k)
{
  double r;
  long j;

  modf(n/k, &r);
  j = k*r-n;
  
  if (j < 0)
    j += k;
  for (; j<tsiz8; j+=k) {
    tbl[j>>3] |= bittab[j&07];
  }
}

void limit(void)
{
  puts("limits exceeded");
  exit(-1);
}

int main(int argc, char *argv[])
{
  if (argc <= 1) {
    printf("%s <start> <end> (primes) [,]\n", argv[0]);
    exit(-1);
  }

  int i;
  double k, v, tmp, lim, n;
  
  char c = (argc >= 4) ? ',': ' ';
    
  n = atof(argv[1]);
  lim = N;
  
  if (argc > 2) {
    lim = atof(argv[2]);
    if (lim < n)
      exit(0);
    if (lim > N)
      limit();
  }

  if (n<0 || n>N)
    limit();
  if (n == 0)
    n = 1;
  
  if (n < 230) {
    for (i=0; i<psize; ++i) {
      if (pt[i] < n)
        continue;
      if (pt[i] > lim)
        exit(0);
      printf("%d%c\n", pt[i],c);
      if (lim >= N)
        exit(0);
    }
    n = 230;
  }

  modf(n/2, &tmp);
  n = 2.*tmp+1;
  
  for (;;) {
    for (i=0; i<tsize; ++i)
      tbl[i] = 0;
    v = sqrt(n+tsiz8);
    mark(n, 3);
    mark(n, 5);
    mark(n, 7);
    
    for (i=0,k=11; k<=v; k+=whl[i]) {
      mark(n, k);
      ++i;
      if (i >= wsize)
        i = 0;
    }
    
    for (i=0; i<tsiz8; i+=2) {
      if (tbl[i>>3] & bittab[i&07])
        continue;
      tmp = n+i;
      if (tmp > lim)
        exit(0);
      printf("%.0f%c\n", tmp,c);
      if (lim >= N)
        exit(0);
    }
    n += tsiz8;
  }
}

