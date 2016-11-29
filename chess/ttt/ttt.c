#include <stdio.h>
#include <stdlib.h>

#include "ttt.h"

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
    fprintf(stderr,
        "%s: line=%d: could not allocate memory\n", __FILE__,__LINE__);
    exit(1);
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

  while (1) {
    prompt(c&1 ? p2->who:p1->who, board);
    ++c;
    pboard(board);
  }
  free(p1);
  free(p2);
  exit(0);
}

