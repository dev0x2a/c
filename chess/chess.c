#include <stdio.h>
#include <stdlib.h>

#define PGRM "chess.c"
#define DEAD 0
#define ALIVE 1
#define WHITE 1
#define BLACK 2

const char str[8][8] = {
/*8*/  {'R','N','B','K','Q','B','N','R'},
/*7*/  {'+','+','+','+','+','+','+','+'},
/*6*/  {'.','.','.','.','.','.','.','.'},
/*5*/  {'.','.','.','.','.','.','.','.'},
/*4*/  {'.','.','.','.','.','.','.','.'},
/*3*/  {'.','.','.','.','.','.','.','.'},
/*2*/  {'*','*','*','*','*','*','*','*'},
/*1*/  {'r','n','b','k','q','b','n','r'},
      /* a   b   c   d   e   f   g   h */
};

typedef struct piece {
  int x, y;
  int status;
  int who, type;
} psc_t;

typedef struct display {
  char board[8][8];
  int status, turn;
} disp_t;

typedef struct user {
  int who, status;
  int color, turn;
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

void initpieces(void)
{
  psc_t rook1_p1, rook2_p1;
  psc_t knt1_p1, knt2_p1;
  psc_t bisp1_p1, bisp2_p1;
  psc_t queen_p1, king_p1;
  psc_t p11, p12, p13, p14, p15, p16, p17, p18;

  psc_t rook1_p2, rook2_p2;
  psc_t knt1_p2, knt2_p2;
  psc_t bisp1_p2, bisp2_p2;
  psc_t queen_p2, king_p2;
  psc_t p21, p22, p23, p24, p25, p26, p27, p28;


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
  initpieces();
  
  pboard(&disp);
  
  
  exit(0);
}

