#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int x, y;
  int a, b, g, u, v, w, q;

  x = atoi(argv[1]);
  y = atoi(argv[2]);

  if ((x<y) || (y<0))
    exit(1);

  a = v = 1;
  b = u = 0;
  g = x;
  w = y;

  while (w > 0) {
    q = (int) (g/w);
    a = u;
    b = v;
    g = w;
    u = a-(q*u);
    v = b-(q*v);
    w = g-(q*w);
  }

  printf("%d %d %d\n", a,b,g);
  exit(0);
}
    
