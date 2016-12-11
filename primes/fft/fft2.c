
void FFT(unsigned logN, double *real, double *im) /* logN is base 2 log(N) */
{
  unsigned n=0, nspan, span, submatrix, node;
  unsigned N=1<<logN;
  double tmp, primitive, angle, realtw, imtw;

  for (span=N>>1; span; span>>=1) {
    primitive = MINPI/span;
    for (submatrix=0; submatrix<(N>>1); ++submatrix) {
      for (node=0; node<span; ++node) {
        nspan = n+span;
        tmp = real[n]+real[nspan];
        real[nspan] = real[n]-real[nspan];
        real[n] = tmp;
        tmp = im[n]+im[nspan];
        im[nspan] = im[n]-im[nspan];
        im[n] = tmp;

        angle = primitive*node;
        realtw = cos(angle);
        imtw = sin(angle);
        tmp = realtw*real[nspan]-imtw*im[nspan];
        im[nspan] = realtw*im[nspan]+imtw*real[nspan];
        real[nspan] = tmp;
        ++n;
      }
      n = (n+span) & (N-1);
    }
  }
}

void unityroots(double *realtw, double *imtw, unsigned logN)
{
  double twopi = 6.28318530717959;
  unsigned n, N;

  N = 1<<logN;
  for (n=0; n<(N>>1); ++n) {
    realtw[n] = cos(twopi*n/N);
    imtw[n] = -sin(twopi*n/N);
  }
}

void fft(double *real, double *im, double *realtw, double *imtw, int N)
{
  unsigned even, odd, span, log, rootindex;
  double tmp;
  log=0;

  for (span=N>>1; span; span>>=1,++log) {
    for (odd=span; odd<N; ++odd) {
      odd |= span;
      even = odd^span;

      tmp = real[even]+real[odd];
      real[odd] = real[even]-real[odd];
      real[even] = tmp;

      tmp = im[even]+im[odd];
      im[odd] = im[even]-im[odd];
      im[even] = tmp;

      rootindex = (even<<log) & (N-1);
      if (rootindex) {
        tmp = realtw[rootindex]*real[odd]-imtw[rootindex]*im[odd];
        im[odd] = realtw[rootindex]*im[odd]+imtw[rootindex]*real[odd];
        real[odd] = tmp;
      }
    }
  }
}

typedef struct {
  double *re, *im;
} complex_t;

void sfft(complex_t *c, double *realtw, double *imtw, int N)
{
  unsigned even, odd, span, log=0, rootindex;
  double tmp;

  for (span=N>>1; span; span>>=1,++log) {
    for (odd=span; odd<N; ++odd) {
      odd |= span;
      even = odd^span;

      tmp = c->real[even]+c->real[odd];
      c->real[odd] = c->real[even]-c->real[odd];
      c->real[even] = tmp;

      tmp = c->im[even]+c->im[odd];
      c->im[odd] = c->im[even]-c->im[odd];
      c->im[even] = tmp;

      rootindex = (even<<log) & (N-1);
      if (rootindex) {
        tmp=realtw[rootindex]*c->real[odd]-imtw[rootindex]*c->im[odd];
        c->im[odd]=realtw[rootindex]*c->im[odd]+imtw[rootindex]*c->real[odd];
        c->real[odd]=tmp;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  complex_t *c;
  return 0;
} 
