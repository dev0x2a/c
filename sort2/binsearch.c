#include <stdio.h>

int binsearch(int x, int k[], int n)
{
  int middle, left, right;
  if (x <= k[0])
    return 0;
  if (x > k[n-1])
    return n;
  left = 0;
  right = n-1;
  while (right-left > 1) {
    middle = right+left>>1;
    if (x <= k[middle])
      right = middle;
    else
      left = middle;
  }
  return right;
}

int main(void)
{
  int a[7] = {0,1,2,3,4,5,6};
  int i, x=4, n=7;

  i = binsearch(x, a, n);

  if (i<n && x==a[i]) {
    printf("found (A) %d\n", i);
  } else {
    printf("not found (B) %d\n", i);
  }
  return 0;
}

