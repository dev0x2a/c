#include <stdio.h>
#include <stdlib.h>

#define PGRM "chess.c"

const char str[8][8] = {
  {'R','N','B','K','Q','B','N','R'},
  {'+','+','+','+','+','+','+','+'},
  {'.','.','.','.','.','.','.','.'},
  {'.','.','.','.','.','.','.','.'},
  {'.','.','.','.','.','.','.','.'},
  {'.','.','.','.','.','.','.','.'},
  {'*','*','*','*','*','*','*','*'},
  {'r','n','b','k','q','b','n','r'},
};

#if 0
typedef struct piece {
  int x, y;
  const int type;
} psc_t;
#endif

typedef struct display {
  char board[8][8];
  int status;
} disp_t;

void init(disp_t *p)
{
  int i, j;

  for (i=0; i<8; ++i) {
    for (j=0; j<8; ++j) {
      p->board[i][j] = str[i][j];
    }
  }
}

void pboard(disp_t *p)
{
  int i, j;

  for (i=0; i<8; ++i) {
    for (j=0; j<8; ++j) {
      printf("%c ", p->board[i][j]);
    }
    putchar('\n');
  }
}

int main(void)
{
  disp_t disp;


  init(&disp);
  
  pboard(&disp);
  
  
  exit(0);
}

