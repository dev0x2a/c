#include <stdio.h>
#include <stdlib.h>
#include "alg.h"

int main(int argc, char *argv[])
{
  int i, j, key;

  unsigned int k = m_atoi(argv[1]);
  int *a;
  a = (int *)malloc(k*sizeof(int));
  printf("a[%d] = ", k);

  for (i=0; i<k; ++i) {
    a[i] = m_rand(); 
    printf("%d ", a[i]);
  }
  puts("\nsort:\n");

  i = 0;
  for (j=2; j<k; ++j) {
    key = a[j];
    /* insert a[j] into the sorted seq [1..j-1] */
    i = j-1;  
    do {
      a[i+1] = a[i];
      i -= 1;
    } while (i>0 && a[i]>key);
    a[i+1] = key;
  }



#if 1
  for (i=0; i<k; ++i) {
    printf("%d ", a[i]);
  }
#endif
  putchar('\n');
  free(a);

}

