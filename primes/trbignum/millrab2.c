#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

size_t power(size_t, size_t, size_t);
bool witness(size_t, size_t, size_t, size_t);
bool isprime_mr(size_t);

int main(int argc, char *argv[])
{
  size_t n = atoi(argv[1]);
  bool p = isprime_mr(n);
  printf("%d %s prime\n", n, p ? "probably" : "not");
  return 0;
}

/* a^n%mod */
size_t power(size_t a, size_t n, size_t mod)
{
  size_t power = a;
  size_t result = 1;

  while (n) {
    if (n & 1)
      result = (result*power)%mod;
    power = (power*power)%mod;
    n >>= 1;
  }
  return result;
}

/* n-1 = 2^s * d
 * d is odd
 * factor powers or 2 from n-1 */
bool witness(size_t n, size_t s, size_t d, size_t a)
{
  size_t x = power(a, d, n);
  size_t y;

  while (s) {
    y = (x*x)%n;
    if (y==1 && x!=1 && x!=n-1)
      return false;
    x = y;
    --s;
  }
  if (y != 1)
    return false;
  return true;
}

/*
 * n < 1,373,653           a=2,3
 * n < 9,080,191           a=31,73
 * n < 4,759,123,141       a=2,7,61
 * n < 1,122,004,669,633   a=2,13,23,1662803
 * n < 2,152,302,898,747   a=2,3,5,7,11
 * n < 3,474,749,660,383   a=2,3,5,7,11,13
 * n < 341,550,071,728,321 a=2,3,5,7,11,13,17
 */
bool isprime_mr(size_t n)
{
  if (((!(n & 1)) && n!=2) || (n<2) || (n%3==0 && n!=3))
    return false;
  if (n <= 3)
    return true;

  size_t d = n/2;
  size_t s = 1;
  while (!(d & 1)) {
    d /= 2;
    ++s;
  }

  if (n < 1373653)
    return witness(n, s, d, 2) && witness(n, s, d, 3);
  if (n < 9080191)
    return witness(n, s, d, 31) && witness(n, s, d, 73);
  if (n < 4759123141)
    return witness(n, s, d, 2) && witness(n, s, d, 7) &&
      witness(n, s, d, 61);
  if (n < 1122004669633)
    return witness(n, s, d, 2) && witness(n, s, d, 13) &&
      witness(n, s, d, 23) && witness(n, s, d, 1662803);
  if (n < 2152302898747)
    return witness(n, s, d, 2) && witness(n, s, d, 3) &&
      witness(n, s, d, 5) && witness(n, s, d, 7) && witness(n, s, d, 11);
  if (n < 3474749660383)
    return witness(n, s, d, 2) && witness(n, s, d, 3) &&
      witness(n, s, d, 5) && witness(n, s, d, 7) &&
      witness(n, s, d, 11) && witness(n, s, d, 13);
  return witness(n, s, d, 2) && witness(n, s, d, 3) &&
      witness(n, s, d, 5) && witness(n, s, d, 7) &&
      witness(n, s, d, 11) && witness(n, s, d, 13) &&
      witness(n, s, d, 17);
}

