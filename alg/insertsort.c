#include <stdio.h>
#include <stdlib.h>
#include "alg.h"

int main(int argc, char *argv[])
{
  int i, j, key;

  unsigned int k = m_atoi(argv[1]);
  int *a;
  a = (int *)malloc(k*sizeof(int));
  printf("a[%d] = {\n\t", k);

  for (i=0; i<k; ++i) {
    a[i] = m_rand(); 
    printf("%d ", a[i]);
  }
  puts("\n}\nsort:\n");

  for (j=2,i=0; j<k; ++j) {
    key = a[j];
    /* insert a[j] into the sorted seq [1..j-1] */
    i = j-1;
    while (i>0 && a[i]>key) {
      a[i+1] = a[i];
      i -= 1;
    }
    a[i+1] = key;
  }
  printf("%d ", a[0]);
#if 0
  for (i=0; i<k; ++i) {
    printf("%d ", a[i]);
  }
#endif
  putchar('\n');

}

