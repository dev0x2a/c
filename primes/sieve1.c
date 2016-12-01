#include <stdio.h>
#include <stdlib.h>

#define SIEVE1 0
#define SIEVE2 1

#if SIEVE1
#include <math.h>

char *eratosthenes(int n, int *c)
{
  char *sieve;
  int i, j, m;

  if (n < 2)
    return NULL;
  
  *c = n-1; /* prime count */
  m = (int) sqrt((double)n);
  
  sieve = calloc(n+1, sizeof(char));
  sieve[0] = 1;
  sieve[1] = 1;
  for (i=2; i<=m; ++i)
    if (!sieve[i])
      for (j=i*i; j<=n; j+=i)
        if (!sieve[j]) {
          sieve[j] = 1;
          --(*c);
        }
  return sieve;
}
#endif /* SIEVE1 */

#if SIEVE2
//#include <malloc.h>
void sieve(int *, int);

int main(int argc, char *argv[])
{
  int *array, n=10;
  array = (int *)malloc(sizeof(int));
  putchar('\n');
  sieve(array, n);
  return 0;
}

void sieve(int *a, int n)
{
  int i=0, j=0;

  for (i=2; i<=n; ++i)
    a[i] = 1;

  for (i=2; i<=n; ++i) {
    printf("i:%d\n", i);
    if (a[i] == 1) {
      for (j=i; (i*j)<=n; ++j) {
        printf("j:%d\n", j);
        printf("  antes de a[%d*%d]: %d\n", i,j,a[i*j]);
        a[(i*j)] = 0;
        printf("despues de a[%d*%d]: %d\n", i,j,a[i*j]);
      }
    }
  }
  printf("\nprimos entre 1 y %d son: ", n);
  for (i=2; i<=n; ++i)
    if (a[i] == 1)
      printf("%d, ", i);
  printf("\n\n");
}
#endif /* SIEVE2 */

