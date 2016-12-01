#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define max(a,b) ((a) > (b) ? (a) : (b))
#define OUT '.'
typedef uint32_t bitsieve;

unsigned sieve_check(bitsieve *b, const unsigned v)
{
  if ((v!=2 && !(v & 1)) || (v<2))
    return 0;
  else
    return !(b[v >> 6] & (1 << (v >> 1 & 31)));
}

bitsieve *sieve(const unsigned v)
{
  unsigned i, j;
  bitsieve *b = calloc((v >> 6)+1, sizeof(uint32_t));

  for (i=3; i<=sqrt(v); i+=2)
    if (!(b[i >> 6] & (1 << (i >> 1 & 31))))
      for (j=i*i; j<v; j+=(i << 1))
        b[j >> 6] |= (1 << (j >> 1 & 31));

  return b;
}

int ulam_get_map(int x, int y, int n)
{
  x -= (n-1)/2;
  y -= n/2;

  int mx = abs(x), my = abs(y);
  int l = 2*max(mx,my);
  int d = y > x ? l*3+x+y : l-x-y;

  return pow(l - 1, 2) + d;
}

/* Passing a value of 0 as glyph will print numbers */
void output_ulam_spiral(int n, const char glyph)
{
  /* An even side length does not make sense, use greatest odd value < n */
  n -= n%2 == 0 ? 1 : 0;

  const char *spaces = "                 ";
  //const char *spaces = ".................";
  int mwidth = log10(n*n)+1;

  bitsieve *b = sieve(n*n+1);
  int x, y;

  for (x=0; x<n; ++x) {
    for (y=0; y<n; ++y) {
      int z = ulam_get_map(y, x, n);

      if (glyph == 0) {
        if (sieve_check(b, z))
          printf("%*d ", mwidth, z);
        else
          printf("%.*s ", mwidth, spaces);
      } else {
        printf("%c", sieve_check(b, z) ? glyph : spaces[0]);
      }
    }
    putchar('\n');
  }
  free(b);
}

int main(int argc, char *argv[])
{
  const int n = argc < 2 ? 9 : atoi(argv[1]);

  //output_ulam_spiral(n, 0);
  //putchar('\n');

  output_ulam_spiral(n, OUT);
  putchar('\n');

  return 0;
}

