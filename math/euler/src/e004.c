#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/*  largest palendromic num from the product of 2 3-digit nums */

int main(void)
{
  int i, m;
  bool found = false;
  for (i=998; i>=100; --i) {
    char c[7];
    sprintf(c, "%d", i);
    c[3] = c[2];
    c[4] = c[1];
    c[5] = c[0];
    int n = atoi(c);
    int lim = sqrt((float)n);
    for (m=999; m>=lim; --m) {
      if( n%m == 0) {
        printf("%d\n", n);
        found = true;
        break;
      }
    }
    if (found)
      break;
  }
  return(0);
}

