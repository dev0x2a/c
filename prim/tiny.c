#if 1
#include <stdio.h>
/* 
 * added for printf() calls
 */
#endif
#define TPI_1   0
#define TPI_2   0
#define TPI_3   0
#define TE_1    0
#define TLOG2_1 0
#define TLOG2_2 0
#define T_SQ2_1 0
#define T_GR_1  0
#define T_GEN_1 0
#define T_EUL_1 0
#define T_PRI_1 0
#define T_PRI_2 0
#define T_FFT_1 1

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

#if T_GEN_1
main(){for(d=0,k=c;--k;d/=b,d*=2*k-1)f[k]=(d+=f[k]*a)%(b=100*k);}
#endif

#if T_EUL_1
int*d,*e,w[2850],p=475,b=10000,r=3,i,j,x;s(int k){d=w+k/14%4*p;
e=w+k/56*p;for(x=k&1,j=k/2%7*p;j--;k&1?*d=(x+=k-49?*e++-*d+b-1:
(r?r-1?4096:3888:4374)**d)%b,d++,x/=b:(x=x%i*b+e[j],d[j]=x/i));
}main(){for(;r<3&i++<33*p+!r?s(216),s(49),s(242),s(59),1:r?i=0,
w[5*p]=--r?r-1?23:84:60:printf("%.4d",w[--p])&&p>53;);}
#endif

#if T_PRI_1
main(){for(int p=1,i;++p<1e5;i>p?printf("%d ",p):0)for(i=2;p%i++;);}
#endif

#if T_PRI_2
main(){int a[100000],i=1e5,n=i,p=1;while(--i)a[i]=1;
while(++p<n)for(a[p]?printf("%d ",i=p):0;p<4e4&&i*p<n;a[i++*p]=0);}
#endif

#if T_FFT_1
int m=754974721,N,t[1<<22],a,*p,i,e=4625195,j,s,b,c,U;f(d){for(s
=1<<23;s;s/=2,d=d*1LL*d%m)if(s<N)for(p=t;p<t+N;p+=s)for(i=s,c=1;
i;i--)b=*p+p[s],p[s]=(m+*p-p[s])*1LL*c%m,*p++=b%m,c=c*1LL*d%m;
for(j=0;i<N-1;){for(s=N/2;!((j^=s)&s);s/=2);if(++i<j)a=t[i],t[i]
=t[j],t[j]=a;}}main(){*t=2;U=N=1;while(e/=2){N*=2;U=U*1LL*(m+1)/
2%m;f(362);for(p=t;p<t+N;)*p++=*p*1LL**p%m*U%m;f(415027540);for(
a=0,p=t;p<t+N;)a+=*p<<(e&1),*p++=a%10,a/=10;}while(!*--p);t[0]--
;while(p>=t)printf("%d",*p--);}
#endif
