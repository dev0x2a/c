#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpfr.h>

#define BASE 65536
#define UINT unsigned

struct {
  int sign; // 1 if negative
  int size;
  UINT *tab;
} bignum;

int main(int argc, char *argv[])
{
  /*
  double a = sin(1e22), b = log(17.1);
  double c = exp(0.42);
  double d = 173746*a + 94228*b - 78487*c;
  printf("d = %.16e\n", d);
  return 0;
  *//*
  mp_prec_t p = atoi(argv[1]);
  mpfr_t a, b, c, d;
  mpfr_inits2(p, a, b, c, d, (mpfr_ptr) 0);
  mpfr_set_str(a, "1e22", 10, GMP_RNDN);
  mpfr_sin(a, a, GMP_RNDN);
  mpfr_mul_ui(a, a, 173746, GMP_RNDN);
  mpfr_set_str(b, "17.1", 10, GMP_RNDN);
  mpfr_log(b, b, GMP_RNDN);
  mpfr_mul_ui(b, b, 94228, GMP_RNDN);
  mpfr_set_str(c, "0.42", 10, GMP_RNDN);
  mpfr_exp(c, c, GMP_RNDN);
  mpfr_mul_si(c, c, -78487, GMP_RNDN);
  mpfr_add(d, a, b, GMP_RNDN);
  mpfr_add(d, d, c, GMP_RNDN);
  mpfr_printf("d = %1.16Re\n", d);
  mpfr_clears(a, b, c, d, NULL);
  return 0;*//*
  double x = 2.522464e-1;
  printf("sin(x) = %.16e\n", sin(x));
  return 0;*/
  _Decimal64 a = sin(1e22);
  _Decimal64 b = log(17.1);
  _Decimal64 c = exp(0.42);
  _Decimal64 d = 173746*a+94228*b-78487*c;
  printf("d = %.16e\n", (double)d);
  return 0;
}


#if 0
{
  int t,n,i,j,tmp,m,x;
  UINT a[200];

  t = 1;
  while (t--) {
    n = atoi(argv[1]);
    a[0] = 1; //array init 1
    m = 1;    //dgt counter

    tmp = 0; //carry
    for (i=1; i<=n; ++i) {
      for (j=0; j<m; ++j) {
        x = a[j]*i+tmp; //x contains dgt by dgt product
        a[j] = x%BASE; //dgt in pos j
        tmp = x/BASE;  //carry value that will be stored on later indices
        }
      while (tmp > 0) { //store carry in arr
        a[m] = tmp%BASE;
        tmp /= BASE;
        m++; //dgt counter
      }
    }
    for (i=m-1; i>=0; --i) {//print
      printf("%d", a[i]);
    }
    putchar('\n');
  }
  return 0;
}
#endif

