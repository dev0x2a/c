#include <stdio.h>
#define TLOG2_1 1
#define TLOG2_2 0
#define T_SQ2_1 0

#if TLOG2_1
int main()
{
  int a=1000, b=0,
      c=7973, d,
      f[7974],
      n=800, k;
  for ( ; b<c; f[b++]=5);
  for ( ; n--; d+=*f*a,printf("%.3d",d/a),*f=d%a)
    for (d=0,k=c; --k; d/=b,d*=k)
      f[k] = (d+=f[k]*a)%(b=2*k+2);}
#endif

#if TLOG2_2
int main()
{
  int a=1000, b=0,
      c=2658, d=75,
      f[2659],
      n=800, k;
  for ( ; b<c; f[b++]=d,d=-d);
  for ( ; n--; d+=*f*a,printf("%.3d",d/a),*f=d%a)
    for (d=0,k=c; --k; d/=b,d*=k)
      f[k] = (d+=f[k]*a)%(b=8*k+4);
}
#endif

#if T_SQ2_1
main(){int a=1000,b=0,c=1413,d,f[1414],n=800,k;
for(;b<c;f[b++]=14);
for(;n--;d+=*f*a,printf("%.3d",d/a),*f=d%a)
for(d=0,k=c;--k;d/=b,d*=2*k-1)f[k]=(d+=f[k]*a)%(b=100*k);}
#endif

