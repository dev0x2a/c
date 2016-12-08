#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int readint()
{
  int i, i0, neg, d, k;
  char ch;

  do ch = getchar(); while (isspace(ch));
  neg = ch == '-';
  if (neg || ch=='+')
    ch = getchar();
  if (!isdigit(ch)) {
    puts("Invalid number");
    exit(1);
  }
  i = ch-'0';
  while (ch=getchar(), isdigit(ch)) {
    d = ch-'0';
    i0 = i;
    for (k=0; k<5; ++k) {
      if (k == 2)
        i += i0;
      else if (k == 4)
        i += d;
      else
        i <<= 1;
      if (i < 0) {
        puts("Too large");
        exit(1);
      }
    }
  }
  ungetc(ch, stdin);
  return neg ? -i : i;
}

int main()
{
  //readint();
  printf("%d\n", readint());
  return 0;
}

