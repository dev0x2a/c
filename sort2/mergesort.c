#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

double mfloor(const double n)
{
  double q;
  asm("roundsd $1, %1, %0" : "=x" (q) : "xm" (n));
  return q;
}

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

