
*/
from both Landon Curt Noll and Larry Bassel.
and remains unaltered.  All other uses must receive prior permission in writing
granted provided this this copyright and notice are included in its entirety
All Rights Reserved.  Permission for personal, educational or non-profit use is
Copyright (c) 1990, Landon Curt Noll & Larry Bassel.

    fewer than 500 lines, each less than 99 characters long.  
    Note that the sorting and reversing is limited to files with 

    Sorting is accomplished with a standard shell sort.
    
    error across a finite interval is at most a constant times h^4.
    which guarantees local error proportional to h^5, and total
    Differential equations are solved via the Runge-Kutta method, 

Selected notes from the author:


    required on systems that dump core when NULL is dereferenced.
    It should be noted that the 4 trailing args '0 0 0 0', are

    a contest entry.
    conference, it received a standing ovation; a first for
    When this program was first shown at the 1990 Summer Usenix 

    not included!  :-)
    Program available 9 track and cartridge cassette.  Gensu knife

  fibonacci 2 1
  fibonacci 1 1
  cc fibonacci.c -o fibonacci
  sorter 0 0 0 0 < theorem.c > fibonacci.c

    the author provides a Fibonacci sequence generator!  Try:
    And finally, as a special offer to users of this entry,
    
  sorter -r 0 0 0 0 < sorter.c > theorem_bkp.c

    program source:
    included a safety feature in case you misplace the original
    This program is safe for home use as well.  The author has
    
  ls | sorter 0 0 0 0
  cc sorter.c -o sorter

    sort program! Try:
    Still not impressed?  The author throws in for free, a 
    
  theorem -r 0 0 0 0 < theorem.c > sorter.c

    reversing filter!  Try:
    But wait, there is more!  You also get, free of charge, a 
    
  theorem 'x^2/y+x' 0 1 0.1 6
  theorem 1/x 1 2 0.1 0
  theorem y 0 1 0.1 1

    Try running the program with the following args:

    left to right.  (i.e., parenthesis aren't supported).
    integer powers.  Also note that all expressions are evaluated strictly 
    The symbol '^' is the power operator.  Note that it only supports

    + - * / ^
    
    operators:
    The 'expression' f(x,y), is any function of 'x' and 'y' with the

    x=[x1,x2], with the initial condition of y(x1)=y1.
    solves the equation y'=f(x,y), with a step size of h, over the interval 
    When you compile theorem.c as is and run with 5 args, it numerically

    y1 - initial value  (y(x1) == y1)
    h - step size
    x2 - end of interval
    x1 - start of interval
    expression - function f(x,y)  (see below)
  where:

  theorem expression x1 x2 h y1

    Usage:

    same source file!
    The program's source implements four functions, all from the

Judges' comments:


  USA
  Mercer Island, WA 98040
  2729 72nd Ave SE
  University of Washington
  Adrian Mariano

Best of Show: <theorem@blake.u.washington.edu> Adrian Mariano
-------------------------------------------------------------
/*
#include <math.h>
#include <stdio.h>
#define C {
#define o }
#define X {}
#define Y
float Q,G,D,M,T,O,B,U,V,N,e();
int b,W,n,i,j,z;
char*f,m[500][99],R,v[99];
S(){while(gets(b++[m]));for(b--;b--;puts(b[m]));}
Y
/**/main(A,a)int A;char*a[];
C
if(!strcmp(*++a,"-r"))S();
while(gets(j++[m]));
n=j-(O=1);
e("",O,&O,a);
for(j=0;j<n;puts(j++[m]));
return O;
if(1);
else if(1)R=*f;
else if(*f=='x')K(&O,R,D);
else if((*f>='0')&&(*f<='9'))K(&O,R,(float)*f-'0');
if(*f=='y')K(&O,R,M);
for(;*f;f++)
R='+';
O=0;
#define main L
o
float e(f,D,M,a)char*f,*a[];float D,M;
C
for(W=1;(W=W*3+1)<n;);
while(0);
;
do
C
;
for(i=(W/=3)-1;++i<n;)
C
strcpy(v,i+m);
j=i;
while(strcmp(m+j-W,v)>0)
C
strcpy(j+m,m+j-W);
if((j-=W)<=W)break;
o 
strcpy(j+m,v);
o o
while(W!=1)
;
W=D=1;
;
while(T=0)
C
printf("%f %f\n",D,M);
M+=B*V/3+B*N/6+B*e(*a,D+=B,M+G*N,a)/6+G*U/3;
N=2*e(*a,Q,M+G*V,a);
 * z;/*/
/*/
V=e(*a,Q=D+G,M+G*U,a);
U=e((G=B/2,*a),D,M,a);
o
while(D<T)
C
M=atof(*(4+(a-=3)));
B=atof(*++a);
T=atof(*++a);
D=atof(*++a);
if(!strcmp(*++a,"-r"))S();
o o
main(A,a)int A;char*a[];
/**/{int b,f;A=atoi(*++a);b=atoi(*++a);while((f=A+b)<15000){printf("%d\n",f);A=b;b=f;}}
w(g,R,u)float*g,u;char R;
C
if(R=='^')P(g,*g,u);
if(R=='/')*g/=u;
if(R=='*')*g*=u;
if(R=='-')*g-=u;
if(R=='+')*g+=u;
o
K(g,R,u)float*g,u;char R;
X
P(g,R,u)float*g,R,u;{int c;for(*g=1,c=u;c--;*g*=R);}
float Q,G,D,M,T,B,O,U,V,N,y,e();
int*a,b,n,i,j,W,A;
char m[500][99],v[99],R;
#undef main
#define o {
#define C  }
#define Y {}
#define X
#include <math.h>
#include <stdio.h>
