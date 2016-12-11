#include <stdio.h>
#include <math.h>

void fourier(float *data,int nn,int isign)
{ /* nn must be an integer power of 2 */
#define SWAP(a,b) rtmp=(a);(a)=(b);(b)=rtmp
  int m,n,i,j,mmax,istep;
  double wtmp,wr,wpr,wpi,wi,theta;
  float rtmp,itmp;
  
  n=nn<<1;
  j=1;
  for (i=1; i<n; i+=2) {
    if (j>i) {
      SWAP(data[j],data[i]);
      SWAP(data[j+1],data[i+1]);
    }
    m=n>>1;
    while (m>=2 && j>m) {
      j-=m;
      m>>=1;
    }
    j+=m;
  }
  mmax=2;
  while (n>mmax) {
    istep=2*mmax;
    theta=6.28318530717959/(isign*mmax);
    wtmp=sin(0.5*theta);
    wpr=-2.0*wtmp*wtmp;
    wpi=sin(theta);
    wr=1.0;
    wi=0.0;
    for (m=1; m<mmax; m+=2) {
      for (i=m; i<=n; i+=istep) {
        j=i+mmax;
        rtmp=wr*data[j]-wi*data[j+1];
        itmp=wr*data[j+1]+wi*data[j];
        data[j]=data[i]-rtmp;
        data[j+1]=data[i+1]-itmp;
        data[i]+=rtmp;
        data[i+1]+=itmp;
      }
      wr=(wtmp=wr)*wpr-wi*wpi+wr;
      wi=wi*wpr+wtmp*wpi+wi;
    }
    mmax=istep;
  }
}

void twofourier(float *data1,float *data2,float *fft1,float *fft2,int n)
{
  int nn2, nn3, j, jj;
  float rep, rem, aip, aim;
  void fourier();

  nn3=1+(nn2=2+n+n);
  for (j=1,jj=2; j<=n; ++j,jj+=2) {
    fft1[jj-1]=data1[j];
    fft1[jj]=data2[j];
  }
  fourier(fft1,n,1);
  fft2[1]=fft1[2];
  fft1[2]=fft2[2]=0.0;
  for (j=3; j<=n+1; j+=2) {
    rep=0.5*(fft1[j]+fft1[nn2-j]);
    rem=0.5*(fft1[j]-fft1[nn2-j]);
    aip=0.5*(fft1[j+1]+fft1[nn3-j]);
    aim=0.5*(fft1[j+1]-fft1[nn3-j]);
    fft1[j]=rep;
    fft1[j+1]=aim;
    fft1[nn2-j]=rep;
    fft1[nn3-j]=-aim;
    fft2[j]=aip;
    fft2[j+1]=-rem;
    fft2[nn2-j]=aip;
    fft2[nn3-j]=rem;
  }
}

int main(void)
{
#define DATA 4
  int i,n=DATA;
  float data1[DATA]={3.0,4.0,2.0,1.0},
        data2[DATA]={8.0,9.0,3.0,2.0},
        fft1[DATA]={7.0,5.0,1.0,6.0},
        fft2[DATA]={2.0,4.0,9.0,8.0};
  for (i=0; i<DATA; ++i)
    printf("%f\n", data1[i]);
  for (i=0; i<DATA; ++i)
    printf("%f\n", data2[i]);
  for (i=0; i<DATA; ++i)
    printf("%f\n", fft1[i]);
  for (i=0; i<DATA; ++i)
    printf("%f\n", fft2[i]);
  twofourier(data1,data2,fft1,fft2,n);
  for (i=0; i<DATA; ++i)
    printf("%f\n", data1[i]);
  for (i=0; i<DATA; ++i)
    printf("%f\n", data2[i]);
  for (i=0; i<DATA; ++i)
    printf("%f\n", fft1[i]);
  for (i=0; i<DATA; ++i)
    printf("%f\n", fft2[i]);
  return 0;
}

