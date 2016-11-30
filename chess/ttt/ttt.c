#include <stdio.h>
#include <stdlib.h>

#include "ttt.h"
#include "iottt.c"

int main(void)
{
  int n=0, c=0;
  char board[3][3] = {
    {'.','.','.'},
    {'.','.','.'},
    {'.','.','.'}
  };

  puts("x(0) or o(1)?");
  scanf("%d", &n);
  usr_t p1 = malloc(sizeof(usr_t));
  usr_t p2 = malloc(sizeof(usr_t));

  if (!p1 || !p2) {
    emit(1, "could not allocate memory", __FILE__,__LINE__);
  }

  if (n == 0) {
    p1->who = X;
    p2->who = O;
  } else {
    p1->who = O;
    p2->who = X;
  }
  
  printf("\n%c goes first\n\n", p1->who ? 'o' : 'x');
  p1->turn = ON;
  p2->turn = OFF;
  pboard(board);
  
  const char *p = "point";
  const int gflags = 1;
  int len = 5;
  put_tty_line(p, len, gflags);
#if 0
  while (1) {
    prompt(c&1 ? p2->who:p1->who, board);
    ++c;
    pboard(board);
  }
#endif
  free(p1);
  free(p2);
  exit(0);
}

