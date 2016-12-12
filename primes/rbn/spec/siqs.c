
/*
 
        This is a an implementation of the self initializing
        quadratic sieve (siqs), written by Scott Contini.  It uses
        large integer arithmetic routines from Arjen Lenstra's
        LIP code (files lip.c, lip.h, lip.o).
 
        The sieving code here has not been highly optimized.
        The purpose of this code is for comparison with my
        multiple polynomial quadratic sieve (mpqs) implementation.
        Any significant improvement in the sieving for mpqs can
        also be applied to siqs.
 
        It is assumed that the user of this program is familiar
        with my Master's thesis from the University of Georgia.
 
        To run this program (on Unix):
                you must have lip.o and lip.h in your directory
 
                select values for parameters (explained below)
                and put them in the code
 
                compile by doing something like:
                gcc -O2 lip.o siqs.c -lm
                where siqs.c is the name of this program
 
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

	Copyright 1996

*/

#include <stdio.h>
#include <math.h>
#include "lip.h"



#define BLOCK_LENGTH		100000	/* amount of sieve array to
					sieve upon at a time */
#define NUM_BLOCKS		1	/* M = BLOCK_LENGTH * NUM_BLOCKS */
#define B			60000	/* largest prime of factor base */
#define START                   20     /* where to start sieving */
#define THRESH1                 50
#define ERROR2                  4


#define	NUM_A_PRIMES		200	/* num primes we can use to compute a */
#define	OFFSET			180	/* index of smallest prime that can
					be used to compute a */


	/* note: we are assuming that any prime that divides the
	multiplier must have index less than START.  In other words,
	the primes that you sieve with are all larger than anything
	that divides the multiplier. */


#define MULT_FILE               "multiplier"
#define MAX_FACTORS_A		15


char SMOOTH_FILE[1000],SEMI_FILE[1000],PP_FILE[1000],GOOD_PRIME_FILE[1000];

#if (THRESH1 > 64)
#define COMP                    0x80808080
#else
#define COMP                    0xc0c0c0c0
#endif
#define MAX_FB                  100000   /* Max primes in Factor Base */


FILE	*factors_fp;
int	comp;
int     rootN[MAX_FB];                  /* sqrt(N) mod primes[i] */
int	soln1[MAX_FB],soln2[MAX_FB];	/* for sieving */
int	ptr1[MAX_FB],ptr2[MAX_FB];	/* for sieving */
int     primes[MAX_FB],                 /* primes in factor base */
	p_count;
int	mp[10];				/* multiplier primes */
int	mpc=0;
int	*factors_a;
unsigned char   accum[BLOCK_LENGTH+1000];
unsigned char   log_p[MAX_FB];          /* logs of the primes in factor base */
verylong        N=0,			/* number to factor */
	a=0,b=0,Nby2=0,ainv=0;
unsigned char   thresh2;
int     ssc,                            /* number of semi-smooth residues */
        smc,                            /* number of smooth residues */
        ppc;                            /* number of pps */
int     STOP;                           /* When to stop sieving */
int     MACHINE_NO;                     /* For parallel factoring */
verylong semi_thresh=0, pp_thresh=0;
verylong ztemp1=0, ztemp2=0, ztemp3=0;
int	FSM,FSS,FPP,F;			/* # smooths, semis, pps */
int	multiplier;
verylong B2=0;
int	ssc=0, smc=0, ppc=0;
int	INIT;
int	M;				/* length of sieve inetrval */
int	markers[3];			/* for parallelism */
int	n;				/* number of divisors of a */
verylong actual=0,maxa=0,mina=0,
	minaby2=0;			/* for computing values of a */
int	*step = NULL;
verylong twoB[MAX_FACTORS_A];
char	*gray,*nu;
char	valid[NUM_A_PRIMES+OFFSET];

/* valid[i] will hold one of the 3 values:
 
        -1      indicates primes[i] cannot be used for
                computing a.
        0       indicates primes[i] is currently not being
                used for a, but it can be used.
        1       indicates primes[i] is a divisor of a.
        2       indicates primes[i] is a divisor of the multiplier.
*/




FILE *fsmooth,*fsemi,*fadata,*fpp;


main () {

	FILE *fp, *status_fp;
	char cc;
	int i;
	double dthresh;
	int loopc=0;

	printf("Welcome to Self Initializing Quadratic Sieve\n"); fflush(stdout);
	printf("using THRESH1=%d ERROR2=%d\n",THRESH1,ERROR2);

	factors_a = (int *) malloc(MAX_FACTORS_A*sizeof(int));

	for (i=0; i < MAX_FACTORS_A; i++)
		twoB[i] = 0;

	/* read in data from params file */

	fp=fopen("params","r");
	if (fp== NULL) {
		printf("Need params file!\n");
		exit(1);
	}
	zfread(fp,&N);
	printf("trying to factor:\n  ");
	zwriteln(N); fflush(stdout);
	M = BLOCK_LENGTH * NUM_BLOCKS;
	printf("using M=%d (%d blocks of length %d)\n",M,NUM_BLOCKS,
	 BLOCK_LENGTH);
	fscanf(fp,"%d",&MACHINE_NO);
	printf("Machine number: %d\n", MACHINE_NO);
	while ((cc=fgetc(fp)) != '\n') ;
	fscanf(fp,"%d",&STOP);
	printf("stop sieving after %d smooths\n",STOP);
	while ((cc=fgetc(fp)) != '\n') ;
	for (i=0; (cc=fgetc(fp)) != '\n'; i++)
		GOOD_PRIME_FILE[i]=cc;
	GOOD_PRIME_FILE[i]='\0';
	printf("factor base primes will be put in file '%s'\n",
	   GOOD_PRIME_FILE);
	for (i=0; (cc=fgetc(fp)) != '\n'; i++)
		SMOOTH_FILE[i]=cc;
	SMOOTH_FILE[i]='\0';
	printf("smooths will be put in file '%s'\n",SMOOTH_FILE);
	for (i=0; (cc=fgetc(fp)) != '\n'; i++)
		SEMI_FILE[i]=cc;
	SEMI_FILE[i]='\0';
	printf("partials will be put in file '%s'\n",SEMI_FILE);
	for (i=0; (cc=fgetc(fp)) != '\n'; i++)
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
	if (fp == NULL) {
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

	dthresh= .5*NumBits(N)*log(2.0) + log((double)M) -
	 NumBits(semi_thresh)*log(2.0) - ERROR2;
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

	/* initialize the valid array */

	/* do not allow small primes to divide a */
	for (i=0; i< OFFSET; i++)
		valid[i] = -1;

	for (; i< OFFSET+NUM_A_PRIMES; i++)
		valid[i] = 0;

	/* If the MACHINE_NO is nonzero (in "params" file), then
	each machine will choose 3 primes from the 15 that are
	available (starting at OFFSET).  Any two computers with
	different MACHINE_NO values will have a different set of
	3 primes.  These primes will be used to construct a.  This
	prevents two computers from sieving upon the same polynomials.
	The three primes will be stored in the markers array. */

	if (MACHINE_NO) {
		for (i=0; i<15; i++)
			valid[i+OFFSET] = -1;
		gettrio(markers,MACHINE_NO);
	}

	fp = fopen("dead.primes","r");
	if (fp != NULL)
		while (fscanf(fp,"%d", &i)>0)
			valid[i]= -1;
	fclose(fp);


	/* a must be size sqrt(2*N)/M.  Compute this, and store it in
	actual.  Then compute the maximum/minimum value of a which can be
	used, and store these in maxa/mina.  Also compute half of the
	minimum value for a.  */

	zsmul(N,2,&ztemp1);
	zsqrt(ztemp1,&ztemp2,&ztemp3);	/* ztemp2 = sqrt(2*N) */
	zsdiv(ztemp2,M,&actual);	/* ztemp1 = sqrt(2*N)/M */
	printf("actual = "); zwriteln(actual);
	zsmul(actual,8,&ztemp2);
	zsdiv(ztemp2,7,&maxa);
	printf("maxa = "); zwriteln(maxa);
	zsmul(actual,7,&ztemp2);
	zsdiv(ztemp2,8,&mina);
	printf("mina = "); zwriteln(mina);
	zsdiv(mina,2,&minaby2);

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
				}
				else {
					rootN[0]=0;
					valid[0]=2;
					mp[mpc++]=0;
				}
				p_count++;
				continue;
			}
			/* if prime divides the multiplier then we
			must treat it a different way */
			j = multiplier % i;
			if (j==0 && (p_count >= START || p_count>=OFFSET)) {
				printf("Error: multiplier too large.\n");
				exit(1);
			}
			if (j==0) {
				valid[p_count]=2;
				mp[mpc++]=p_count;
			}
			else {
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
	}
	else {
		printf("creating factor base primes file!\n"); fflush(stdout);
		fclose(fp);
		fp=fopen(GOOD_PRIME_FILE, "w");
		primes[0] = 2;
		fprintf(fp,"2\n");
		log_p[0]=(unsigned char) (log((double) 2.0) +.5);
		if (multiplier %2 ==1) {
			rootN[0]=1;
		}
		else {
			rootN[0]=0;
			valid[0]=2;
			mp[mpc++]=0;
		}
		p_count=1;
		zpstart();
		while ((i = zpnext()) < B ) {
			register int j,js;
			if (i==2) {
				printf("need larger PRIM_BND for this factor
				   base\n");
				exit(1);
			}
			j = zsmod(N,i);
			if (j==0) {
				if (multiplier % i != 0) {
					printf("N is divisible by %d\n",i);
					exit(1);
				}
				if (p_count >= START || p_count>=OFFSET) {
					printf("Error: multiplier too large.\n");
					exit(1);
				}
			}
			else if ( (js=zjacobis(j,i))== -1)
				continue;
			primes[p_count] = i;
			fprintf(fp,"%d\n",i);
			if (p_count < START) {
				if (j==0) {
					mp[mpc++]=p_count;
					valid[p_count] = 2;
				}
				else {
					rootN[p_count]=sqrtmod(j,i);
				}
			}
			log_p[p_count]=(unsigned char) (log((double) i) +.5);
			p_count++;
		}
		fclose(fp);
	}

	primes[p_count]=0;

	/* read in previous factors of a, if they exist. */

	n=0;
	zzero(&a);
	factors_fp=fopen("factors_a","r");
	if (factors_fp != NULL) {
		int pi;

		zone(&a);
		while ((fscanf(factors_fp,"%d",&pi))>0) {
			/* assume the file has not been corrupted:
			If there is a nonzero MACHINE_NO, then the
			first three primes should be the same as
			those in the markers array. */

			factors_a[n++]=pi;
			zsmul(a,primes[pi],&a);
			valid[pi]=1;
		}
	}

	/* get data from status file */

	status_fp=fopen("status","r");
	if (status_fp != NULL) {
		fscanf(status_fp,"%d",&F);              /* # good primes */
		fscanf(status_fp,"%d",&FPP);            /* # pps */
		fscanf(status_fp,"%d",&FSS);            /* # semi */
		fscanf(status_fp,"%d",&FSM);            /* # smooth */
		fclose(status_fp);
        }
	else {
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

		if ((loopc&3)==0) {
			printf("\nstatus: %d %d %d %d\n\n",F,FPP,FSS,FSM);
			system("ps -aux| head |grep a.out");
			fflush(stdout);
		}
		loopc++;

		get_a();

		get_b_data();		/* value of b's for this a */

		compute_solns();

		/* sieve on the first polynomial */

		sieve();

		/* sieve on the remaining polynomials */

		for (i=1; i < (1<<(n-1)); i++) {
			register int j,p;
			register int *stepptr;

			j = nu[i];
			stepptr = &(step[j*p_count - 1]);

			if (gray[i] == -1) {
				zsub(b,twoB[j],&b);
				for (j=p_count-1; j>= 0; j--,stepptr--) {
					register int s1,s2;

					if (j <OFFSET+NUM_A_PRIMES &&
					   valid[j] > 0)
						continue;
					p = primes[j];
					s1 = soln1[j] - (*stepptr);
					s2 = soln2[j] - (*stepptr);
					if (s1 < 0)
						s1 += p;
					if (s2 < 0)
						s2 += p;
					if (s1 < s2) {
						soln1[j] = s1;
						ptr1[j] = s1;
						soln2[j] = s2;
						ptr2[j] = s2;
					}
					else {
						soln1[j] = s2;
						ptr1[j] = s2;
						soln2[j] = s1;
						ptr2[j] = s1;
					}
				}
			}
			else {
				zadd(b,twoB[j],&b);
				for (j=p_count-1; j>= 0; j--,stepptr--) {
					register int s1,s2;

					if (j <OFFSET+NUM_A_PRIMES &&
					   valid[j] > 0)
						continue;
					p = primes[j];
					s1 = soln1[j] + (*stepptr);
					s2 = soln2[j] + (*stepptr);
					if (s1 >= p)
						s1 -= p;
					if (s2 >= p)
						s2 -= p;
					if (s1 < s2) {
						soln1[j] = s1;
						ptr1[j] = s1;
						soln2[j] = s2;
						ptr2[j] = s2;
					}
					else {
						soln1[j] = s2;
						ptr1[j] = s2;
						soln2[j] = s1;
						ptr2[j] = s1;
					}
				}
			}

			sieve();
		}

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
 
   Always return the smallest squareroot
*/


int
sqrtmod(a, p)
int a,p;
 
{
 
	register long long r,s,c;
	long long m,n,k,kprime,i,j;
 
	/* if number is small then search for soultion */
 
	if (p < 50 || (p <200 && p&2==0))
		for (i=1; i<p; i++)
			if (i*i % p == a) return i;
 
	if (p&2==1) {   /* p == 3 mod 4 */
		s=expmod((long long) a,(long long) ((p+1)>>2),(long long) p);
		if (s > (p>>1)) return p-s;
		else return s;
	}
 
	kprime= -1; k=0;
	m=p-1;
	while ((m&1)==0) k++, m>>=1;
 
	/* perform two fast exponentiations at the same time below */
 
	s=(m+1)>>1; c=a; r=1; n=1;
	for (i=0; (j=(1<<i)) <= m; i++) {
		if (m&j) n=(n*c) % p;
		if (s&j) r=(r*c) % p;
		c=(c*c)%p;
        }
 
	while(1) {
		if (n==1)
			if (r > (p>>1)) return p-r;
			else return r;
		if (kprime < 0) {
			for (i=0; ;i++) {
				c=primes[i];
				if (jacobi((int) c,p)==-1) break;
			}
			c=expmod(c,m,(long long) p);
		}
		s=n;
		for (kprime=1; ; kprime++) {
			s=(s*s)%p;
			if (s==1) break;
		}
		s=c;
		for (i=0; i<k-kprime-1; i++)
			s=(s*s) % p;
		r=(s*r) % p; c=(s*s) % p; n=(c*n) % p; k=kprime;
	}
 
 
}




/* Function: expmod
 
   Description: calculates and returns a^2 mod n.  Use the simple,
        recursive algorithm.
*/
 
int
expmod (a,e, n)
long long a,e,n;
{
 
	long long temp;
 
	if (e==1) return a % n;
	if (e&1) return (a*expmod(a,e-1,n)) % n;
	temp= expmod(a,e>>1,n);
	return (temp*temp) % n;
 
}




/* Function: jacobi
 
   Description: calculates and returns the jacobi symbol.
 
   Note: The jacobi symbol is the same as the Legendre symbol mod a prime
*/
 
int jacobi(m, n)
int m,n;
{
 
	int t;
 
	if (m>n) m=m%n;
	if (m==0) return 0;
	if (m==1) return 1;
	if (m==2) {
		if (n&1==0) return 0;
		t=n&7;                                  /* t = n % 8 */
		if (t==1 || t==7) return 1;
		return -1;
	}
	if ((m&1)==0)
		return jacobi((m>>1),n)*jacobi(2,n);
	if ((m&3)==3 && (n&3)==3) return -jacobi(n,m);
	return jacobi(n,m);
	 
}




NumBits(a)
verylong a;
 
{
 
	int i,b,c;
 
	b=a[a[0]];
	c=0;
	while (b>0)
		b>>=1, c++;
 
	return NBITS*(a[0]-1)+c;
 
}



get_b_data() {

	int l;

	if (step == NULL) {
		step = (int *) malloc((n-1)*p_count*sizeof(int));
		if (step == NULL) {
			printf("Error: could not allocate enough memory\n");
			printf("for step.\n");
			exit(1);
		}
		get_gray_code();
	}

	zzero(&b);

	for (l=0; l<n; l++) {
		int q,rem,t,tmp, tmp2;
		long long r1;

		q = primes[factors_a[l]];
		t = rootN[factors_a[l]];	/* t^2 == N mod q */

		zsdiv(a,q,&ztemp1);	/* ztemp1 = a/q */
		rem = zsdiv(ztemp1,q,&ztemp2);
		tmp = inverse(rem,q);	/* tmp = (a/q)^-1 mod q */

		/* need to use the least non-negative integer in
		residue class. */

		r1 = (long long) tmp * (long long) t;
		tmp2 = r1 % q;		/* tmp2 = t*(a/q)^-1 mod q */
		if (tmp2 > (q>>1)) {
			t = (q-t);
			tmp2 = q-tmp2;
		}
		/* tmp2 represents t(a,q) in siqs paper */

		zsmul(ztemp1,tmp2,&ztemp2);
		zadd(b,ztemp2,&b);
		zsmul(ztemp2,2,&twoB[l]);
	}
	zmod(b,a,&b);

}





compute_solns() {

	int i;
	int bmodp, amodp;

	for (i =0 ; i<p_count; i++) {
		register int p;
		register long long x,inv;

		if (i < OFFSET+NUM_A_PRIMES && valid[i]>0)
			continue;

		p = primes[i];
		amodp = zsdiv(a,p,&ztemp1);
		bmodp = zsdiv(b,p,&ztemp1);

		x = rootN[i] + bmodp;
		inv = inverse(amodp, p);
		soln1[i] = (x * inv) % p;

		x = p - rootN[i] + bmodp;
		soln2[i] = (x * inv) % p;

		if (soln2[i] < soln1[i]) {	/* swap 'em */
			register int tmp;

			tmp = soln1[i];
			soln1[i] = soln2[i];
			soln2[i] = tmp;
		}
		ptr1[i] = soln1[i];
		ptr2[i] = soln2[i];

		{
			register int j;

			for (j=1; j < n; j++) {
				x = zsdiv(twoB[j],p,&ztemp1);
				x = (x * inv) % p;
				step[(j-1)*p_count+i] = (int) x;
			}

		}

	}

}




int
inverse(s, t)
int s,t;
{
 
	register int u1,u2,v1,v2,q;
	int temp;
 
	u1=1; u2=s;
	v1=0; v2=t;

	while (v2!=0) {
		q=u2/v2;
 
		temp=u1-q*v1;
		u1=v1;
		v1=temp;
 
		temp=u2-q*v2;
		u2=v2;
		v2=temp;
        }
 
	if (u1 < 0)
		u1=u1-t*(-u1/t-1);
 
	return u1;
	 
}

 

sieve() {

	int k;
	int sdc,index;
	static int sd[100];		/* small divisors */

	/* first sieve to the right */

	for (k=0; k < NUM_BLOCKS; k++) {
		register int i;
		register int p;
		register char logp;

		memset (accum, INIT, BLOCK_LENGTH+1000);

		/* first do the small primes that we must be cautious
		about */

		for (i=START; i < OFFSET + NUM_A_PRIMES; i++) {
			register int i1,i2;

			if (valid[i]>0)
				continue;
			p = primes[i];
			logp = log_p[i];
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

			ptr1[i] = i1 - BLOCK_LENGTH;
			ptr2[i] = i2 - BLOCK_LENGTH;
			if (ptr2[i] < ptr1[i]) {
				p = ptr2[i];
				ptr2[i] = ptr1[i];
				ptr1[i] = p;
			}

		}


		i = p_count-1;

		for (;  i >= OFFSET + NUM_A_PRIMES ;  ) {
			register int i1,i2;

			p = primes[i];
			logp = log_p[i];
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

			ptr1[i] = i1 - BLOCK_LENGTH;
			ptr2[i] = i2 - BLOCK_LENGTH;
			if (ptr2[i] < ptr1[i]) {
				p = ptr2[i];
				ptr2[i] = ptr1[i];
				ptr1[i] = p;
			}

			/* advance to next prime */
			i--;
		}

		/* now scan the array for hits */

		{
		register long *fscan=( long *) accum;
		register long  *lim= (fscan+(BLOCK_LENGTH>>2));

		for (; fscan <=  lim; fscan++ ) 	/* scan array 4 cells
							at a time */
		    if ((*fscan) & COMP) {		/* find hit */
			register unsigned char *scan =(unsigned char *)
			   fscan;
			register int j;

			for (j=0; j<4; j++)
			    if (scan[j] & comp) {
				int test;

				sdc=0;
				index= (int) (scan-accum);
				index= index + j + k*BLOCK_LENGTH;

				for (i=0; i < START; i++)
				    if (i>=OFFSET+NUM_A_PRIMES || valid[i]<=0) {
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


	for (k=p_count-1; k>=0; k--) {
		register int p;

		/* we switch the order of the ptrs here so
		that ptr1 is less than ptr2 */
		p = primes[k];
		ptr2[k] = p - soln1[k];
		ptr1[k] = p - soln2[k];
	}


	for (k=0; k < NUM_BLOCKS; k++) {
		register int i;
		register int p;
		register char logp;

		memset (accum, INIT, BLOCK_LENGTH+1000);

		/* first do the small primes that we must be cautious
		about */

		for (i=START; i < OFFSET + NUM_A_PRIMES; i++) {
			register int i1,i2;

			if (valid[i]>0)
				continue;
			p = primes[i];
			logp = log_p[i];
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

			ptr1[i] = i1 - BLOCK_LENGTH;
			ptr2[i] = i2 - BLOCK_LENGTH;
			if (ptr2[i] < ptr1[i]) {
				p = ptr2[i];
				ptr2[i] = ptr1[i];
				ptr1[i] = p;
			}

		}

		i = p_count-1;

		for (;  i >= OFFSET+NUM_A_PRIMES;  ) {
			register int i1,i2;

			p = primes[i];
			logp = log_p[i];
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

			ptr1[i] = i1 - BLOCK_LENGTH;
			ptr2[i] = i2 - BLOCK_LENGTH;
			if (ptr2[i] < ptr1[i]) {
				p = ptr2[i];
				ptr2[i] = ptr1[i];
				ptr1[i] = p;
			}

			/* advance to next prime */
			i--;
		}

		/* now scan the array for hits */

		{
		register long *fscan=( long *) accum;
		register long  *lim= (fscan+(BLOCK_LENGTH>>2));

		for (; fscan <=  lim; fscan++ ) 	/* scan array 4 cells
							at a time */
		    if ((*fscan) & COMP) {		/* find hit */
			register unsigned char *scan =(unsigned char *)
			   fscan;
			register int j;

			for (j=0; j<4; j++)
			    if (scan[j] & comp) {
				int test;

				sdc=0;
				index= (int) (scan-accum);
				index= index + j + k*BLOCK_LENGTH;
				index= -index;

				for (i=0; i < START; i++)
				    if (i>=OFFSET+NUM_A_PRIMES || valid[i]<=0) {
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




trial_divide(index, sd, sdc)
int index, sd[100], sdc;

{

	register int i,p;
	int e;
	static verylong residue = 0, u=0;
	int sign=1,j;
	static int all[100];
	int allc=0,mi,fi;
	static int exp[100];

	/* sd holds the index of the small prime divisors of the
	residue (excluding any primes that divide the multiplier).
	Now find the large primes that divide the residue. */
	
	for (i= START; i<p_count; i++) {
		register int test;

		if ((i<NUM_A_PRIMES + OFFSET) && (valid[i] >0))
			continue;
		p = primes[i];
		test = index % p;
		if (test < 0) test += p;
		if (test == soln1[i] || test == soln2[i])
			sd[sdc++]=i;
	}

	/* compute the residue */

	zsmul(a,index,&ztemp1);
	zsub(ztemp1,b,&u);
	if (zsign(u) < 0)
		znegate(&u);
	zsq(u,&ztemp1);
	zsub(ztemp1,N,&residue);
	if (zsign(residue) < 0) {
		znegate(&residue);
		sign = -1;
	}

	/* now trial divide and also check the primes which divide
	the multiplier.  Put all prime divisors into the all array.
	Also find their multiplicities and put that in exp. */

	for (i=0,mi=0,fi=0; i<sdc; ) {

		/* if there are still multiplier primes to check
		and the next is smaller than the next prime in the
		sd array, and also smaller than the next prime in
		the factors_a array, then... */
		if ((mi< mpc) && (mp[mi] < sd[i]) && (mp[mi] <
		   factors_a[fi])) {
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
		}
		else if ((fi < n) && (factors_a[fi] < sd[i])) {
			p = primes[factors_a[fi]];
			j= zsdiv(residue,p,&ztemp1);
			if (j==0) {
				e = 1;
				zcopy(ztemp1,&residue);
				while (zsdiv(residue,p,&ztemp1)==0) {
					e++;
					zcopy(ztemp1,&residue);
				}
				all[allc] = factors_a[fi]+1;
				exp[allc++] = e;
			}
			else {
				printf("Error:\n");
				printf("residue: "); zwriteln(residue);
				printf("u = "); zwriteln(u);
				printf("a = "); zwriteln(a);
				printf("b = "); zwriteln(b);
				printf("x = %d\n",index);
				printf("not divisible be prime %d\n",p);
				exit(1);
			}

			fi++;
		}
		else {
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
					printf("%d ",primes[all[j]-1]);
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

	if (residue[1]==1 && residue[0] < 2) {
		/* smooth */

		smc++;

		zfwrite(fsmooth,u,120,"","");
		fprintf(fsmooth," ");
		if (sign == -1)
			fprintf(fsmooth,"-1 1 ");
		for (j=0; j<allc; j++)
			fprintf(fsmooth,"%d %d ",all[j],exp[j]);
		fprintf(fsmooth,"0\n");
/*
printf("index %d: smooth\n",index);
*/
	}
	else if (zcompare(residue,semi_thresh)== -1) {
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
		fprintf(fsemi,"0\n");
/*
printf("index %d: semi-smooth\n",index);
*/
	}
	else {
		/* possibly partial-partial relation */
/*
printf("index %d: rejected (residue = ",index);
zwrite(residue);
printf(")\n");
*/
	}

}




/* generate a leading coefficient divisible by as many primes
as possible. */

get_a() {

	FILE *deadfp;
	int i,j,k;
	int start_point;


	start_point=OFFSET;

	if (n>0) {	/* try to get new approx by changing old */
		if (MACHINE_NO) {
			factors_a+=3;		/* hide 3 primes */
			n-=3;
		}

		for (i=n-2; i>0; i-=2) {
			if (factors_a[i] < NUM_A_PRIMES+OFFSET)
				valid[factors_a[i]] = 0;	/* unmark factor */
			if (factors_a[i+1] < NUM_A_PRIMES+OFFSET)
				valid[factors_a[i+1]] = 0;
			k=factors_a[i+1];	/* first prime to be changed */

			for (j=i; j<n; j++) {
				/* find the next available prime */
				for (;valid[k+j-i+1]!=0; k++);
				factors_a[j]=k+j-i+1;
			}

			/* now compute a */

			if (MACHINE_NO) {
				/* first multiply the primes that
				are unique to this MACHINE_NO. */

				zintoz(primes[markers[0]+OFFSET],&a);
				zsmul(a,primes[markers[1]+OFFSET],&a);
				zsmul(a,primes[markers[2]+OFFSET],&a);
			}
			else zone(&a);

			for (j=0; j<n; j++)
				zsmul(a,primes[factors_a[j]],&a);

			if(zcompare(a,maxa)<1 && factors_a[n-1] < NUM_A_PRIMES+OFFSET)
				goto done;

		}
	}

	/* if exited loop with i=0, then need to kill a prime */

	if (n > 0) {
		valid[factors_a[0]]= -1;	/* Kill smallest prime */
		valid[factors_a[1]]= -1;	/* and next smallest */
		deadfp=fopen("dead.primes","a");
		fprintf(deadfp,"%d\n",factors_a[0]);
		fclose(deadfp);
	}

	/* if first call to this procedure, or if previous lines did
	not succeed in finding a good value of a, then find value of a
	by the code below */

doitover:

	for (j=0; j < n; j++)
		if (valid[factors_a[j]] == 1)
			valid[factors_a[j]]=0;

	n = 0;
	i = start_point;

	if (MACHINE_NO) {
		factors_a[0]= OFFSET+markers[0];
		factors_a[1]= OFFSET+markers[1];
		factors_a[2]= OFFSET+markers[2];
		valid[OFFSET+markers[0]]= 1;
		valid[OFFSET+markers[1]]= 1;
		valid[OFFSET+markers[2]]= 1;
		factors_a+=3;		/* hide these primes */
		zintoz(primes[markers[0]+OFFSET],&a);
		zsmul(a,primes[markers[1]+OFFSET],&a);
		zsmul(a,primes[markers[2]+OFFSET],&a);
	}
	else zone(&a);

	while (zcompare(a,minaby2) < 0 || zcompare(a,maxa)>0) {
		register int p,q;

		while ((i<NUM_A_PRIMES+OFFSET) && (valid[i] != 0)) i++;

		if (i >= NUM_A_PRIMES+OFFSET) {
			/* Can't take these primes.  Got to try again. */

			/* Increase start_point so that we
			are forced to use larger primes. */

			start_point++;

			if (start_point >= NUM_A_PRIMES+OFFSET) {
				printf("Need to raise NUM_");
				printf("A_PRIMES\n");
				exit(1);
			}

			valid[factors_a[0]] = -1;
			goto doitover;
		}

		p=primes[i];
		i++;
		zsmul(a,p,&ztemp1);
		if (zcompare(ztemp1,maxa) > 0) {	/* too big */

			/* first try to remove a prime that fits well */
			for (j=n-1; j>=0; j--) {
				q=primes[factors_a[j]];
				zsdiv(ztemp1,q,&ztemp2);
				if ((zcompare(ztemp2,minaby2)>= 0) &&
				   (zcompare(ztemp2,maxa)<=1)) {
					for (k=j; k<n-1; k++)
						factors_a[k]=factors_a[k+1];
					factors_a[n-1] = i-1;
					zcopy(ztemp2,&a);
					break;
				}
			}

			if (j < 0) {
				zsdiv(a,primes[factors_a[n-1]],&a);	/* remove
								largest prime */
				n--;
			}
		}
		else {			/* take the prime */
			zsmul(a,p,&a);
			factors_a[n++]=i-1;
			if (n> MAX_FACTORS_A) {
				printf("Need to increase MAX_");
				printf("FACTORS_A\n");
				exit(1);
			}
		}
	}

done:

	if (zcompare(a,mina) < 0) {
		register int p,q;

		/* need to adjust largest prime */

		p =primes[factors_a[n-1]];
		for (j=factors_a[n-1]+1; ; j++) {

			if (j >= NUM_A_PRIMES+OFFSET) {
				/* There's no room to adjust largest prime.
				Got to try it all over again. */

				start_point = factors_a[0]+1;

				goto doitover;
			}

			if (valid[j]!=0)
				continue;
			/* see how well the next prime fits */
			q=primes[j];
			zsmul(a,q,&ztemp1);
			zsdiv(ztemp1,p,&ztemp2);
			if (zcompare(ztemp2,mina) > 1) {
				/* got it! */
				zcopy(ztemp2,&a);
				factors_a[n-1]=j;
				break;
			}
		} /* for j */
	} /* if */

	if (MACHINE_NO) {	/* unhide primes */
		factors_a-=3;
		n+=3;
	}

	factors_fp=fopen("factors_a","w");
	for (j=0; j<n; j++) {
		fprintf (factors_fp, "%d\n",factors_a[j]);
		valid[factors_a[j]]=1;
		factors_a[j] = factors_a[j];
	}
	fclose(factors_fp);

	zfwrite(fadata,a,70, "","");
	fprintf(fadata,"\n");
	fflush(fadata);

	zinv(a,N,&ainv);

}




/* choose 3 primes for each machine */

gettrio(trial,num)
int trial[3],num;
 
{
 
	int keep[45][3], kc=0;
 
 
	trial[0] = 0; trial[1] =1; trial[2] = 2;
	while (num) {
		if (good(trial,keep,kc)) {
			keep[kc][0] = trial[0];
			keep[kc][1] = trial[1];
			keep[kc][2] = trial[2];
			kc++;
			if (--num==0) return;
		}
		if (++trial[2] == 15) {
			if (++trial[1] == 14) {
				if (++trial[0] == 13) {
					printf("total machines: %d\n",kc);
					exit(1);
				}
				trial[1] = trial[0]+1;
			}
			trial[2] = trial[1]+1;
		}
	}
	return;
 
}



int
good(trial,keep,kc)
int trial[3],keep[45][3],kc;
 
{
 
        int m;
 
        for (m=0; m < kc; m++)
                if (conflict(keep[m],trial)) return 0;
        return 1;
 
}
 
 


int
conflict(old, trial)
int old[], trial[];
 
{
 
	int m,n, count=0;
 
	for (m=0; m < 3; m++)
		for(n=0; n<3; n++)
			if (old[m]==trial[n]) {
				if (++count==2) return 1;
			break;
			}
	return 0;
 
}
 



get_gray_code() {

	register int i, v, j;
	int tmp;

	gray = (char *) malloc( (1 << (n-1)) * sizeof(char));
	nu = (char *) malloc( (1 << (n-1)) * sizeof(char));

	for (i=1; i< (1 << (n-1)); i++) {
		v = 1;
		j = i;
		while ((j&1)==0)
			v++, j>>=1;
		tmp = i + (1<<v) - 1;
		tmp = (tmp>>v);
		nu[i] = v;
		if (tmp&1)
			gray[i] = -1;
		else
			gray[i] = 1;
	}

}
















