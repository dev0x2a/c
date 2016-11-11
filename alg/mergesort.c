#include "alg.h"
#define DEBUG 1

int main(int argc, char *argv[])
{
  c_atoi(2, argc);
  tprint("Insertion Sort");

  int i, j, key, *a;
  unsigned int k = m_atoi(argv[1]);
  
  a = (int *)malloc(k*sizeof(int));
  printf("a[%d] =\n", k);

  for (i=0; i<k; ++i) {
    scanf("%d", &a[i]);
    /* for psuedo-random numbers,
     * use:
     * a[i] = m_rand(); 
     * printf("%d ", a[i]);
     */
  }
  puts("\nsort:\n");

#if DEBUG
  for (j=1; j<k; ++j) {
    key = a[j];
    /* insert a[j] into the sorted seq [1..j-1] */
    i = j-1;  
    while (i>=0 && a[i]>key) {
      a[i+1] = a[i];
      i -= 1;
    }
    a[i+1] = key;
  }
  for (i=0; i<k; ++i) {
    printf("%d ", a[i]);
  }
  free(a);
  putchar('\n');
#endif
  
  aexit(0, "Insertion Sort");
}

