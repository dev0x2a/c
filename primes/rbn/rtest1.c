#include <stdio.h>
#include "rbn.c"

void draw(rni *a, FILE *o)
{
  int x;
  fprintf(o, "%d, %d, ", a->u,a->s);
  for (x=a->u-1; x>=0; --x) {
    //fprintf(o, "%01611x ", a->dp[x]);
    //fprintf(o, "%081x ", a->dp[x]);
    fprintf(o, "%c", a->dp[x]);
  }
  fprintf(o, "\n");
}


int main(void)
{
  rni p, q, n;
  init(&p);
  init(&q);
  init(&n);
  
  rn_read_radix(&p, "1", 10);
  //rn_read_radix(&q, "12345", 10);
  //rn_add(&p, &q, &n);
  rn_printf(&p, 10, stdout);
//  draw(&n, stdout);
  return 0;
}

