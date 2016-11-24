#ifndef TTT_H
#define TTT_H

#include "typedef.h"

char initb[3][3] = {
  {'.','.','.'},
  {'.','.','.'},
  {'.','.','.'}
};

enum { X=0, O };
enum { OFF=0, ON };

struct user {
  u8 stat:1;
  u8 turn:1;
  u8 who:1;
};
typedef struct user *usr_t;

struct nodetype {
  char board[3][3];
  char turn:1;
  struct nodetype *son, *next;
};
typedef struct nodetype *NODEPTR;

void pboard(char board[3][3]);
void expand(NODEPTR p, int plevel, int depth);
void nextmove(char board[][3], char nboard[][3], int looklvl, char player);
void bestbranch(NODEPTR pnd, NODEPTR *pbest, int *pvalue, char player);
NODEPTR buildtree(char board[][3], int looklvl);
NODEPTR evaluate(NODEPTR p, char player);
NODEPTR generate(NODEPTR p);

void pboard(char board[3][3])
{
  short i, j;
  for (i=0; i<3; ++i) {
    for (j=0; j<3; ++j) {
      printf("%c ", board[i][j]);
    }
    printf("%d\n", i+1);
  }
  puts("a b c\n");
}
#if 1
void nextmove(
    char board[][3], char nboard[][3], int looklvl, char player)
{
  NODEPTR ptree, best;
  int i, j, val;
  ptree = buildtree(board, looklvl);
  bestbranch(ptree, player, &best, &val);
  for (i=0; i<3; ++i)
    for (j=0; j<3; ++j)
      nboard[i][j] = best->board[i][j];
}

NODEPTR buildtree(char board[][3], int looklvl)
{
  NODEPTR ptree;
  short i, j;

  /* create root of tree and init */
  ptree = getnode();
  for (i=0; i<3 ++i)
    for (j=0; j<3; ++j)
      ptree->board[i][j] = board[i][j];
  /* root is a (+)node */
  ptree->turn = 1;
  ptree->son = NULL;
  ptree->next = NULL;
  /* create rest of game tree */
  expand(ptree, 0, looklvl);
  return(ptree);
}

void expand(NODEPTR p, int plevel, int depth)
{
  NODEPTR q;
  if (plevel < depth) {
    /* p is not at max level */
    q = generate(p->board);
    p->son = q;
    while (q != NULL) {
      /* traverse node list */
      if (p->turn == 1)
        q->turn = -1;
      else
        q->turn = 1;
      q->son = NULL;
      expand(1, plevel+1, depth);
      q = q->next;
    }
  }
}

void bestbranch(NODEPTR pnd, NODEPTR *pbest, int *pvalue, char player)
{
  NODEPTR p, pbest2;
  int val;

  if (pnd->son == NULL) {
    /* pnd is a leaf */
    *pvalue = evaluate(pnd->board, player);
    *pbest = pnd;
  } else {
    /* node is not a leaf; traverse son list */
    p = pnd->son;
    bestbranch(p, player, pbest, pvalue);
    *pbest = p;
    if (pnd->turn == -1)
      *pvalue = -*pvalue;
    p = p->next;
    while (p != NULL) {
      bestbranch(p, player, &pbest2, &val);
      if (pnd->turn == -1)
        val = -val;
      if (val > *pvalue) {
        *pvalue = val;
        *pbest = p;
      }
      p = p->next;
    }
    if (pnd->turn == -1)
      *pvalue = -*pvalue;
  }
}

#endif

#endif /* TTT_H */
