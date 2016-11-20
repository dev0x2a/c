#include <stdio.h>
#include <stdlib.h>

int a[7] = {0,1,2,3,4,5,6};

int
binsearch(int x, int k[], int n)
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

int
main(int argc, char *argv[])
{
  int i, x, n;

  x = atoi(argv[1]);
  n = atoi(argv[2]);
  i = binsearch(x, a, n);

  if (i<n && x==a[i]) {
    printf("found %d\n", i);
  } else {
    printf("not found %d\n", i);
  }
  return 0;
}

