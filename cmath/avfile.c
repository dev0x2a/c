#include <stdio.h>

/* computes stats on a file of numbers */

int main(void)
{
  int k, count;
  float item, sum;

  FILE *fp;
  char *fname;

  printf("open ");
  scanf("%s", fname);
  fp = fopen(fname, "r");
  count = 0;
  sum = 0.0;

  do {
    k = fscanf(fp, "%f", &item);
    if (k == 1) {
      count++;
      sum += item;
    }
  } while (k != EOF);

  printf("  %d items\n  sum = %f\n", count,sum);

  if (count > 0)
    printf("  avg = %f\n", sum/count);

  fclose(fp);
  return 0;
}

