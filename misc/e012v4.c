
#include <stdio.h>
#include <time.h>
#include <math.h>

int getDivisorCount(int);

int main(void) {
  clock_t start;
  clock_t end;
  double cpu_time_used;

  int i;
  int n;

  start = clock();

  i = 0;
  n = 0;

  do {
    i++;
    n += i;
  } while(getDivisorCount(n) <= 500);

  printf("%d\n", n);

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("CPU Time Used: %lf\n", cpu_time_used);
  return 0;
}

int getDivisorCount(int n) {
  int i = 1;
  int limit = floor(sqrt(n));
  int divisors = 0;

  for(i = 1; i <= limit; i++) {
    if(n%i == 0) divisors += 2;
  }

  if(limit * limit == n) divisors--;

  return divisors;
}
