#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n)
{
  int i, j, k, gap, tmp;

  for (gap=n/2; gap>0; gap/=2)
    for (i=gap; i<n; ++i)
      for (j=i-gap; j>=0&&v[j]>v[j+gap]; j-=gap) {
        tmp=v[j];
        v[j]=v[j+gap];
        v[j+gap]=tmp;
      }
  for(k=0; k<n; ++k)
    printf("%d\t", v[k]);
  putchar('\n');
}

int main(void)
{
  int v[SIZE], k;

  srand(time(NULL));

  for (k=0; k<SIZE; ++k)
    v[k] = rand()%SIZE;

  shellsort(v, SIZE);
  return(0);
}

