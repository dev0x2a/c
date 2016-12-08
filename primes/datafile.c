#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int i=0, k=1;
  unsigned long long n;
  FILE *fp;
  char c;

  if (argc < 2) {
    fprintf(stderr, "%s [FILE]\n", argv[0]);
    exit(1);
  }
  fp = fopen(argv[1], "r");

  if (!fp) {
    end:
    fprintf(stderr, "%s: %s cannot be opened\n", argv[0],fp);
    exit(0);
  }

  while (fscanf(fp, "%c", &c) != EOF) {
    if (c==',' || c=='$' || c=='\n')
      ++k;
  }
  fclose(fp);
  printf("\ninit p[%d]\n\n", k);
  unsigned long long p[k];

  fp = fopen(argv[1], "r");
  if (!fp)
    goto end;
  while (fscanf(fp, "%llu", &n) != EOF) {
    p[++i] = n;
    fprintf(stdout, "%llu\n", p[i++]);
  }
  putchar('\n');
  fclose(fp);
  exit(0);
}

