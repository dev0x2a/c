#include <stdio.h>
#include <stdlib.h>

#define USECOL 1

unsigned long long *c;

void coef(int, int);
void show(int);
/*int isprime(int);*/

int main(int argc, char *argv[])
{
  int n, lim = atoi(argv[1])*10;
  c = malloc(lim*sizeof(int));
  if (!c) {
    puts("could not allocate memory\n");
    exit(1);
  }
  for (n=0; n<(int)lim/10; ++n) {
    coef(n, lim);
#if USECOL
    printf("\033[3m(x-1)^%d\033[0m = ", n);
#else
    printf("(x-1)^%d\033 = ", n);
#endif
    show(n);
    putchar('\n');
  }
/*printf("\nprimes (excluding 1): ");
  for (n=1; n<=LIM; ++n)
    if (isprime(n))
      printf(" %d", n);*/
  free(c);
  putchar('\n');
  return 0;
}

void coef(int n, int lim)
{
  int i, j;
  if (n<0 || n>lim)
    abort();
  for (c[i=0]=1; i<n; c[0]=-c[0],++i)
    for (c[1+(j=i)]=1; j>0; --j)
      c[j] = c[j-1]-c[j];
}
/*int isprime(int n)
{
  int i;
  coef(n, lim);
  c[0] += 1, c[i=n] -= 1;
  while (i-- && !(c[i] % n));
  return i < 0;
}*/
void show(int n)
{
  do
#if USECOL
    printf("\033[31m%+lld\033[0mx^\033[35m%d\033[0m", c[n],n);
#else
    printf("%+lldx^%d", c[n],n);
#endif
  while (n--);
}

