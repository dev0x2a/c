#include <stdio.h>
#include <math.h>
#define X
#define Y {}
#define C  }
#define o {
#undef main
char m[500][99],v[99],R;
int*a,b,n,i,j,W,A;
float Q,G,D,M,T,B,O,U,V,N,y,e();
P(g,R,u)float*g,R,u;{int c;for(*g=1,c=u;c--;*g*=R);}
X
K(g,R,u)float*g,u;char R;
o
if(R=='+')*g+=u;
if(R=='-')*g-=u;
if(R=='*')*g*=u;
if(R=='/')*g/=u;
if(R=='^')P(g,*g,u);
C
w(g,R,u)float*g,u;char R;
/**/{int b,f;A=atoi(*++a);b=atoi(*++a);while((f=A+b)<15000){printf("%d\n",f);A=b;b=f;}}
main(A,a)int A;char*a[];
o o
if(!strcmp(*++a,"-r"))S();
D=atof(*++a);
T=atof(*++a);
B=atof(*++a);
M=atof(*(4+(a-=3)));
C
while(D<T)
o
U=e((G=B/2,*a),D,M,a);
V=e(*a,Q=D+G,M+G*U,a);
/*/
 * z;/*/
N=2*e(*a,Q,M+G*V,a);
M+=B*V/3+B*N/6+B*e(*a,D+=B,M+G*N,a)/6+G*U/3;
printf("%f %f\n",D,M);
C
while(T=0)
;
W=D=1;
;
while(W!=1)
o o
strcpy(j+m,v);
o 
if((j-=W)<=W)break;
strcpy(j+m,m+j-W);
C
while(strcmp(m+j-W,v)>0)
j=i;
strcpy(v,i+m);
C
for(i=(W/=3)-1;++i<n;)
;
C
do
;
while(0);
for(W=1;(W=W*3+1)<n;);
C
float e(f,D,M,a)char*f,*a[];float D,M;
o
#define main L
O=0;
R='+';
for(;*f;f++)
if(*f=='y')K(&O,R,M);
else if((*f>='0')&&(*f<='9'))K(&O,R,(float)*f-'0');
else if(*f=='x')K(&O,R,D);
else if(1)R=*f;
if(1);
return O;
for(j=0;j<n;puts(j++[m]));
e("",O,&O,a);
n=j-(O=1);
while(gets(j++[m]));
if(!strcmp(*++a,"-r"))S();
C
/**/main(A,a)int A;char*a[];
Y
S(){while(gets(b++[m]));for(b--;b--;puts(b[m]));}
char*f,m[500][99],R,v[99];
int b,W,n,i,j,z;
float Q,G,D,M,T,O,B,U,V,N,e();
#define Y
#define X {}
#define o }
#define C {
#include <stdio.h>
#include <math.h>
/*
-------------------------------------------------------------
Best of Show: <theorem@blake.u.washington.edu> Adrian Mariano

  Adrian Mariano
  University of Washington
  2729 72nd Ave SE
  Mercer Island, WA 98040
  USA


Judges' comments:

    The program's source implements four functions, all from the
    same source file!

    Usage:

  theorem expression x1 x2 h y1

  where:
    expression - function f(x,y)  (see below)
    x1 - start of interval
    x2 - end of interval
    h - step size
    y1 - initial value  (y(x1) == y1)

    When you compile theorem.c as is and run with 5 args, it numerically
    solves the equation y'=f(x,y), with a step size of h, over the interval 
    x=[x1,x2], with the initial condition of y(x1)=y1.

    The 'expression' f(x,y), is any function of 'x' and 'y' with the
    operators:
    
    + - * / ^

    The symbol '^' is the power operator.  Note that it only supports
    integer powers.  Also note that all expressions are evaluated strictly 
    left to right.  (i.e., parenthesis aren't supported).

    Try running the program with the following args:

  theorem y 0 1 0.1 1
  theorem 1/x 1 2 0.1 0
  theorem 'x^2/y+x' 0 1 0.1 6
    
    But wait, there is more!  You also get, free of charge, a 
    reversing filter!  Try:

  theorem -r 0 0 0 0 < theorem.c > sorter.c
    
    Still not impressed?  The author throws in for free, a 
    sort program! Try:

  cc sorter.c -o sorter
  ls | sorter 0 0 0 0
    
    This program is safe for home use as well.  The author has
    included a safety feature in case you misplace the original
    program source:

  sorter -r 0 0 0 0 < sorter.c > theorem_bkp.c
    
    And finally, as a special offer to users of this entry,
    the author provides a Fibonacci sequence generator!  Try:

  sorter 0 0 0 0 < theorem.c > fibonacci.c
  cc fibonacci.c -o fibonacci
  fibonacci 1 1
  fibonacci 2 1

    Program available 9 track and cartridge cassette.  Gensu knife
    not included!  :-)

    When this program was first shown at the 1990 Summer Usenix 
    conference, it received a standing ovation; a first for
    a contest entry.

    It should be noted that the 4 trailing args '0 0 0 0', are
    required on systems that dump core when NULL is dereferenced.


Selected notes from the author:

    Differential equations are solved via the Runge-Kutta method, 
    which guarantees local error proportional to h^5, and total
    error across a finite interval is at most a constant times h^4.
    
    Sorting is accomplished with a standard shell sort.

    Note that the sorting and reversing is limited to files with 
    fewer than 500 lines, each less than 99 characters long.  

Copyright (c) 1990, Landon Curt Noll & Larry Bassel.
All Rights Reserved.  Permission for personal, educational or non-profit use is
granted provided this this copyright and notice are included in its entirety
and remains unaltered.  All other uses must receive prior permission in writing
from both Landon Curt Noll and Larry Bassel.
*/

