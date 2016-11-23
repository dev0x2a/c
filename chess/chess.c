#include <stdio.h>
#include <stdlib.h>

#define PGRM "chess.c"

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

enum {PAWN=0, ROOK, KNIGHT, BISHOP, KING, QUEEN};
enum {DEAD=0, ALIVE};
enum {WHITE=1, BLACK};

typedef struct position {
  int dx, dy;
} pos_t;

typedef struct piece {  
  int status;
  int who, type;
  pos_t loc;
} psc_t;

typedef struct display {
  char board[8][8];
  int status, turn;
} disp_t;

typedef struct user {
  int who, status;
  int color, turn;
} usr_t;

void initboard(disp_t *p);
void initpieces(void);
void printinfo(psc_t *piece);
void pboard(disp_t *p);

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
  psc_t *rook_1w;
  //, rook_2w;
  //psc_t knt_1w, knt_2w;
  //psc_t bisp_1w, bisp_2w;
  //psc_t queen_w, king_w;
  //psc_t p1w, p2w, p3w, p4w, p5w, p6w, p7w, p8w;

  //psc_t rook_1b, rook_2b;
  //psc_t knt_1b, knt_2b;
  //psc_t bisp_1b, bisp_2b;
  //psc_t queen_b, king_b;
  //psc_t p1b, p2b, p3b, p4b, p5b, p6b, p7b, p8b;
  
  rook_1w = malloc(sizeof(psc_t));

  rook_1w->loc.dx = 0x8;
  rook_1w->loc.dy = 0x1;
  rook_1w->type = ROOK;
  rook_1w->status = ALIVE;
  rook_1w->who = WHITE;
  printinfo(rook_1w);

  free(rook_1w);
}

void printinfo(psc_t *piece)
{
  printf("\nx:   %d\n", piece->loc.dx);
  printf("y:   %d\n", piece->loc.dy);
  printf("type:%d\n", piece->type);
  printf("stat:%s\n", piece->status ? "alive" : "dead");
  printf("who: p%d, %s\n", piece->who,piece->who?"white":"black");
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
  initpieces();
  
  exit(0);
}

