#include "../alg.h"
#define PGRM "Merge Sort"
#define DEBUG 0

//{{{
#if DEBUG
int main(int argc, char *argv[])
{
  c_atoi(4, argc, "<vector 1> <vector 2> <vector 3>");
  tprint(PGRM);
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
  aexit(0, PGRM);
}
#endif
//}}}

int main(int argc, char *argv[])
{
  int i, j, p, k, n;
  int a, K;
  int m = 7, M = 128, L = 1;
  int *a0, *a1, *a2;

  a0 = (int *)malloc(5*sizeof(int));
  a1 = (int *)malloc(5*sizeof(int));
  a2 = (int *)malloc(5*sizeof(int));

  for (i=1; i<=m; ++i) {
    K = M>>i;
    a = 1<<i;
    for (j=0; j<K; ++j) {
      n=p=0;
      for (k=0; k<2*L; ++k) {
        if (a0[a*j+n] < a0[a*j+L+p]) {
          a1[a*j+k] = a0[a*j+n];
          n++;
        } else {
          a1[a*j+k] = a0[a*j+L+p];
          p++;
        }
        if ((n>=L) || (p>=L)) {
          k++;
          break;
        }
      }
      if (n < p)
        for (; k<2*L; ++k) {
          a1[a*j+k] = a0[a*j+n];
          n++;
        }
      else
        for (; k<2*L; ++k) {
          a1[a*j+k] = a0[a*j+L+p];
          p++;
        }
    }
    L <<= 1;
    *a2 = *a1;
    *a1 = *a0;
    *a0 = *a2;
  }
  for (i=0; i<=5; ++i)
    printf("%d ", a0[i]);

  aexit(0, PGRM);
}

