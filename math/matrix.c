#include <stdio.h>
#include <stdlib.h>

void dot(int **a, int **b, int **c, int n)
{
  int i, j, k;
  for (i=0; i<n; ++i)
    for (k=0; k<n; ++k)
      for (j=0; j<n; ++j)
        c[i][j] += a[i][k]*b[k][j];
}
    
int main()
{
  int i, j, n;
  int **a1, **a2;
//      int **a3;
  i=j=0;
  n = 3;
  
  a1 = malloc(n*sizeof(int));
  a2 = malloc(n*sizeof(int));
//  a3 = malloc(n*sizeof(int));


  for (i=0; i<n; ++i) {
    for (j=0; j<n; ++j) {
      a1[i][j] = i;
      a2[i][j] = i;
    }
  }
  for (i=0; i<n; ++i) {
    for (j=0; j<n; ++j) {
      printf("%d ", a1[i][j]);
    }
    putchar('\n');
  }
  for (i=0; i<n; ++i) {
    for (j=0; j<n; ++j) {
      printf("%d ", a2[i][j]);
    }
    putchar('\n');
  }

#if 0
  dot(a1, a2, a3, n);

  for (i=0; i<n; ++i) {
    for (j=0; j<n; ++j) {
      printf("%d ", a3[i][j]);
    }
    putchar('\n');
  }
#endif
  free(a1);
  free(a2);
//  free(a3);
  return 0;
}

