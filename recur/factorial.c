#include <stdio.h>
#include <stdlib.h>

int factorial (int n)
/* recursive version */
{
  if (n == 1) return 1;
  else
  return n*factorial(n-1);
}

int factiter (int n)
/* iterative version using for loop */
{
  int ans = 1, i;
  for (i=n; i>0; --i)
    ans *= i;
  return(ans);
}

int main (int argc, char **argv)
{
  int n;

  if (argc < 2)
    n = 4;
  else
    n = atoi(argv[1]);

  printf("factorial %d (recursive) is: %d\n", n,factorial(n));
  printf("factorial %d (iterative) is: %d\n", n,factiter(n));
  return 0;
}
