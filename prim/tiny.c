#if 0
#include <stdio.h>
#endif

#define TPI_1   0
#define TPI_2   0
#define TPI_3   0

#define TE_1    0

#define TLOG2_1 0
#define TLOG2_2 0

#define T_SQ2_1 0

#define T_GR_1  1

#if TPI_1
int a=10000,b,c=8400,d,e,f[8401],g;main(){
for(;b-c;)f[b++]=a/5;
for(;d=0,g=c*2;c-=14,printf("%.4d",e+d/a),e=d%a)
for(b=c;d+=f[b]*a,f[b]=d%--g,d/=g--,--b;d*=b);}
#endif

#if TPI_2
main(){int a=1e4,c=3e3,b=c,d=0,e=0,f[3000],g=1,h=0;
for(;b;!--b?printf("%04d",e+d/a),e=d%a,h=b=c-=15:(f[b]=
(d=d/g*b+a*(h?f[b]:2e3))%(g=b*2-1)));}
#endif

#if TPI_3
long k=4e3,p,a[337],q,t=1e3;
main(j){for(;a[j=q=0]+=2,--k;)
for(p=1+2*k;j<337;q=a[j]*k+q%p*t,a[j++]=q/p)
k!=j>2?:printf("%.3d",a[j-2]%t+q/p/t);}
#endif

#if TE_1
main(){int N=9009,n=N,a[9009],x;while(--n)a[n]=1+1/n;
for(;N>9;printf("%d",x))
for(n=N--;--n;a[n]=x%n,x=10*a[n-1]+x/n);}
#endif

#if TLOG2_1
main(){int a=1000,b=0,c=7973,d,f[7974],n=800,k;
for(;b<c;f[b++]=5);
for(;n--;d+=*f*a,printf("%.3d",d/a),*f=d%a)
for(d=0,k=c;--k;d/=b,d*=k)f[k]=(d+=f[k]*a)%(b=2*k+2);}
#endif

#if TLOG2_2
main(){int a=1000,b=0,c=2658,d=75,f[2659],n=800,k;
for(;b<c;f[b++]=d,d=-d);
for(;n--;d+=*f*a,printf("%.3d",d/a),*f=d%a)
for(d=0,k=c;--k;d/=b,d*=k)f[k]=(d+=f[k]*a)%(b=8*k+4);}
#endif

#if T_SQ2_1
main(){int a=1000,b=0,c=1413,d,f[1414],n=800,k;
for(;b<c;f[b++]=14);
for(;n--;d+=*f*a,printf("%.3d",d/a),*f=d%a)
for(d=0,k=c;--k;d/=b,d*=2*k-1)f[k]=(d+=f[k]*a)%(b=100*k);}
#endif

#if T_GR_1
main(){int a=1000,b=0,c=3434,d,f[3435],n=800,k;
for(;b<c;f[b++]=1);f[1]+=5;
for(;n--;d+=*f*a,printf("%.3d",d/a),*f=d%a)
for(d=0,k=c;--k;d/=b,d*=2*k-1)f[k]=(d+=f[k]*a)%(b=10*k);}
#endif
