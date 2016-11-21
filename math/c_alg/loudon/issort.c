/* issort.c: insertion sort */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int issort(
    void *data, int size, int esize,
    int (*compare)(const void *key1, const void *key2))
{
  char *a = data;
  void *key;
  int i, j;
  
  /* allocate memory for the key element */
  if ((key=(char *)malloc(esize)) == NULL)
      return(-1);
  
  /* repeatedly insert a key element among the sorted elements */
  for (j=1; j<size; ++j) {
    memcpy(key, &a[j*esize], esize);
    i = j-1;

    /* determine the position at which to insert the key element */
    while (i>=0 && compare(&a[i*esize], key)>0) {
      memcpy(&a[(i+1)*esize], &a[i*esize], esize);
      i--;
    }
    memcpy(&a[(i+1)*esize], key, esize);
  }
  /* free the storage allocated for storing */
  free(key);
  return 0;
}

int main(int argc, char *argv[])
{
  void *mdata;
  int size, esize;
  int (*compare)(const void *key1, const void *key2);

  size = 10;
  esize = 100;

  issort(mdata, size, esize, compare);
  return 0;
}

