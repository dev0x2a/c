#ifndef CHESS_H
#define CHESS_H

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#define FREE(p,q) ((free(p)),(free(q)))

const char str[8][8] = {
/*8*/ {'R','N','B','K','Q','B','N','R'},
/*7*/ {'+','+','+','+','+','+','+','+'},
/*6*/ {'.','.','.','.','.','.','.','.'},
/*5*/ {'.','.','.','.','.','.','.','.'},
/*4*/ {'.','.','.','.','.','.','.','.'},
/*3*/ {'.','.','.','.','.','.','.','.'},
/*2*/ {'*','*','*','*','*','*','*','*'},
/*1*/ {'r','n','b','k','q','b','n','r'},
      /*a   b   c   d   e   f   g   h*/
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

typedef struct user {
  char who, status, turn;
} *usr_t;

typedef struct display {
  char board[8][8];
  short status, turn;
} disp_t;

void pboard(disp_t *p);
void initboard(disp_t *p);
void printuser(usr_t user);
void printinfo(psc_t piece);
void emit(short ret, u8 *msg, u8 *file, short line);
void send(register short *to, register short *from, register int count);

usr_t inituser(char who);
psc_t initpiece(char type, char stat, char who, int x, int y);

void emit(short ret, u8 *msg, u8 *file, short line)
{
  fprintf(stderr, "\nfile=%s, line=%d\nerror: %s\n", file,line,msg);
  exit(ret);
}

void send(register short *to, register short *from, register int count)
{
  register int n = (count+7)/8;
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
  for (int i=0; i<8; ++i)
    for (int j=0; j<8; ++j)
      p->board[i][j] = str[i][j];
}

psc_t initpiece(char type, char stat, char who, int x, int y)
{ 
  psc_t piece = malloc(sizeof(psc_t));
  if (!piece) {
    emit(EF, "piece struct allocation failure", FILENM,LINENO);
  }
  piece->loc.dx = x;
  piece->loc.dy = y;
  piece->type = type;
  piece->status = stat;
  piece->who = who;
  return(piece);
}

void printinfo(psc_t piece)
{
  char *type;
  switch(piece->type) {
    case 0: type="pawn";  break;
    case 1: type="rook";  break;
    case 2: type="knight";break;
    case 3: type="bishop";break;
    case 4: type="king";  break;
    case 5: type="queen"; break;
    default:break;
  }
  printf("\nx:    %d\n", piece->loc.dx);
  printf("y:    %d\n", piece->loc.dy);
  printf("type: %s\n", type);
  printf("stat: %s\n", piece->status ? "alive" : "dead");
  printf("who:  p%d, %s\n", piece->who,piece->who ? "white" : "black");
}

usr_t inituser(char who)
{
  usr_t user = malloc(sizeof(usr_t));
  if (!user) {
    emit(EF, "player struct allocation failure", FILENM,LINENO);
  }
  user->who = who;
  return(user);
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
  for (char i=0; i<8; ++i) {
    for (char j=0; j<8; ++j) {
      printf("%c ", p->board[i][j]);
    }
    putchar('\n');
  }
}
#endif /* CHESS_H */
