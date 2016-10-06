#include <stdio.h>
#include "mprimes.h"

/*  function is_prime defined in primes.h
 *  return 0 if not prime, 1 if prime
 */

int main(int argc, char *argv[])
{
  long int num;
  int result;

  if (argc != 2) {
    printf("%s <num> to check if prime\n", argv[0]);
    return(-1);
  }
  num = atol(argv[1]);

  if (num == 0) {
    printf("%ld not prime\n", num);
    return 0;
  }

  result = is_prime(num);

  if (result == 0)
    printf("%ld not prime\n", num);
  else if (result == 1)
    printf("%ld is prime\n", num);

  return 0;
}

