#include <stdio.h>
#include "primes.h"

/*  function is_prime defined in primes.h
 *  return 0 if not prime, 1 if prime
 */

int main(int argc, char **argv)
{
  long int num;
  int result;

  num = atol(argv[1]);
  result = is_prime(num);

  if (result == 0)
    printf("%ld not prime\n", num);
  else if (result == 1)
    printf("%ld is prime\n", num);

  return 0;
}

