#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define q 3      /* for 2^3 points */
#define N (1<<q) /* N-point FFT, iFFT */
#define DATAFILE 1

typedef float real;
typedef struct complex_st {
  real re, im;
} complex_t;

#ifndef PI
#define PI 3.14159265358979323846264338327950288
#endif

static void printvector(const char *name, complex_t *c, int n)
{
  int i;
  printf("%s (dim=%d):", name,n);
  for (i=0; i<n; ++i)
    printf(" %5.2f,%5.2f ", c[i].re,c[i].im);
  putchar('\n');
  return;
}

/* fft(v,N):
   [0] if N==1, return
   [1] for k=0 to N/2-1, let ve[k] = v[2*k]
   [2] compute fft(ve,N/2)
   [3] for k=0 to N/2-1, let vo[k] = v[2*k+1]
   [4] compute fft(vo,N/2)
   [5] for m=0 to N/2-1, do [6] through [9]
   [6]   let w.re = cos(2*pi*m/N)
   [7]   let w.im = -sin(2*pi*m/N)
   [8]   let v[m] = ve[m] + w*vo[m];
   [9]   let v[m+N/2] = ve[m] - w*vo[m] */
void fft(complex_t *v, int n, complex_t *tmp)
{
  if (n > 1) {
    int k, m;
    complex_t z, w, *vo, *ve;
    
    ve = tmp;
    vo = tmp+n/2;
    for (k=0; k<n/2; ++k) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    fft(ve, n/2, v);
    fft(vo, n/2, v);
    for (m=0; m<n/2; ++m) {
      w.re = cos(2*PI*m/(double)n);
      w.im = -sin(2*PI*m/(double)n);
      z.re = w.re*vo[m].re-w.im*vo[m].im;
      z.im = w.re*vo[m].im+w.im*vo[m].re;
      v[m].re = ve[m].re+z.re;
      v[m].im = ve[m].im+z.im;
      v[m+n/2].re = ve[m].re-z.re;
      v[m+n/2].im = ve[m].im-z.im;
    }
  }
  return;
}

/* ifft(v,N):
   [0] if N==1, return
   [1] for k=0 to N/2-1, let ve[k] = v[2*k]
   [2] compute ifft(ve,N/2)
   [3] for k=0 to N/2-1, let vo[k] = v[2*k+1]
   [4] compute ifft(vo,N/2)
   [5] for m=0 to N/2-1, do [6] through [9]
   [6]   let w.re = cos(2*pi*m/N)
   [7]   let w.im = sin(2*pi*m/N)
   [8]   let v[m] = ve[m] + w*vo[m];
   [9]   let v[m+N/2] = ve[m] - w*vo[m] */
void ifft(complex_t *v, int n, complex_t *tmp)
{
  if (n > 1) {
    int k, m;
    complex_t z, w, *vo, *ve;
    
    ve = tmp;
    vo = tmp+n/2;
    for (k=0; k<n/2; ++k) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    ifft(ve, n/2, v);
    ifft(vo, n/2, v);
    for (m=0; m<n/2; ++m) {
      w.re = cos(2*PI*m/(double)n);
      w.im = sin(2*PI*m/(double)n);
      z.re = w.re*vo[m].re-w.im*vo[m].im;
      z.im = w.re*vo[m].im+w.im*vo[m].re;
      v[m].re = ve[m].re+z.re;
      v[m].im = ve[m].im+z.im;
      v[m+n/2].re = ve[m].re-z.re;
      v[m+n/2].im = ve[m].im-z.im;
    }
  }
  return;
}

int main(int argc, char *argv[])
{
  complex_t v[N], v1[N], tmp[N];
  int k;

  /* fill v[] with function of known FFT */
  for (k=0; k<N; ++k) {
    v[k].re = 0.125*cos(2*PI*k/(double)N);
    v[k].im = 0.125*sin(2*PI*k/(double)N);
    v1[k].re = 0.3*cos(2*PI*k/(double)N);
    v1[k].im = -0.3*sin(2*PI*k/(double)N);
  }
#if !DATAFILE
  /* v[] */
  printvector("original", v, N);
  fft(v, N, tmp);
  printvector(" FFT", v, N);
  ifft(v, N, tmp);
  printvector("iFFT", v, N);

  /* v1[] */
  printvector("original", v1, N);
  fft(v1, N, tmp);
  printvector(" FFT", v1, N);
  ifft(v1, N, tmp);
  printvector("iFFT", v1, N);
#else
  puts("original");
  for (k=0; k<N; ++k)
    printf("%5.2f,%5.2f\n", v[k].re,v[k].im);
  puts("FFT");
  fft(v, N, tmp);
  for (k=0; k<N; ++k)
    printf("%5.2f,%5.2f\n", v[k].re,v[k].im);
#endif
  exit(EXIT_SUCCESS);
}

