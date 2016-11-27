#include <stdio.h>

int main(int argc, char *argv[])
{
  int i, k;
  unsigned long long n;
  FILE *fp;
  char c;

  if (argc < 2) {
    fprintf(stderr, "%s [FILE]\n", argv[0]);
    return(-1);
  }
  fp = fopen(argv[1], "r");

  if (!fp) {
    fprintf(stderr, "%s: %s cannot be opened\n", argv[0],fp);
    return(-1);
  }

  k = 1;
  while (fscanf(fp, "%c", &c) != EOF) {
    if (c == ',')
      ++k;
  }
  fclose(fp);
  printf("\ninit p[%d]\n\n", k);

  unsigned long long p[k];
  fp = fopen(argv[1], "r");
  i = 0;
  
  while (fscanf(fp, "%llu,", &n) != EOF) {
    p[++i] = n;
    printf("%llu\n", p[i++]);
  }

  putchar('\n');
  fclose(fp);
  return(0);
}

