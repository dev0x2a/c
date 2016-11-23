#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
enum {A=1, B, C, D, E, F, G, H};
enum {DEAD=0, ALIVE};
enum {WH=1, BL};

typedef struct position {
  int dx, dy;
} pos_t;

typedef struct piece {  
  int status;
  int who, type;
  pos_t loc;
} *psc_t;

typedef struct display {
  char board[8][8];
  int status, turn;
} disp_t;

typedef struct user {
  int who, status;
  int color, turn;
} usr_t;

void initboard(disp_t *p);
psc_t initpiece(int type, int stat, int who, int x, int y);
void printinfo(psc_t piece);
void pboard(disp_t *p);
void freepiece(...);

void initboard(disp_t *p)
{
  int i, j;
  for (i=0; i<8; ++i) {
    for (j=0; j<8; ++j) {
      p->board[i][j] = str[i][j];
    }
  }
}

psc_t initpiece(int type, int stat, int who, int x, int y)
{ 
  psc_t piece = malloc(sizeof(psc_t));
  if (!piece) {
    fprintf(stderr, "%s: piece allocation failure\n", PGRM);
    exit(1);
  }
  piece->loc.dx = x;
  piece->loc.dy = y;
  piece->type = type;
  piece->status = stat;
  piece->who = who;
  return piece;
}

void freepiece(...)
{
  va_list va;
  va_start(va);
  free(va);
  va_end(va);
}

void printinfo(psc_t piece)
{
  printf("\nx:    %d\n", piece->loc.dx);
  printf("y:    %d\n", piece->loc.dy);
  printf("type: %d\n", piece->type);
  printf("stat: %s\n", piece->status ? "alive" : "dead");
  printf("who:  p%d, %s\n", piece->who,piece->who?"white":"black");
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
  //disp_t disp;
  //initboard(&disp);
  //pboard(&disp);

  psc_t rw1, rw2;
#if 0
  psc_t kw1, kw2;
  psc_t bw1, bw2;
  psc_t quw, kiw;
  psc_t pw1, pw2, pw3, pw4, pw5, pw6, pw7, pw8;
  psc_t rb1, rb2;
  psc_t kb1, kb2;
  psc_t bb1, bb2;
  psc_t qub, kib;
  psc_t pb1, pb2, pb3, pb4, pb5, pb6, pb7, pb8;
#endif
  rw1 = initpiece(ROOK, 1, WH, H, 1);
  rw2 = initpiece(ROOK, 1, WH, A, 1);
#if 0
  kw1 = initpiece(KNIGHT, 1, WH, G, 1);
  kw2 = initpiece(KNIGHT, 1, WH, B, 1);
  bw1 = initpiece(BISHOP, 1, WH, H, 1);
  bw2 = initpiece(BISHOP, 1, WH, H, 1);
  quw = initpiece(QUEEN, 1, WH, H, 1);
  kiw = initpiece(KING, 1, WH, H, 1);

  rb1 = initpiece(1, 1, BL, H, 1);
  rb2 = initpiece(1, 1, BL, H, 1);
#endif
  printinfo(rw1);
  printinfo(rw2);

  //freepiece(rw1, rw2);

  //free(rw1);
  //free(rw2);
  exit(0);
}

