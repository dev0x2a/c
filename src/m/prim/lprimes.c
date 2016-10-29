#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define	T (o(t)/o(*(t+0)))
#define	P (o(p)/o(*(p+0)))
#define	W (o(w)/o(*(w+0)))
#define E return(0)
#define R printf
#define M modf
#define A atof
#define S sqrt
#define H main
#define F for
#define I if
#define C continue
#define h char
#define V void
#define d double
#define l long
#define z int
#define u unsigned h
#define o sizeof
d N=9.007199254740992e15,w[]={10,2,4,2,4,6,2,6,4,2,4,6,6,2,6,4,2,6,4,6,8,4,2,4,2
,4,8,6,4,6,2,4,6,2,6,6,4,2,4,6,2,6,4,2,4,2,10,2};u t[1000],b[]={1,2,4,8,16,32,64
,128};z p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89
,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,
197,199,211,223,227,229};V m(d n,l k){d r;l j;M(n/k,&r);j=k*r-n;I(j<0)j+=k;F(;j<
T*8;j+=k){t[j>>3]|=b[j&7];}}z H(z c,h**a){I(c<=1)E;z i;d k,v,e,L,n=A(a[1]);L=N;I
(c>2){L=A(a[2]);I(L<n)E;I(L>N)E;}I(n<0||n>N)E;I(n==0)n=1;I(n<230){F(i=0;i<P;++i)
{I(p[i]<n)C;I(p[i]>L)E;R("%d\n",p[i]);I(L>=N)E;}n=230;}M(n/2,&e);n=2.*e+1;F(;;){
F(i=0;i<T;++i)t[i]=0;v=S(n+T*8);m(n,3);m(n,5);m(n,7);F(i=0,k=11;k<=v;k+=w[i]){m(
n,k);++i;I(i>=W)i=0;}F(i=0;i<T*8;i+=2){I(t[i>>3]&b[i&7])C;e=n+i;I(e>L)E;R("%.0f\
\n",e);I(L>=N)E;}n+=T*8;}}/****************************************************/

