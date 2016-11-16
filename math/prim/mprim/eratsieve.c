#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long u64;

int eratsieve(const u64);

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "%s: <n> to sieve primes in range [1..n-1]\n", argv[0]);
    exit(-1);
  }
  
  const int n = atoi(argv[1]);

  eratsieve(n);
  putchar('\n');
  exit(0);
}

int eratsieve(const u64 set)
{
  u64 i, j;
  int k = 1;
  int *table = malloc(set*sizeof(int));
  
  if (!table) {
    fprintf(stderr, "could not allocate memory for sieve table\n");
    exit(1);
  }

  for (i=2; i<set; ++i)
    table[i] = 1;

  for (i=2; i<set; ++i)
    if (table[i])
      for (j=i; i*j<set; ++j)
        table[i*j] = 0;

  for (i=2; i<set; ++i)
    if (table[i])
      printf("p #%d\t= %d\n", k++,i);
  free(table);
  return(0);
}

