/*
 * prime.c  --  Find primes in a range.
 * Copyright (c) 2006 by James Dow Allen
 *
 *  This program can be distributed or modified subject to
 *  the terms of the GNU General Public License (version 2
 *  or, at your option, any later version) as published by
 *  the Free Software Foundation.
 *
 * Supports only smallish integers (up to 4 billion or so).
 * (I have routines, requiring no other libraries, that handle
 *  primes up to 10 billion billion.  I'd probably send
 *  them to anyone who says "Pretty please.")
 */
#include	<stdlib.h>
#include	<stdio.h>

typedef	unsigned long int Integer;  /* assume this is 32-bits */
typedef unsigned long long int Largenum;  /* assume this is 64-bits */

/*
 * Following number must be a multiple of 30,
 *  at least 900 (for functionality) but even
 *  larger (for performance).
 */
#define	MTHRESH	720000

/*
 * Actually we have several versions
 *  of this routine, depending on whether
 *  intermediate results are 32-bit, 64-bit, or larger.
 * Here, just one version, perhaps good enough for 32-bit n
 */
int 
fermtst2(int a, Integer n)
{
	Integer i, b, resu;
	b = n - 1;
	for (i=1<<31; b && !(i&b); i>>=1)
		;
	resu = a;
	for (i>>=1; i; i>>=1) {
		resu = (resu * (Largenum)resu) % n;
		if (i & b) {
			resu = (a * (Largenum)resu) % n;
			resu %= n;
		}
	}
	return resu == 1;
}

int 
ispcandid(Integer x)
{
	return
		/* Caller must do 2, 3, 5 herself */
		(x%  7) &&
		(x% 11) && (x% 13) && (x% 17) && (x% 19) &&
		(x% 23) && (x% 29) && (x% 31) && (x% 37) &&
		(x% 41) && (x% 43) && (x% 47) && (x% 53) &&
		(x% 59) && (x% 61) && (x% 67) && (x% 71) &&
		(x% 73) && (x% 79) && (x% 83) && (x% 89) &&
		(x% 97) && (x%101) && (x%103) && (x%107) &&
		(x%109) && (x%113) && (x%127) && (x%131) &&
		(x%137) && (x%139) && (x%149) && (x%151) &&
		(x%157) && (x%163) && (x%167) && (x%173) &&
		(x% 79) && (x%181) && (x%191) && (x%193) &&
		(x%197) && (x%199) && (x%211) && (x%223) &&
		(x%227) && (x%229) && (x%233) && (x%239) &&
		(x%241) && (x%251) && (x%257) && (x%263) &&
		/*
		 * Prior to here, try all primes; after here,
		 *  just those that kill specific pseudoprimes.
		 * Note that these aren't costly: trying to
		 *  bypass fermtst2() is always a partial win.
		 */
		(x%271) && (x%277) && (x%281) && (x%293) &&
		(x%307) && (x%311) && (x%331) && (x%337) &&
		(x%349) && (x%367) && (x%373) && (x%379) &&
		(x%401) && (x%421) && (x%433) && (x%461) &&
		(x%487) && (x%541) && (x%547) && (x%601) &&
		(x%613) && (x%661) &&
		/* Preceding perfect for x < 2 billion;
		 *  following improves that to 2.7 billion.
		 */
		(x%353) && (x%443) && (x%499) && (x%727) &&
		(x%739) && (x%1093) &&
		(x%34501) /* nasty: 2380603501 = 34501 69001 */ &&
		1;
}

int
fermtrial[] = {
	2, 3, 5, 7, 11, 13, 17,
	10111,
};

int
isprime(Integer x)
{
	int	fix, f, fbnd;
	/*
	 * Save some cycles when x is small.
	 * It relies on divisibility by 601, 661
	 *  (and others) having been tested elsewhere.
	 *  Otherwise we'd need
	 *	fbnd = x < 721801 ? 5 : x < 42702661 ? 11 : 17;
	 */
	fbnd = x < 9006401 ? 5 : x < 42702661 ? 11 : 17;
	for (fix=0; (f = fermtrial[fix])<=fbnd; ++fix)
		if (!fermtst2(f, x))
			return 0;
	return 1;
}

void 
emit(Integer x)
{
	printf("%lu\n", x);
}

void
cemit(Integer x)
{
	if (ispcandid(x) && isprime(x))
		emit(x);
}

int 
main(int argc, char *argv[])
{
	Integer	x, last;
	int	resid, y, z;

	if (argc == 2) {
		x = last = atoll(argv[1]);
	} else if (argc == 3) {
		x = atoll(argv[1]);
		last = atoll(argv[2]);
	} else {
		printf("Usage: primelist #a #b -- list primes from a to b\n");
		printf("   Or: primelist #a    -- show a if prime\n");
		exit(1);
	}
	if (x < MTHRESH) {
		if (x < 3) {
			if (last >= 2)
				emit((Integer)2);
			x = 3;
		} else {
			x += !(x%2);
		}
		/*
		 * We "should" do the following with a variation
		 * of (Duff's) sieve as below, but
		 *   o  quite fast anyway, for MTHRESH < 1 million.
		 *   o  for real speed we might use table for
		 *        x < 100 million or so.
		 *   o  because range needs segmentation based on
		 *        last and 30-mult, 3 loops would be needed.
		 *   o  most of the small odds are prime anyway,
		 *        so avoiding 9,15,21,... isn't quite as
		 *        big a win as one might think.
		 */
		for (; x<MTHRESH; x+=2) {
			if (x > last)
				exit(0);
			for (y=3; z=x/y, y<=z; y+=2)
				if (z*y == x)
					goto bigbreak;
			emit(x);
		bigbreak:
			;
		}
	}
	resid = x%30;
	x -= resid;
	if (x+30 <= last) {
	/* Erastothenes' sieve is done a la Duff's Device! */
		switch (resid) {
			for (; x+30<=last; x+=30) {
		case 0: case 1:
				cemit(x+1);
		case 2: case 3: case 4:
		case 5: case 6: case 7:
				cemit(x+7);
		case 8: case 9: case 10: case 11:
				cemit(x+11);
		case 12: case 13:
				cemit(x+13);
		case 14: case 15: case 16: case 17:
				cemit(x+17);
		case 18: case 19:
				cemit(x+19);
		case 20: case 21: case 22: case 23:
				cemit(x+23);
		case 24: case 25: case 26:
		case 27: case 28: case 29:
				cemit(x+29);
			}
		}
	} else
		x += resid;
	for (x+=!(x%2); x<=last; x+=2)
		if (x%3 && x%5)
			cemit(x);
	exit(0);
}

