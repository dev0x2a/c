#include <stdio.h>

int
main(void)
{
  int i, n;
  float arr[100];

  printf("enter elements:\t");
  scanf("%d", &n);
  printf("\n");

  for (i=0; i<n; ++i) {
    printf("enter num %d:\t", i + 1);
    scanf("%f", &arr[i]);
  }
  for (i=1; i<n; ++i) { /*  store largest num to arr[o] */
    if (arr[0] < arr[i])
      arr[0] = arr[i];
  }
  printf("\nlargest element:\t%.2f\n", arr[0]);
  return 0;
}

