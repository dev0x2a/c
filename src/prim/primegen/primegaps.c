#include "plib.h"

primegen pg;

void main(void)
{
  uint32 diff, maxdiff;
  uint64 p, lastp;

  primegen_init(&pg);
  primegen_next(&pg);

  lastp = primegen_next(&pg);
  maxdiff = 0;

  for (;;) {
    p = primegen_next(&pg);
    diff = p-lastp;
    if (diff > maxdiff) {
      printf("%.0f %.0f %f\n" ,(double)p, (double)diff
          ,log((double)diff)/log(log((double)p)));
      maxdiff =d iff;
    }
    lastp = p;
  }
}

