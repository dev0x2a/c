#include <stdio.h>

void J(char *a)
{
  int f, i=0, c='1';
  for (; a[i]!='0'; ++i)
    if (i == 81) {
      puts(a);
      return;
    }
  for (; c<='9'; ++c) {
    for (f=0; f<9; ++f)
      if (a[i-i%27+i%9/3*3+f/3*9+f%3]==c ||
          a[i%9+f*9]==c || a[i-i%9+f]==c)
        goto e;
    a[i]=c;
    J(a);
    a[i]='0';
e:;
  }
}

int main(int c, char **v)
{
  int t=0;
  if (c > 1) {
    for (; v[1][t]; ++t);
    if (t == 81) {
      J(v[1]);
      return 0;
    }
  }
  puts("sudoku [0-9]{81}");
  return 1;
}

