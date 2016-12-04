#include <stdio.h>
#include <stdlib.h>
//#include "clrs.h"

//#define PGRM "Merge Sort"
#define DEBUG 0
#define DEBUG1 0

void merge(int *a, int n, int m)
{
  int i, j, k;
  int *x = malloc(n * sizeof(int));

  for (i=0, j=m, k=0; k<n; ++k) {
    x[k] = j == n ?      a[i++]
         : i == m ?      a[j++]
         : a[j] < a[i] ? a[j++]
         :               a[i++];
  }
  for (i=0; i<n; ++i) {
    a[i] = x[i];
  }
  free(x);
}

void mergesort(int *a, int n)
{
  if (n < 2)
    return;
  int m = n/2;
  mergesort(a, m);
  mergesort(a+m, n-m);
  merge(a, n, m);
}

int main(void)
{
#define SIZE 10
  //int a[SIZE] = {5,8,1,2,5,6,1,2,7,3};
  int a[SIZE];
  int i;
  for (i=0; i<SIZE; ++i)
    scanf("%d", &a[i]);
  int n = sizeof a / sizeof a[0];
  for (i=0; i<n; ++i)
    printf("%d%s", a[i], i==n-1 ? "\n" : " ");
  mergesort(a, n);
  for (i=0; i<n; ++i)
    printf("%d%s", a[i], i==n-1 ? "\n" : " ");
  return 0;
}


#if DEBUG1
double mfloor(const double n)
{
  double q;
  asm("roundsd $1, %1, %0" : "=x" (q) : "xm" (n));
  return q;
}

void merge(int *a, int p, int q, int r)
{
  /* p<=q<r */
  int i, j, k, n1, n2;
  n1 = q-p+1; 
  n2 = r-q;
  int la[n1+1];
  int ra[n2+1];

  for (i=0; i<n1; ++i)
    la[i] = a[p+i-1];
  for (j=0; j<n2; ++j)
    ra[j] = a[q+j];
  la[n1+1] = -1;
  ra[n2+1] = -1;

  i=j=0;
  for (k=p; k<r; ++k) {
    if (la[i] <= ra[j]) {
      a[k] = la[i];
      ++i;
    } else {
      a[k] = ra[j];
      ++j;
    }
  }
}

void mergesort(int *a, int p, int r)
{
  int q;
  if (p < r) {
    q = (int)((p+r)/2);
    mergesort(a, p, q);
    mergesort(a, q+1, r);
    merge(a, p, q, r);
  }
}

int main(int argc, char *argv[])
{
  tprint(PGRM);
  int i;
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

#if DEBUG
int main(int argc, char *argv[])
{
  int i, j, p, k, n;
  int a, K;
  int m = 7, M = 128, L = 1;
  int *a0, *a1, *a2;

  a0 = malloc(5*sizeof(int));
  a1 = malloc(5*sizeof(int));
  a2 = malloc(5*sizeof(int));

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

