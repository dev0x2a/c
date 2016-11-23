#ifndef CHESS_H
#define CHESS_H

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
enum {A=1, B, C, D, E, F, G, H};
enum {DEAD=0, ALIVE};
enum {WH=1, BL};

typedef struct position {
  char dx, dy;
} pos_t;

typedef struct piece {  
  short status, who, type;
  pos_t loc;
} *psc_t;

typedef struct display {
  char board[8][8];
  short status, turn;
} disp_t;

typedef struct user {
  char who, status, turn;
} *usr_t;

void initboard(disp_t *p);
void printinfo(psc_t piece);
void pboard(disp_t *p);
void printuser(usr_t user);
usr_t inituser(char who);
psc_t initpiece(char type, char stat, char who, int x, int y);

send(to, from, count)
register short *to, *from;
register count;
{
  register n = (count+7)/8;
  switch(count%8) {
    case 0: do { *to = *from++;
    case 7:      *to = *from++;     
    case 6:      *to = *from++;     
    case 5:      *to = *from++;     
    case 4:      *to = *from++;     
    case 3:      *to = *from++;     
    case 2:      *to = *from++;     
    case 1:      *to = *from++;     
            } while (--n > 0);
  }
}

void initboard(disp_t *p)
{
  int i, j;
  for (i=0; i<8; ++i) {
    for (j=0; j<8; ++j) {
      p->board[i][j] = str[i][j];
    }
  }
}

psc_t initpiece(char type, char stat, char who, int x, int y)
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

void printinfo(psc_t piece)
{
  char *type;
  switch(piece->type) {
    case 0:
      type = "pawn";
      break;
    case 1:
      type = "rook";
      break;
    case 2:
      type = "knight";
      break;
    case 3:
      type = "bishop";
      break;
    case 4:
      type = "king";
      break;
    case 5:
      type = "queen";
      break;
    default:
      break;
  }

  printf("\nx:    %d\n", piece->loc.dx);
  printf("y:    %d\n", piece->loc.dy);
  printf("type: %s\n", type);
  printf("stat: %s\n", piece->status ? "alive" : "dead");
  printf("who:  p%d, %s\n", piece->who,piece->who?"white":"black");
}

usr_t inituser(char who)
{
  usr_t user = malloc(sizeof(usr_t));
  if (!user) {
    fprintf(stderr, "%s: player allocation failure\n", PGRM);
    exit(1);
  }
  user->who = who;
  return user;
}

void printuser(usr_t user)
{
  char *who;
  if (user->who == 1)
    who = "white";
  else
    who = "black";

  printf("\nwho: p%d, %s\n", user->who,who);
  printf("turn: %s\n", user->turn ? "yes" : "no");
  printf("stat: %s\n", user->status ? "alive" : "dead");
}

void pboard(disp_t *p)
{
  char i, j;
  for (i=0; i<8; ++i) {
    for (j=0; j<8; ++j) {
      printf("%c ", p->board[i][j]);
    }
    putchar('\n');
  }
}
#endif /* CHESS_H */
