#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define	ptsiz	(sizeof(pt)/sizeof(pt[0]))
#define	whsiz	(sizeof(whl)/sizeof(whl[0]))
#define	tabsiz (sizeof(tbl)/sizeof(tbl[0]))
#define	tsiz8	(tabsiz*8)

typedef unsigned char uchar;
double N = 9.007199254740992e15;

int	pt[] = {
	  2,  3,  5,  7, 11, 13, 17, 19, 23, 29,
	 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	 73, 79, 83, 89, 97,101,103,107,109,113,
	127,131,137,139,149,151,157,163,167,173,
	179,181,191,193,197,199,211,223,227,229,
};
double whl[] = {
	10, 2, 4, 2, 4, 6, 2, 6, 4, 2,
	 4, 6, 6, 2, 6, 4, 2, 6, 4, 6,
	 8, 4, 2, 4, 2, 4, 8, 6, 4, 6,
	 2, 4, 6, 2, 6, 6, 4, 2, 4, 6,
	 2, 6, 4, 2, 4, 2,10, 2,
};
uchar	tbl[1000];
uchar	bittab[] = {
	1,2,4,8,16,32,64,128,
};

void mrk(double, long);
void elim(void);

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		fprintf(stderr, "%s <num> <lim>\n", argv[0]);
		exit(1);
	}
	int i;
	double k, v, tmp;
  double lim=N, nn=atof(argv[1]);
	lim = N;
	if (argc > 2) {
		lim = atof(argv[2]);
		if (lim < nn)
			exit(0);
		if (lim > N)
			elim();
	}
	if (nn<0 || nn>N)
		elim();
	if (nn == 0)
		nn = 1;
	if (nn < 230) {
		for (i=0; i<ptsiz; ++i) {
			if (pt[i] < nn)
				continue;
			if (pt[i] > lim)
				exit(0);
			printf("%d\n", pt[i]);
			if (lim >= N)
				exit(0);
		}
		nn = 230;
	}
	modf(nn/2, &tmp);
	nn = 2.0*tmp+1;
  /* clear the sieve table */
	for (;;) {
		for (i=0; i<tabsiz; ++i)
			tbl[i] = 0;
    /* run the sieve */
		v = sqrt(nn+tsiz8);
		mrk(nn, 3);
		mrk(nn, 5);
		mrk(nn, 7);
		for (i=0,k=11 ;k<=v; k+=whl[i]) {
			mrk(nn,k);
			++i;
			if (i >= whsiz)
				i = 0;
		}
    /* now get the primes from the table
     * and printf them */
		for (i=0; i<tsiz8; i+=2) {
			if (tbl[i>>3] & bittab[i&07])
				continue;
			tmp = nn+i;
			if (tmp > lim)
				exit(0);
			printf("%.0f\n", tmp);
			if (lim >= N)
				exit(0);
		}
		nn += tsiz8;
  }
}

void mrk(double nn,long k)
{
	double t1;
	long j;
	modf(nn/k, &t1);
	j = k*t1-nn;
	if (j < 0)
		j += k;
	for (; j<tsiz8; j+=k)
		tbl[j>>3] |= bittab[j&07];
}

void elim(void)
{
	fprintf(stderr, "lim exceeded\n");
	exit(1);
}

