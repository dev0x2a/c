/*
 * p18
 * insertion sort (A)
 * 
 *   for j=2 to A.length
 *       key = A[j]
 *       // insert A[j] into the sorted seq A[1..j-1]
 *       i = j-1
 *       while i>0 and A[i]>key
 *           A[i+1] = A[i]
 *           i = i-1;
 *       A[i+1] = key
 */

#include "clrs.h"
#define PGRM "Insertion Sort"

int main(int argc, char *argv[])
{
  catoi(2, argc, "<vector size>");
  tprint(PGRM);

  int i, j, key, *a;
  unsigned int k = matoi(argv[1]);
  
  a = (int *)malloc(k*sizeof(int));
  printf("a[%d] =\n", k);

  for (i=0; i<k; ++i) {
    scanf("%d", &a[i]);
    /* for psuedo-random numbers,
     * use:
     * a[i] = mrand(); 
     * printf("%d ", a[i]);
     */
  }
  puts("\nsort:\n");

  for (j=1; j<k; ++j) {
    key = a[j];
    /* insert a[j] into the sorted seq [1..j-1] */
    i = j-1;  
    while (i>=0 && a[i]>key) {
      a[i+1] = a[i];
      --i;
    }
    a[i+1] = key;
  }
  for (i=0; i<k; ++i) {
    printf("%d ", a[i]);
  }
  free(a);
  putchar('\n');
  aexit(0, PGRM);
}

