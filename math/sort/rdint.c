#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int rdint(void)
{
  int i, neg, d;
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
    i = 10*i+d;
  }
  ungetc(ch, stdin);
  return neg ? -i : i;
}

int main(void)
{
  printf("%d\n", rdint());
  return 0;
}

