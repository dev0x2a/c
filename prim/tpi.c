#include <stdio.h>

int b, d, e, g;
int a = 10000;
int c = 8400;
int f[8401];

int main(void)
{
  for ( ;b-c; ) {
    f[b++] = a/5;
  }
  for ( ;d=0,g=c*2; c-=14, printf("%.4d", e+d/a),e=d%a) {
    for (b=c; d+=f[b]*a,f[b]=d%--g,d/=g--,--b; d*=b);
  }
}

#if 0
main(){int a=1e4,c=3e3,b=c,d=0,e=0,f[3000],g=1,h=0;
for(;b;!--b?printf("%04d",e+d/a),e=d%a,h=b=c-=15:f[b]=
(d=d/g*b+a*(h?f[b]:2e3))%(g=b*2-1));}

long k=4e3,p,a[337],q,t=1e3;
main(j){for(;a[j=q=0]+=2,--k;)
for(p=1+2*k;j<337;q=a[j]*k+q%p*t,a[j++]=q/p)
k!=j>2?:printf("%.3d",a[j-2]%t+q/p/t);}
#endif
