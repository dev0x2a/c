#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  int i, n;
  float *data;
  
  printf("enter elements:\t");
  scanf("%d", &n);

  data = (float *)calloc(n, sizeof(float));

  if (data == NULL) {
    printf("error:\tmemory not allocated\n");
    exit(0);
  }
  printf("\n");
  
  for (i=0; i<n; ++i) {
    printf("enter number %d:\t", i + 1);
    scanf("%f", data + i);
  }
  for (i=1; i<n; ++i) {
    if (*data<*(data + i))
      *data=*(data + i);
  }
  printf("largest element:\t%.2f\n\n", *data);
  return 0;
}

