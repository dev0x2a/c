/*
 * bitsort.c: bitmap sort, distinct ints in range [0..n-1]
 * (c)1999 Lucent Tech
 */

#include <stdio.h>

#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1f
#define N 10000000

int a[1+N/BITSPERWORD];

void set(int i) {       a[i>>SHIFT] |=  (1<<(i & MASK)); }
void clr(int i) {       a[i>>SHIFT] &= ~(1<<(i & MASK)); }
int test(int i) {return a[i>>SHIFT] &   (1<<(i & MASK)); }

int main(void)
{
  int i;
  
  for (i=0; i<N; ++i)
    clr(i);
  /* replace above 2 lines w/ below 3 for word-parallel init
   *  
   * int top = 1+N/BITSPERWORD;
   * for (i=0; i<top; ++i)
   *   a[i] = 0;
   */

  while (scanf("%d", &i) != EOF)
    set(i);
  for (i=0; i<N; ++i)
    if (test(i))
      printf("%d\n", i);
  return 0;
}

