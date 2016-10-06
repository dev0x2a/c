#include <stdio.h>

int
main(int argc, char *argv[])
{
  unsigned int divisors = 0;
  unsigned long long int i = 1, r, triangle = 0;

  while (divisors < 250) {
    divisors = 0;
    triangle = triangle + i;
    printf ("TRIANGLE: %i; ", triangle);

    for (r=1; r<=sqrt(triangle); ++r) 
      if (triangle%r == 0) 
        ++divisors;
      printf ("%i\n", divisors);
      ++i;
  }
  return 0;
}
