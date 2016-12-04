#include <stdio.h>

void quicksort(int *a, int n)
{
  int i, j, p, t;
  if (n < 2)
    return;
  
  p = a[n/2];
  for (i=0, j=n-1 ;; ++i, --j) {
    while (a[i] < p)
      i++;
    while (p < a[j])
      j--;
    if (i >= j)
      break;
    t = a[i];
    a[i] = a[j];
    a[j] = t;
  }
  quicksort(a, i);
  quicksort(a+i, n-i);
}

int main(void)
{
  int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
  int n = sizeof a / sizeof a[0];
  int i;

  for (i=0; i<n; ++i)
    printf("%d%s", a[i], i==n-1 ? "\n" : " ");
  quicksort(a, n);
  for (i=0; i<n; ++i)
    printf("%d%s", a[i], i==n-1 ? "\n" : " ");
  return 0;
}

