#include <stdio.h>
#include <stdlib.h>

#define PGRM "chess.c"

#define BOARD {{'R','N','B','K','Q','B','N','R'},\
  {'+','+','+','+','+','+','+','+'},\
  {'.','.','.','.','.','.','.','.'},\
  {'.','.','.','.','.','.','.','.'},\
  {'.','.','.','.','.','.','.','.'},\
  {'.','.','.','.','.','.','.','.'},\
  {'*','*','*','*','*','*','*','*'},\
  {'r','n','b','k','q','b','n','r'}};

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
      p->board[i][j] = '.';
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
#if 0
void allocboard(disp_t *p)
{
  p->board = (char **) malloc(64*sizeof(char));
  if (!(p->board)) {
    fprintf(stderr, "%s: could not allocate memory for board\n", PGRM);
    exit(1);
  }
}

void freeboard(disp_t *p)
{
  free(p->board);
}
#endif

int main(void)
{
  disp_t disp;


  init(&disp);
  
  pboard(&disp);
  
  
  exit(0);
}

