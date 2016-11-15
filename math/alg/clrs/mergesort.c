#include "alg.h"
#define PGRM "Merge Sort"
#define DEBUG 0
#define DEBUG1 1

#if DEBUG1
double mfloor(const double n)
{
  double q;
  asm("roundsd $1, %1, %0" : "=x" (q) : "xm" (n));
  return(q);
}

int merge(int a[], const int p, const int q, const int r)
{
  /* p<=q<r */
  int i, j, k, n1, n2;
  n1 = q-p+1; 
  n2 = r-q;
  //int *la = (int *)malloc((n1+1)*sizeof(int));
  //int *ra = (int *)malloc((n2+1)*sizeof(int));
  int la[n1];
  int ra[n2];

  for (i=0; i<n1; ++i)
    la[i] = a[p+i-1];
  for (j=0; j<n2; ++j)
    ra[j] = a[q+j];
  la[n1+1] = -0x1;
  ra[n2+1] = -0x1;

  i=j=0;
  for (k=p; k<=r; ++k) {
    if (la[i] <= ra[j]) {
      a[k-1] = la[i];
      ++i;
    } else {
      a[k-1] = ra[j];
      ++j;
    }
  }
  //free(la);
  //free(ra);
  return(0);
}

int mergesort(int a[], const int p, const int r)
{
  int q;
  if (p < r) {
    q = (int)((p+r)/2);
    mergesort(a, p, q);
    mergesort(a, q+1, r);
    merge(a, p, q, r);
  }
  return(0);
}

int main(int argc, char *argv[])
{
  tprint(PGRM);
  int i;
  //int a[5] = {mrand(), mrand(), mrand(), mrand(), mrand()};
  int a[5] = {10,5,4,2,8};

  for (i=0; i<5; ++i)
    printf("%d\n", a[i]);

  mergesort(a, 0, 4);
  puts("\nsort:");

  for (i=0; i<5; ++i)
    printf("%d\n", a[i]);

  putchar('\n');
  aexit(0, PGRM);
}
#endif

//{{{
#if DEBUG
int main(int argc, char *argv[])
{
  int i, j, p, k, n;
  int a, K;
  int m = 7, M = 128, L = 1;
  int *a0, *a1, *a2;

  a0 = (int *)malloc(5*sizeof(int));
  a1 = (int *)malloc(5*sizeof(int));
  a2 = (int *)malloc(5*sizeof(int));

  for (i=1; i<=m; ++i) {
    K = M>>i;
    a = 1<<i;
    for (j=0; j<K; ++j) {
      n=p=0;
      for (k=0; k<2*L; ++k) {
        if (a0[a*j+n] < a0[a*j+L+p]) {
          a1[a*j+k] = a0[a*j+n];
          n++;
        } else {
          a1[a*j+k] = a0[a*j+L+p];
          p++;
        }
        if ((n>=L) || (p>=L)) {
          k++;
          break;
        }
      }
      if (n < p)
        for (; k<2*L; ++k) {
          a1[a*j+k] = a0[a*j+n];
          n++;
        }
      else
        for (; k<2*L; ++k) {
          a1[a*j+k] = a0[a*j+L+p];
          p++;
        }
    }
    L <<= 1;
    *a2 = *a1;
    *a1 = *a0;
    *a0 = *a2;
  }
  for (i=0; i<=5; ++i)
    printf("%d ", a0[i]);

  aexit(0, PGRM);
}
#endif
//}}}

