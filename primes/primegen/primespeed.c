#include <stdio.h>
#include <stdlib.h>
#include "plib.h"
#include "timing.h"

static const unsigned long __pop[256] = {
  0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

timing told;
timing t;

uint64 timedcount(primegen *pg, uint64 to)
{ 
  int pos, j;
  register uint32 *bufj, bits, smallcount;
  uint32 (*buf)[B32] = pg->buf;
  uint64 count = 0;

  timing_now(&told);

  for (;;) {
    while (pg->num) {
      if(pg->p[pg->num-1] >= to)
        return(count);
      ++count;
      --pg->num;
    }

    smallcount = 0;
    pos = pg->pos;
    while ((pos<B32)&&(pg->base+1920 < to)) {
      for (j=0; j<16; ++j) {
        bits=~buf[j][pos];
        smallcount += __pop[bits&255]; bits >>= 8;
        smallcount += __pop[bits&255]; bits >>= 8;
        smallcount += __pop[bits&255]; bits >>= 8;
        smallcount += __pop[bits];
      }
      pg->base += 1920;
      ++pos;
    }

    pg->pos=pos;
    count += smallcount;
    if(pos == B32)
      while(pg->base+B*60 < to) {
        primegen_sieve(pg);
        timing_now(&t);
        printf("Finished L=%d: %f\n", (int)pg->L,timing_diff(&t,&told));
        told = t;
        pg->L += B;
        smallcount = 0;
        for (j=0; j<16; ++j) {
          bufj = buf[j];
          for (pos=0; pos<B32; ++pos) {
            bits = ~bufj[pos];
            smallcount += __pop[bits&255]; bits >>= 8;
            smallcount += __pop[bits&255]; bits >>= 8;
            smallcount += __pop[bits&255]; bits >>= 8;
            smallcount += __pop[bits];
          }
        }
        count += smallcount;
        pg->base += B*60;
      }
    primegen_fill(pg);
  }
}

char strnum[40];
primegen pg;
timing start;
timing finish;
timing_basic startb;
timing_basic finishb;

int main(int argc, char *argv[])
{ 
  /*int loop;*/
  uint64 result, high = 1000000000;

  if (argv[1])
    scan_uint64(argv[1], &high);

  timing_basic_now(&startb);
  timing_now(&start);
  
  primegen_init(&pg);
  
  result = timedcount(&pg, high);
  
  timing_basic_now(&finishb);
  timing_now(&finish);
  
  strnum[fmt_uint64(strnum,result)] = 0;
  printf("%s primes up to ",strnum);
  
  strnum[fmt_uint64(strnum,high)] = 0;
  
  printf("%s.\n", strnum);
  printf("Timings are in ticks. Nanoseconds per tick: approximately %f.\n",
      timing_basic_diff(&finishb, &startb)/timing_diff(&finish, &start));
  printf("Overall seconds: approximately %f.\n",
      0.000000001*timing_basic_diff(&finishb, &startb));
  puts("Tick counts may be underestimates on systems\
 without hardware tick support.");
  exit(0);
}

