#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

const int max = 10000000; /*  not actual max, just to keep system mem usage low */

int
main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("%s <base> <exp>\n", argv[0]);
    return(-1);
  }
  int b, n, s;
  clock_t start, end;
  double cpu_usage;
  char out[100000];
  mpz_t ret;

  start = clock();
  b = atoi(argv[1]);
  n = atoi(argv[2]);
  s = 0;
  if (n > max) {
    printf("%s limit\n", argv[0]);
    return(-1);
  }
  printf("%d^%d = ", b, n);

  mpz_init(ret);
  mpz_ui_pow_ui(ret, b, n);
  gmp_sprintf(out, "%Zd", ret); 
  mpz_clear(ret);
  for (int i=0; out[i]!='\0'; ++i) {
    printf("%d", out[i]-'0');
    s += out[i]-'0';
  }
  printf("\nsum = %d", s);

  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("\ncpu time: %1f\n", cpu_usage);
  return 0;
}

