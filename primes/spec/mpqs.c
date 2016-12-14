/*
	This is a an implementation of the multiple polynomial
	quadratic sieve (mpqs), written by Scott Contini.  It uses
	large integer arithmetic routines from Arjen Lenstra's
	LIP code (files lip.c, lip.h, lip.o).

	The sieving code here has not been highly optimized.
	The purpose of this code is for comparison with my
	self initializing quadratic sieve (siqs) implementation.
	Any significant improvement in the sieving for mpqs can
	also be applied to siqs.

  It is assumed that the user of this program is familiar
  with my Master's thesis from the University of Georgia.

	To run this program (on Unix):
		you must have lip.o and lip.h in your directory

		select values for parameters (explained below)
		and put them in the code

		compile by doing something like:
		gcc -O2 lip.o mpqs.c -lm
		where mpqs.c is the name of this program

		That will create the executable "a.out".
		Typing a.out will run the program.  The
		program immediately looks for a "params" file,
		explained below.

		The program will regularly output updates on
		its progress until it is complete.  It will also
		put some files in your directory, some of which
		are useful for you to factor the number, and the
		other files useful to the program so that it can
		restart where it left off if it was interrupted.
		Every time one wants to factor a new number, they
		should remove the files left behind from the previous
		number factored.

	Parameters that you must select and put into the program:

		BLOCK_LENGTH tells what size blocks the sieve array
		will be broken into.

		NUM_BLOCKS determines the sieve length.  Sieving
		will be done from -M to +M where
		M = BLOCK_LENGTH * NUM_BLOCKS

		B is the upper bound for the largest prime in the
		factor base.  I used the letter "F" in my paper
		to represent this value.  Sorry for the discrepency:
		I'm too lazy to change it.

		there are a few other parameters in the program
		that you can play with, but it should not be
		necessary to mess with these to get somewhat
		efficient factoring.

	The "params" file must contain:

		The number being factored

		A machine number, in case more than one computer
		will be sieving on the same number.  If only one
		computer is sieving, then just use machine number
		equal to 0.

		The number of smooths to get before it should quit
		sieving.

		The name of the file to put the factor base primes
		in.

		The name of the file that the smooths should be put
		in.

		The name of the file that the partials should be put
		in.

		The name of the file that the partial-partials should
		be put in.

	Right now, there is no code for getting partial-partials,
	so that last file will be empty.  Here is a sample params
	file:

213373250047292900922963491789292983262625983360017824143019
0
100
good.primes
smooth
partials
pps

	This means:

		sieve on the number:
		213373250047292900922963491789292983262625983360017824143019
		(this is the number we are trying to factor)

		machine number is 0

		stop when 100 or more smooths are obtained

		put the factor base primes in a file called
		"good.primes"

		put the smooths in a file called "smooth"

		the partials go in the file "partials"

		the partial-partials go in the file "pps"


	As mentioned earlier, when the program is running, it
	outputs updates to its progress.  Assuming that you called
	the executable file "a.out", it will be outputting the cpu-time
	from the unix "ps" command.  It will also print "status:"
	followed by four numbers.  These four numbers are (in order)
	size of factor base, number of partial-partials obtained,
	number of partials obtained, and number of smooths obtained.
	These numbers also appear in the "status" file, where they
	are updated more frequently.


	The smooth file is in the following format:
 
	squareroot p_1 e_1 p_2 e_2 ... p_n e_n 0
 
	where squareroot is a squareroot of a smooth residue, and the p_i and
	e_i following it is the factorization of the residue.  If p_1 is -1,
	then the residue is negative.  If p_1 is not -1, then p_1 is the index
	of the factor base prime which divides the residue.  For example, if
	p_1 is 1 and if the first prime in the factor base file is 2, then 2
	divides the residue.  e_1 is the number of times p_1 divides the
	residue (the exponent of p_1).  The same is true for p_i and e_i, for
	i = 2 to n.
 
	The partial residue file is of the same format, except that
	it first contains one large prime which divides the residue.


	Once enough data is generated, you need to combine the data and
	use some linear algebra techniques to factor the integer.  I do
	not have linear algebra routines which I am allowed to
	distribute, so please don't ask me for these.  Thanks...

	Scott Contini
	(developed while I was graduate student at the University of Georgia)

	Copyright 1996 */
#include <stdio.h>
#include <math.h>
#include "lip.h"

#define BLOCK_LENGTH 150000	/* amount of sieve array to
					                     sieve upon at a time */
#define NUM_BLOCKS 10	/* M = BLOCK_LENGTH * NUM_BLOCKS */
#define B	60000	/* largest prime of factor base */
#define START 20 /* where to start sieving */
#define THRESH1 50
#define ERROR2 4
	/* note: we are assuming that any prime that divides the
	multiplier must have index less than START.  In other words,
	the primes that you sieve with are all larger than anything
	that divides the multiplier. */
#define MULT_FILE "multiplier"

char SMOOTH_FILE[1000],SEMI_FILE[1000],PP_FILE[1000],GOOD_PRIME_FILE[1000];

#if (THRESH1 > 64)
#define COMP 0x80808080
#else
#define COMP 0xc0c0c0c0
#endif
#define MAX_FB 210000   /* Max primes in Factor Base */

int	comp;
int rootN[MAX_FB];                  /* sqrt(N) mod primes[i] */
int	soln1[MAX_FB],soln2[MAX_FB];	/* for sieving */
int	ptr1[MAX_FB],ptr2[MAX_FB];	/* for sieving */
int primes[MAX_FB],                 /* primes in factor base */
    p_count;
char mprimes[START];			/* multiplier primes */
int	mp[10];				/* also multiplier primes */
int	mpc=0;
unsigned char accum[BLOCK_LENGTH+1000];
unsigned char log_p[MAX_FB];          /* logs of the primes in factor base */
verylong N=0,			/* number to factor */
	a=0,b=0,Nby2=0,a2=0,ainv=0;
unsigned char   thresh2;
int ssc,                            /* number of semi-smooth residues */
    smc,                            /* number of smooth residues */
    ppc;                            /* number of pps */
int STOP;                           /* When to stop sieving */
int MACHINE_NO;                     /* For parallel factoring */
verylong semi_thresh=0, pp_thresh=0;
verylong ztemp1=0, ztemp2=0, ztemp3=0;
int	FSM,FSS,FPP,F;			/* # smooths, semis, pps */
int	multiplier;
verylong B2=0;
int ssc=0, smc=0, ppc=0;
int INIT;
int M;/* length of sieve interval */
int smallp[14] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43};
FILE *fsmooth,*fsemi,*fadata,*fpp;

int main(void)
{
	FILE *fp, *status_fp;
	char cc;
	int i;
	double dthresh;
	int loopc=0;

	printf("Welcome to Multiple Polynomial Quadratic Sieve\n");
  fflush(stdout);
	printf("using THRESH1=%d ERROR2=%d\n",THRESH1,ERROR2);

	/* read in data from params file */
	fp=fopen("params","r");
	if (!fp) {
		printf("Need params file!\n");
		exit(1);
	}
	zfread(fp,&N);
	printf("trying to factor:\n  ");
	zwriteln(N); fflush(stdout);
	M = BLOCK_LENGTH*NUM_BLOCKS;
	printf("using M=%d (%d blocks of length %d)\n",
      M,NUM_BLOCKS,BLOCK_LENGTH);
	printf("and B=%d\n",B);
	fscanf(fp,"%d",&MACHINE_NO);
	printf("Machine number: %d\n", MACHINE_NO);
	while ((cc=fgetc(fp)) != '\n') ;
	fscanf(fp,"%d",&STOP);
	printf("stop sieving after %d smooths\n",STOP);
	while ((cc=fgetc(fp)) != '\n') ;
	for (i=0; (cc=fgetc(fp))!='\n'; ++i)
		GOOD_PRIME_FILE[i]=cc;
	GOOD_PRIME_FILE[i]='\0';
	printf("factor base primes will be put in file '%s'\n",
	   GOOD_PRIME_FILE);
	for (i=0; (cc=fgetc(fp))!='\n'; ++i)
		SMOOTH_FILE[i]=cc;
	SMOOTH_FILE[i]='\0';
	printf("smooths will be put in file '%s'\n",SMOOTH_FILE);
	for (i=0; (cc=fgetc(fp))!='\n'; ++i)
		SEMI_FILE[i]=cc;
	SEMI_FILE[i]='\0';
	printf("partials will be put in file '%s'\n",SEMI_FILE);
	for (i=0; (cc=fgetc(fp))!='\n'; ++i)
		PP_FILE[i]=cc;
	PP_FILE[i]='\0';
	printf("pps will be put in file '%s'\n",PP_FILE);
	fclose(fp);

	/* open output data files */
	fsmooth=fopen(SMOOTH_FILE,"a");
	fsemi=fopen(SEMI_FILE,"a");
	fpp=fopen(PP_FILE,"a");
	fadata= fopen("adata","a");

	/* get the multiplier */
	fp=fopen(MULT_FILE,"r");
	if (!fp) {
		printf("no multiplier given, no multiplier will be used!\n");
		multiplier = 1;
	}
	else {
		/* multiply N by the multiplier */
		fscanf(fp,"%d",&multiplier);
		zsmul(N,multiplier,&N);
		printf("kN = "); zwriteln(N);
	}
	fclose(fp);

	/* compute half of N */
	zsdiv(N,2,&Nby2);
	/* compute sieving thresholds */
	zintoz(B,&ztemp1);
	zsmul(ztemp1,128,&semi_thresh);	/* Keep semi-smooth if they are
					less than semi_thresh (Cannot be
					larger than B^2) */
	zsq(ztemp1,&B2);
	zsmul(B2,64*64,&pp_thresh);	/* largest partial partials that
					we will try to factor */
	/* The following code calculates the sieve threshold for the given
	parameters.  It then adjust the sieve threshold so that it is a power
	of 2.  This adjustment allows us to scan the sieve array much faster
	when we search for probable smooth residues. */
	dthresh= .5*NumBits(N)*log(2.0)+log((double)M)-
    NumBits(semi_thresh)*log(2.0)-ERROR2;
	thresh2= (unsigned char) dthresh;       /* sieving threshold */
	printf("sieve thresholds: %d %d\n",THRESH1,thresh2); fflush(stdout);
	INIT=128;
	while (!(INIT&THRESH1)) INIT>>=1;
	if (INIT != THRESH1) INIT<<=1;	/* INIT>=THRESH, INIT is power of 2 */
	INIT= INIT-THRESH1;
	comp=0;
	for (i=THRESH1+INIT; i<=128; i<<=1)
		comp += i;
	if (comp != (COMP& 0xff)) {
		printf("please recompile with COMP = 0x%x%x%x%x\n",
			comp,comp,comp,comp);
		exit(1);
	}
	thresh2 += INIT;
	printf("modified: %d %d %d\n",INIT,THRESH1+INIT,thresh2);
	/* a must be size sqrt (sqrt(2*N)/M).  The first time the
	program is ran, we need to compute this, and store it in
	the a variable (with some adjustments to it if we parallelize).
	a represents the previous leading coefficient.  We are pretending
	that the previous leading coefficient was sqrt(sqrt(2*N)/M).  The
	next value of a will be the next prime after this.
	If the program has already been ran, then just read in a from
	the "a_val" file. */
	fp = fopen("a_val","r");
	if (fp==NULL) {
		fclose(fp);
		zsmul(N,2,&ztemp1);
		zsqrt(ztemp1,&ztemp2,&ztemp3);	/* ztemp2 = sqrt(2*N) */
		zsdiv(ztemp2,M,&ztemp1);	/* ztemp1 = sqrt(2*N)/M */
		zsqrt(ztemp1, &a, &ztemp2);	/* a = sqrt(sqrt(2*N)/M) */
		zsqrt(a,&ztemp1,&ztemp2);	
		zsdiv(ztemp1,100,&ztemp1);	/* ztemp1 will be the adjustment
						"distance" for parallelizing. */
		zsmul(ztemp1,MACHINE_NO,&ztemp2);
		zadd(a,ztemp2, &a);	/* this should prevent overlap */
	} else {
		zfread(fp,&a);
		fclose(fp);
	}

	/* read in the factor base primes */
	fp=fopen(GOOD_PRIME_FILE, "r");
	if (fp != NULL) {
		int j;
		printf("reading in factor base primes!\n"); fflush(stdout);
		p_count=0;
		while(fscanf(fp, "%d", &primes[p_count]) > 0) {
			log_p[p_count]=(unsigned char) (log((double)
            primes[p_count]) +.5);
			i = primes[p_count];
			if (i==2) {
				if (multiplier %2 ==1) {
					rootN[0]=1;
					mprimes[0] = 0;
				} else {
					rootN[0]=0;
					mprimes[0]= 1;
					mp[mpc++] = 0;
				}
				p_count++;
				continue;
			}
			/* if prime divides the multiplier then we
			must treat it a different way */
			j = multiplier%i;
			if (j==0 && p_count>=START) {
				printf("Error: multiplier too large.\n");
				exit(1);
			}
			if (j==0) {
				mprimes[p_count]=1;
				mp[mpc++]=p_count;
			} else {
				if (p_count < START)
					mprimes[p_count] = 0;
				/* calculate the sqrt of N mod each prime in
				the factor base */
				j = zsdiv(N,i,&ztemp3);
				if (j==0) {
					printf("N is divisible by %d\n",j);
					exit(1);
				}
				rootN[p_count]=sqrtmod(j, i);
			}
			p_count++;
		}
	printf("done reading factor base primes\n"); fflush(stdout);
	fclose(fp);
  } else {
		printf("creating factor base primes file!\n"); fflush(stdout);
		fclose(fp);
		fp=fopen(GOOD_PRIME_FILE, "w");
		primes[0] = 2;
		fprintf(fp,"2\n");
		log_p[0]=(unsigned char) (log((double) 2.0)+.5);
		if (multiplier%2 ==1) {
			rootN[0]=1;
			mprimes[0] = 0;
		} else {
			rootN[0]=0;
			mprimes[0]= 1;
			mp[mpc++]=0;
		}
		p_count=1;
		zpstart();
		while ((i = zpnext()) < B) {
			register int j,js;
			if (i==2) {
				printf("need larger PRIM_BND for this factor
				   base\n");
				exit(1);
			}
			j = zsmod(N,i);
			if (j==0) {
				if (multiplier%i != 0) {
					printf("N is divisible by %d\n",i);
					exit(1);
				}
				if (p_count >= START) {
					printf("Error: multiplier too large.\n");
					exit(1);
				}
			} else if ((js=zjacobis(j,i)) == -1)
				continue;
			primes[p_count] = i;
			fprintf(fp,"%d\n",i);
			if (p_count < START) {
				if (j==0) {
					mp[mpc++]=p_count;
					mprimes[p_count] = 1;
				} else {
					mprimes[p_count] = 0;
				}
			}
			rootN[p_count]=sqrtmod(j,i);
			log_p[p_count]=(unsigned char) (log((double) i)+.5);
			p_count++;
		}
		fclose(fp);
	}
	primes[p_count]=0;

	/* get data from status file */
	status_fp=fopen("status","r");
	if (status_fp != NULL) {
		fscanf(status_fp,"%d",&F);   /* # good primes */
		fscanf(status_fp,"%d",&FPP); /* # pps */
		fscanf(status_fp,"%d",&FSS); /* # semi */
		fscanf(status_fp,"%d",&FSM); /* # smooth */
		fclose(status_fp);
  } else {
		fclose(status_fp);
		status_fp=fopen("status","w");
		fprintf(status_fp,"%d 0 0 0\n",p_count);
		F=p_count;
		FPP=0;
		FSS=0;
		FSM=0;
		fclose(status_fp);
  }
	printf("sieving begins at %d\n",primes[START]); fflush(stdout);
	system("date"); system("hostname");

	/* start main loop */
	while (FSM < STOP) {
		ppc = 0;
		ssc = 0;
		smc = 0;
		if ((loopc&63) == 0) {
			printf("\nstatus: %d %d %d %d\n\n",F,FPP,FSS,FSM);
			system("ps -aux| grep a.out");
			fflush(stdout);
		}
		get_coeffs();		/* get new value of a, b */
		compute_roots();
		sieve();
		/* update smooth counts, etc... */
		FPP += ppc;
		FSS += ssc;
		FSM += smc;
		status_fp=fopen("status","w");
		fprintf(status_fp,"%d %d %d %d\n",F,FPP,FSS,FSM);
		fclose(status_fp);

		fflush(fsemi);
		fflush(fsmooth);
		fflush(fpp);

		loopc++;
	}
	printf("%d smooth equations\n%d semi-smooth equations\n",FSM,FSS);
	printf("%d partial partials\n",FPP);
	system("ps -aux| head |grep a.out");
	fclose(fsmooth);
	fclose(fsemi);
	fclose(fpp);
	fclose(fadata);
}
/* Function: sqrtmod
 
   Description: Calculates the squareroot of a mod prime p.
	Uses the RESSOL algorithm of Shanks.  For description of algorithm,
	see:  An Introduction to the Theory of Numbers, 5th edition.
	Authors: Niven, Zuckerman, and Montgomery.  Pages 110-114.
 
   Always return the smallest squareroot */
int sqrtmod(int a, int p)
{ 
	register long long r,s,c;
	long long m,n,k,kprime,i,j;
 
	/* if number is small then search for soultion */
	if (p<50 || (p<200 && p&2==0))
		for (i=1; i<p; ++i)
			if (i*i%p == a) return i;
	if (p&2==1) { /* p == 3 mod 4 */
		s=expmod((long long) a,(long long) ((p+1)>>2),(long long) p);
		if (s > (p>>1)) return p-s;
		else return s;
  }
	kprime= -1; k=0;
	m=p-1;
	while ((m&1)==0) k++, m>>=1;
 
	/* perform two fast exponentiations at the same time below */
	s=(m+1)>>1; c=a; r=1; n=1;
	for (i=0; (j=(1<<i))<=m; ++i) {
		if (m&j) n=(n*c) % p;
		if (s&j) r=(r*c) % p;
		c=(c*c)%p;
  }
	while(1) {
		if (n==1)
			if (r > (p>>1)) return p-r;
			else return r;
		if (kprime < 0) {
			for (i=0 ;; ++i) {
				c=primes[i];
				if (jacobi((int) c,p)==-1) break;
			}
			c=expmod(c,m,(long long) p);
		}
		s=n;
		for (kprime=1 ;; ++kprime) {
			s=(s*s)%p;
			if (s==1) break;
    }
		s=c;
		for (i=0; i<k-kprime-1; ++i)
			s=(s*s) % p;
		r=(s*r) % p; c=(s*s) % p; n=(c*n) % p; k=kprime;
	}
}

/* Function: expmod
 
   Description: calculates and returns a^2 mod n.  Use the simple,
        recursive algorithm */
int expmod(long long a, long long e, long long n)
{
	long long tmp;
	if (e==1) return a % n;
	if (e&1) return (a*expmod(a,e-1,n)) % n;
	tmp = expmod(a,e>>1,n);
	return (tmp*tmp) % n;
}

/* Function: jacobi
 
   Description: calculates and returns the jacobi symbol
 
   Note: The jacobi symbol is the same as the Legendre symbol mod a prime */
int jacobi(int m, int n)
{
	int t;
	if (m>n) m=m%n;
	if (m==0) return 0;
	if (m==1) return 1;
	if (m==2) {
		if (n&1==0) return 0;
		t=n&7; /* t = n % 8 */
		if (t==1 || t==7) return 1;
		return -1;
	}
	if ((m&1)==0)
		return jacobi((m>>1),n)*jacobi(2,n);
	if ((m&3)==3 && (n&3)==3) return -jacobi(n,m);
	return jacobi(n,m);
}

int NumBits(verylong a)
{
	int i,b,c;
	b=a[a[0]];
	c=0;
	while (b>0)
		b>>=1, c++;
	return NBITS*(a[0]-1)+c;
}

/* This routine just searches for the next prime after
	a which has the property that N is a quadratic residue
	mod it.  Once that is found, this becomes the new value of
	a and b is computed so that b^2 == N mod a^2, and b is between
	0 and a^2/2 */
void get_coeffs(void)
{
	static char array[99];
	register int i,j,k,p;
	FILE *fp;
loop:
	/* sieve for the next prime */
	memset(array, 0, 99);
	zsadd(a,1,&a);	/* start sieving at one more than
				             previous a */
	/* trial divide by smallp array */
	for (k=0; k<14; ++k) {
		p = smallp[k];
		j=zsdiv(a,p,&ztemp1);	/* j is remainder after
					division by p */
		if (j==0) array[0] = 1;
		for (i=p-j; i<99; i+=p)
			array[i] = 1;
	}
	for (i=0; i<99; ++i) {
		if (array[i]) continue;
		zsadd(a,i,&ztemp1);
		if (zprobprime(ztemp1,1)) {
			if (zjacobi(N,ztemp1)==1) break;
		}
	}
	if (i==99) {			/* nothing found */
		zsadd(a,99,&a);
		goto loop;		/* try again */
	}
	/* now we have a prime for which N is a q.r. mod */
	/* get b: the sqrt of N mod a^2 */
	zcopy(ztemp1,&a);
	zsq(a,&a2);			 /* a2 = a * a */
	zinv(a,N,&ainv); /* a^-1 mod N */
	zsqrtp2(N, a, a2, &b);

	/* make sure b is between 0 and a^2/2 */
	zsub(a2, b, &ztemp1);
	if (zcompare(ztemp1,b) < 0)
		zcopy(ztemp1,&b);

	/* record this a */
	fp = fopen("a_val","w");
	zfwrite(fp,a,80,"","");
	fprintf(fp,"\n");
	fclose(fp);

	zfwrite(fadata,a,80,"","");
	fprintf(fadata,"\n");
}

/* Find res so that   res * res == x mod p^2, where
	 p is prime.  The input asks for p2 which should be p^2 */
void zsqrtp2(x,p,p2,res)
verylong x,p, p2, *res;
{
	static verylong rr=0, xmodp=0,xmodp2=0;

	zmod(x,p,&xmodp);
	zmod(x,p2,&xmodp2);

	zsqrtmod(xmodp,p,&rr);		/* rr^2 == x mod p */

	zsq(rr,&ztemp1);
	zsub(ztemp1,xmodp2, &ztemp1);	/* ztemp1 is rr^2 - x mod p^2 */
	zsmul(rr,2,&ztemp3);
	zinv(ztemp3,p,&ztemp2);		/* ztemp2 is (2*ztemp1)^-1 mod p */
	zmul(ztemp1,ztemp2,&ztemp3);
	zsub(rr,ztemp3,&ztemp1);
	zmod(ztemp1,p2,res);
}

compute_roots(void)
{
	int i, bmodp, amodp;
	for (i=0 ; i<p_count; ++i) {
		register int p;
		register long long x,inv;
		
    if (i<START && mprimes[i]==1)
			continue;
		p = primes[i];
		amodp = zsdiv(a,p,&ztemp1);
		bmodp = zsdiv(b,p,&ztemp1);

		x = rootN[i]-bmodp;
		if (x < 0) x += p;
		inv = inverse(amodp, p);
		soln1[i] = (((x*inv) % p)*inv) % p;

		x = p-rootN[i]-bmodp;
		if (x < 0) x += p;
		soln2[i] = (((x*inv) % p)*inv) % p;

		if (soln2[i] < soln1[i]) {	/* swap 'em */
			p = soln1[i];
			soln1[i] = soln2[i];
			soln2[i] = p;
		}
		ptr1[i] = soln1[i];
		ptr2[i] = soln2[i];
	}
}

int inverse(int s, int t)
{
	register int u1,u2,v1,v2,q;
	int tmp;
 
	u1=1; u2=s;
	v1=0; v2=t;

	while (v2!=0) {
		q=u2/v2;
 
		tmp=u1-q*v1;
		u1=v1;
		v1=tmp;
 
		tmp=u2-q*v2;
		u2=v2;
		v2=tmp;
  }
	if (u1 < 0)
		u1=u1-t*(-u1/t-1);
	return u1;
}

void sieve(void)
{
	int k, sdc,index;
	static int sd[100];	/* small divisors */

	/* first sieve to the right */
	for (k=0; k<NUM_BLOCKS; ++k) {
		register int i,p;
		register char logp;

		memset (accum, INIT, BLOCK_LENGTH+1000);
		i = p_count-1;
		p = primes[i];
		logp = log_p[i];

		for ( ;i>=START; ) {
			register int i1,i2;

			i1 = ptr1[i];
			i2 = ptr2[i];
			while (i2 < BLOCK_LENGTH) {
				accum[i1] += logp;
				accum[i2] += logp;
				i1 += p;
				i2 += p;
			}
			if (i1 < BLOCK_LENGTH) {
				accum[i1] += logp;
				i1 += p;
			}

			/* adjust ptrs */
			ptr1[i] = i1-BLOCK_LENGTH;
			ptr2[i] = i2-BLOCK_LENGTH;
			if (ptr2[i] < ptr1[i]) {
				p = ptr2[i];
				ptr2[i] = ptr1[i];
				ptr1[i] = p;
			}

			/* advance to next prime */
			i--;
			p = primes[i];
			logp = log_p[i];
		}

		/* now scan the array for hits */
		{
		register long *fscan=(long *)accum;
		register long *lim=(fscan+(BLOCK_LENGTH>>2));

		for (; fscan<=lim; ++fscan) 	/* scan array 4 cells
							at a time */
		    if ((*fscan) & COMP) {		/* find hit */
			register unsigned char *scan =(unsigned char *)
			   fscan;
			register int j;

			for (j=0; j<4; ++j)
			    if (scan[j] & comp) {
				int test;

				sdc=0;
				index= (int) (scan-accum);
				index= index+j+k*BLOCK_LENGTH;
				for (i=0; i<START; ++i)
				    if (mprimes[i]==0) {
					p = primes[i];
					test = index % p;
					if (test== soln1[i] || test==
					 soln2[i]) {
					    sd[sdc++]= i; /* save index */
					    scan[j] +=log_p[i];
					}
				    }
				if (scan[j] >= thresh2) {	/* try it */
				    sd[sdc]=0;
				    trial_divide(index,sd,sdc);
				}
			   }
		    }
		}
	}

	/* now sieve to the left */
	for (k=p_count-1; k>=0; --k) {
		/* we switch the order of the ptrs here so
		that ptr1 is less than ptr2 */
		ptr2[k] = primes[k]-soln1[k];
		ptr1[k] = primes[k]-soln2[k];
	}
	for (k=0; k<NUM_BLOCKS; ++k) {
		register int i, p;
		register char logp;

		memset (accum, INIT, BLOCK_LENGTH+1000);
		i = p_count-1;
		p = primes[i];
		logp = log_p[i];

		for ( ;i>=START; ) {
			register int i1,i2;

			i1 = ptr1[i];
			i2 = ptr2[i];

			while (i2 < BLOCK_LENGTH) {
				accum[i1] += logp;
				accum[i2] += logp;
				i1 += p;
				i2 += p;
			}
			if (i1 < BLOCK_LENGTH) {
				accum[i1] += logp;
				i1 += p;
			}

			/* adjust ptrs */
			ptr1[i] = i1-BLOCK_LENGTH;
			ptr2[i] = i2-BLOCK_LENGTH;
			if (ptr2[i] < ptr1[i]) {
				p = ptr2[i];
				ptr2[i] = ptr1[i];
				ptr1[i] = p;
			}

			/* advance to next prime */
			i--;
			p = primes[i];
			logp = log_p[i];
		}

		/* now scan the array for hits */
		{
		register long *fscan=(long *)accum;
		register long *lim=(fscan+(BLOCK_LENGTH>>2));

		for ( ;fscan<=lim; ++fscan) 	/* scan array 4 cells
							at a time */
		    if ((*fscan) & COMP) {		/* find hit */
			register unsigned char *scan =(unsigned char *)
			   fscan;
			register int j;

			for (j=0; j<4; ++j)
			    if (scan[j] & comp) {
				int test;

				sdc=0;
				index= (int) (scan-accum);
				index= index+j+k*BLOCK_LENGTH;
				index= -index;

				for (i=0; i<START; ++i)
				    if (mprimes[i]==0) {
					p = primes[i];
					test = index % p;
					if (test < 0) test += p;
					if (test== soln1[i] || test==
					 soln2[i]) {
					    sd[sdc++]= i; /* save index */
					    scan[j] +=log_p[i];
					}
				    }
				if (scan[j] >= thresh2) {	/* try it */
				    sd[sdc]=0;
				    trial_divide(index,sd,sdc);
				}
			   }
		    }
		}
	}
}

void trial_divide(int index, int sd[100], int sdc)
{
	int e,sign=1,j,allc=0,mi,tsdc=sdc;
	register int i,p;
	static int all[100], exp[100];
	static verylong residue = 0, u=0;
	/* sd holds the index of the small prime divisors of the
	residue (excluding any primes that divide the multiplier).
	Now find the large primes that divide the residue. */
	for (i=START; i<p_count; ++i) {
		register int test;
		p = primes[i];
		test = index % p;
		if (test < 0) test += p;
		if (test == soln1[i] || test == soln2[i])
			sd[tsdc++]=i;
	}
	/* compute the residue */
	zsmul(a2,index,&ztemp1);
	zadd(ztemp1,b,&ztemp2);
	zmulmod(ztemp2,ainv,N,&u);
	zsqmod(u,N,&residue);		/* probably can do this faster */
	if (zcompare(residue,Nby2)>0) {
		zsub(N,residue,&residue);
		sign = -1;
	}
	/* now trial divide and also check the primes which divide
	the multiplier.  Put all prime divisors into the all array.
	Also find their multiplicities and put that in exp. */
	for (i=0,mi=0; i<tsdc; ) {
		/* if there are still multiplier primes to check
		and the next is smaller than the next prime in the
		sd array... */
		if ((mi<mpc) && (mp[mi]<sd[i])) {
			p = primes[mp[mi]];
			j= zsdiv(residue,p,&ztemp1);
			if (j==0) {
				e = 1;
				zcopy(ztemp1,&residue);
				while (zsdiv(residue,p,&ztemp1)==0) {
					e++;
					zcopy(ztemp1,&residue);
				}
				all[allc] = mp[mi]+1;
				exp[allc++] = e;
			}
			mi++;
		} else {
			p = primes[sd[i]];
			j= zsdiv(residue,p,&ztemp1);
			if (j != 0) {
				printf("ERROR:\n");
				printf("u="); zwriteln(u);
				printf("index=%d\n",index);
				printf("a="); zwriteln(a);
				printf("b="); zwriteln(b);
				printf("sieving says prime %d ",p);
				printf("should divide this residue\n");
				printf("remaining residue = ");
				zwriteln(residue);
				printf("divisors so far:\n");
				for (j=0; j<allc; j++)
					printf("%d ",primes[all[j]]);
				printf("\n");
				exit(1);
			}
			e = 1;
			zcopy(ztemp1,&residue);
			while (zsdiv(residue,p,&ztemp1)==0) {
				e++;
				zcopy(ztemp1,&residue);
			}
			all[allc] = sd[i]+1;
			exp[allc++] = e;
			i++;
		}
	}
	/* if the remaining residue is small enough, then keep it! */
	if (residue[1]==1 && residue[0]<2) {
		/* smooth */
		smc++;

		zfwrite(fsmooth,u,120,"","");
		fprintf(fsmooth," ");
		if (sign == -1)
			fprintf(fsmooth,"-1 1 ");
		for (j=0; j<allc; j++)
			fprintf(fsmooth,"%d %d ",all[j],exp[j]);
		fprintf(fsmooth,"0\n");/*
printf("index %d: smooth\n",index);
*/} else if (zcompare(residue,semi_thresh)== -1) {
		/* semi-smooth */
		ssc++;

		zfwrite(fsemi,residue,120,"","");
		fprintf(fsemi," ");
		zfwrite(fsemi,u,120,"","");
		fprintf(fsemi," ");
		if (sign == -1)
			fprintf(fsemi,"-1 1 ");
		for (j=0; j<allc; j++)
			fprintf(fsemi,"%d %d ",all[j],exp[j]);
		fprintf(fsemi,"0\n");/*
printf("index %d: semi-smooth\n",index);
*/} else {/* possibly partial-partial relation */
/*
printf("index %d: rejected (residue = ",index);
zwrite(residue);
printf(")\n");
*/}
}

