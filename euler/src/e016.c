#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>


unsigned int opt[] =
{
  1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,
};

int
main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("%s <base> <exp>\n", argv[0]);
    return(-1);
  }
  int b, n;
  clock_t start, end;
  double cpu_usage;
  mpz_t ret;

  start = clock();
  b = atoi(argv[1]);
  n = atoi(argv[2]);

  mpz_init(ret);
  mpz_ui_pow_ui(ret, b, n);
  printf("%d^%d = ", b, n);
  mpz_out_str(NULL, 10, ret);
  printf("\n");
  mpz_clear(ret);

  end = clock();
  cpu_usage = ((double)(end-start))/CLOCKS_PER_SEC;
  printf("cpu time: %1f\n", cpu_usage);
  return 0;
}

