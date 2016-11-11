#include "alg.h"
#define DEBUG 1

int main(int argc, char *argv[])
{
  char *pgrm = "Merge Sort";
  c_atoi(4, argc);
  tprint(pgrm);

  int i, j, n1, n2;
  int *la, *ra, *aa;
  unsigned int p = m_atoi(argv[1]), q = m_atoi(argv[2]), r = m_atoi(argv[3]);
  //aa = (int *)malloc(k*sizeof(int));

  n1 = q-p+1; 
  n2 = r-q;

  for (i=1; i<=n1; ++i)
    la[i] = aa[p+i-1];
  for (j=1; j<=n2; ++j)
    ra[j] = aa[q+j];

#if 0
  //printf("a[%d] =\n", k);

  for (i=0; i<k; ++i) {
    scanf("%d", &aa[i]);
    /* for psuedo-random numbers,
     * use:
     * a[i] = m_rand(); 
     * printf("%d ", a[i]);
     */
  }
#endif
  puts("\nsort:\n");

#if DEBUG
  free(aa);
  free(ra);
  free(la);
  putchar('\n');
#endif
  aexit(0, pgrm);
}

