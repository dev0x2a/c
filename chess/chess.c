#include <stdio.h>
#include <stdlib.h>

#define PGRM "chess.c"
#define DEAD 0
#define ALIVE 1
#define WHITE 1
#define BLACK 2

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

typedef struct piece {
  int x, y;
  int status;
  int who, type;
} psc_t;

typedef struct display {
  char board[8][8];
  int status;
} disp_t;

typedef struct user {
  int who, status;
  int color;
} usr_t;

void initboard(disp_t *p)
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


  initboard(&disp);
  
  pboard(&disp);
  
  
  exit(0);
}

