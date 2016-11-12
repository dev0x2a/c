#include "alg.h"
#define DEBUG 1

int main(int argc, char *argv[])
{
  char *pgrm = "Merge Sort";
  c_atoi(4, argc);
  tprint(pgrm);

  int i, j, k, n1, n2;
  int *la, *ra, *aa;
  unsigned int p = m_atoi(argv[1]), q = m_atoi(argv[2]), r = m_atoi(argv[3]);
  //aa = (int *)malloc(k*sizeof(int));

  n1 = q-p+1; 
  n2 = r-q;
  for (i=0; ; ++i) {
    scanf("%d", &aa[i]);
    /* for psuedo-random numbers,
     * use:
     * a[i] = m_rand(); 
     * printf("%d ", a[i]);
     */
  }

  for (i=1; i<=n1; ++i)
    la[i] = aa[p+i-1];
  for (j=1; j<=n2; ++j)
    ra[j] = aa[q+j];


#if DEBUG

  puts("\nsort:\n");

  for (i=j=1,k=p; k<=r; ++k) {
    if (la[i] <= ra[j]) {
      aa[k] = la[i];
      ++i;
    } else {
      aa[k] = ra[j];
      ++j;
    }
  }

  free(aa);
  free(ra);
  free(la);
  putchar('\n');
#endif
  aexit(0, pgrm);
}

