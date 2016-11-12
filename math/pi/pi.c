#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* for long ling integer values */
/* #define HAS_LONG_LONG */

#ifdef HAS_LONG_LONG
#define mul_mod(a,b,m) (( (long long) (a) * (long long) (b) ) % (m))
#else
#define mul_mod(a,b,m) fmod( (double) a * (double) b, m)
#endif

/* return the inverse of x(mod y) */
int inv_mod(int x, int y)
{
  int q, u, v, a, c, t;

  u = x;
  v = y;
  c = 1;
  a = 0;
  do {
    q = v/u;
    
    t = c;
    c = a-q*c;
    a = t;

    t = u;
    u = v-q*u;
    v = t;
  } while (u != 0);
  a %= y;
  if (a < 0)
    a += y;
  return(a);
}

/* return (a^b)(mod m) */
int pow_mod(int a, int b, int m)
{
  int r, aa;

  r = 1;
  aa = a;
  while (1) {
    if (b & 1)
      r = mul_mod(r, aa, m);
    b >>= 1;
    if (b == 0)
      break;
    aa = mul_mod(aa, aa, m);
  }
  return(r);
}

/* return true if n (prime) */
int isprime(int n)
{
  int r, i;
  if ((n%2) == 0)
    return(0);
  r = (int)(sqrt(n));
  for (i=3; i<=r; i+=2)
    if ((n%i) == 0)
      return(0);
  return(1);
}

/* return the prime immediately after n */
int nprime(int n)
{
  do {
    n++;
  } while(!isprime(n));
  return(n);
}

int main(int argc, char *argv[])
{
  int av, a, vmax, N, n, num, den, k, kq, kq2, t, v, s, i;
  double sum;

  if (argc<2 || (n=atoi(argv[1]))<=0) {
    fprintf(stderr, "%s <n> for the n-th digit of pi\n", argv[0]);
    exit(1);
  }

  N = (int) ((n+20)*log(10)/log(2));
  sum = 0;

  for (a=3; a<=(2*N); a=nprime(a)) {
    
    vmax = (int) (log(2*N)/log(a));
    av = 1;
    for (i=0; i<vmax; ++i)
      av *= a;

    s=v=0;
    num=den=kq=kq2=1;

    for (k=1; k<=N; ++k) {
      t = k;
      if (kq >= a) {
        do {
          t /= a;
          v--;
        } while ((t%a) == 0);
        kq = 0;
      }
      kq++;
      num = mul_mod(num, t, av);

      t = (2*k-1);
      if (kq2 >= a) {
        if (kq2 == a) {
          do {
            t /= a;
            v++;
          } while ((t%a) == 0);
        }
        kq2 -= a;
      }
      den = mul_mod(den, t, av);
      kq2 += 2;

      if (v > 0) {
        t = inv_mod(den, av);
        t = mul_mod(t, num, av);
        t = mul_mod(t, k, av);
        for (i=v; i<vmax; ++i)
          t = mul_mod(t, a, av);
        s += t;
        if (s >= av)
          s -= av;
      }
    }
    t = pow_mod(10, n-1, av);
    s = mul_mod(s, t, av);
    sum = fmod(sum+(double)s/(double)av, 1.0);
  }
  printf("decimal digits of pi at %d = %09d\n",
      n,(int)(sum*1e9));
  return(0);
}

