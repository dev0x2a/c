#include <stdio.h>

int main(int argc, char *argv[])
{
  int i,k;
  unsigned long long n;
  char c;
  FILE *fp,*fc;

  if (argc < 2) {
    fprintf(stderr, "%s [FILE]\n", argv[0]);
    return(-1);
  }
  fp = fopen(argv[1], "r");
  fc = fopen(argv[1], "r");

  if (!fp) {
    fprintf(stderr, "%s: %s cannot be opened\n", argv[0],fp);
    return(-1);
  }

  k = 1;
  while (fscanf(fc, "%c", &c) != EOF) {
    if (c == ',')
      k+=2;
  }
  fclose(fc);
  printf("\ninit p[%d]\n\n", k);

  unsigned long long p[k];
  i = 0;
  while (fscanf(fp, "%llu,", &n) > 0) {
    p[++i] = n;
    printf("%llu\n", p[i++]);
  }

  fclose(fp);
  return(0);
}

