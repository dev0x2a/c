#include <stdio.h>
#include "alg.h"

int main(int argc, char *argv[])
{
  int i, j, key;

  unsigned int k = m_atoi(argv[1]);
  unsigned long int a[k];
  printf("a[%d] = {\n\t", k);

  //m_srand(k);

  for (i=0; i<k; ++i) {
    a[i] = m_rand();
    printf("%ld ", a[i]);
  }
  puts("\n}\nsort:\n");

  for (j=2; j<k; ++j) {
    key = a[j];
    /* insert a[j] into the sorted seq [1..j-1] */
    i = j-1;
    while (i>0 && a[i]>key) {
      a[i+1] = a[i];
      i -= 1;
    }
    a[i+1] = key;
  }
  putchar('\n');

}

