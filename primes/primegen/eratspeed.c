#include <stdio.h>
#include <stdlib.h>
#include "eratspeed.h"

timing start, finish;
timing_basic startb, finishb;

void init(uint32 L)
{ 
  int i, d, j;
  uint32 q, qz;
  
  for (i=0; i<8; ++i) {
    d = dtab[i];
    for (j=0; j<3509; ++j) {
      q = qtab[j];
      qz = q*q;
      while (qz%30 != d)
        qz += q+q;
      next[i][j] = (qz-d)/30-L;
    }
  }
}

void doit(void)
{ 
  int i, j;
  uint32 *nexti;
  register uint32 k, q, pos, *buf, bits, data;
  for (i=0; i<8; ++i) {
    buf = a[i];
    nexti = next[i];
    for (k=0; k<B32_E; ++k)
      buf[k] = 0;
    for (j=0; j<3509; ++j) {
      k = nexti[j];
      if (k < B_E) {
        q = qtab[j];
        do {
          pos = k;
          data = k;
          pos >>= 5;
          data &= 31;
          bits = buf[pos];
          data = E_two[data];
          k += q;
          bits |= data;
          buf[pos] = bits;
        } while (k < B_E);
      }
      nexti[j] = k-B_E;
    }
  }
}

uint32 total;
void countit(void)
{
  int i;
  register int pos;
  register uint32 *ai, bits, result=0;
/*To print the primes (slowly), given L:
  for(k=0; k<B; ++k)
    for(i=0; i<8; ++i)
      if(!(a[i][k/32]&two[k&31]))
	printf("%d\n",30*(L+k)+dtab[i]);*/
  for (i=0; i<8; ++i) {
    ai = a[i];
    for (pos=0; pos<B32_E; ++pos) {
      bits = ~ai[pos];
      result += E_pop[bits&255]; bits >>= 8;
      result += E_pop[bits&255]; bits >>= 8;
      result += E_pop[bits&255]; bits >>= 8;
      result += E_pop[bits];
    }
  }
  total += result;
}

timing t, told;
int main(void)
{ 
  int L = 1;
  timing_basic_now(&startb);
  timing_now(&start);
  timing_now(&told);
  
  total = 10; /* 2,3,5,7,11,13,17,19,23,29 */
  init(L);

  timing_now(&t);
  printf("Init: %f\n", timing_diff(&t, &told));
  told = t;
  
  do {
    doit();
    countit();
    timing_now(&t);
    printf("Finished L=%d: %f\n", L,timing_diff(&t, &told));
    told = t;
    L += B_E;
  } while (L < 33333334);

  timing_basic_now(&finishb);
  timing_now(&finish);
  printf("%d primes up to %d.\n", total,30*L);

  printf("Timings are in ticks. Nanoseconds per tick: approximately %f\n",
      timing_basic_diff(&finishb,&startb)/timing_diff(&finish, &start));
  printf("Overall seconds: approximately %f\n",
      0.000000001*timing_basic_diff(&finishb, &startb));
  puts("Tick counts may be underestimates on systems"
      " without hardware tick support");
  exit(0);
}

