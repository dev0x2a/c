#include <stdio.h>
#include <stdlib.h>

/* creates a file of N random numbers */

int main(void)
{
  int i, N;
  FILE *fp;
  char *fname;

  printf("num gen  ");
  scanf("%d", &N);
  printf("filename ");
  scanf("%s", fname);

  fp = fopen(fname, "w");
  for (i=0; i<N; ++i)
    fprintf(fp, "%5d\n", rand()%32767);

  fclose(fp);
  return 0;
}

