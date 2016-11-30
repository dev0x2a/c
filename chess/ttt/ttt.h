#ifndef TTT_H
#define TTT_H

#include "typedef.h"
#define DEBUG 0

enum { X=0, O };
enum { OFF=0, ON };

struct user {
  char stat:1, turn:1, who:1;
};
typedef struct user *usr_t;

struct nodetype {
  char turn:1;
  char board[3][3];
  struct nodetype *son, *next;
};
typedef struct nodetype *NODEPTR;

void pboard(char board[3][3]);
int evaluate(NODEPTR p, char player);
void expand(NODEPTR p, int plevel, int depth);
void nextmove(char board[][3], char nboard[][3], int looklvl, char player);
void emit(const int ret, const char *err, const char *file, const int line);
void bestbranch(NODEPTR pnd, NODEPTR *pbest, int *pvalue, char player);
NODEPTR buildtree(char board[][3], int looklvl);
NODEPTR generate(NODEPTR p);
NODEPTR getnode(void);

void emit(const int ret, const char *err, const char *file, const int line)
{
  fprintf(stderr, "%s: line=%d: %s\n", file,line,err);
  exit(ret);
}

void prompt(char who, char board[3][3])
{
  char c;
  int r, chk, flag=1, stat=0;
  while (flag) {
    printf("\n%c ? ", who?'o':'x');
    scanf("%c%d", &c,&r);
    switch (c) {
      case 'a': chk=0;
      case 'b': chk=1;
      case 'c': chk=2;
      default:break;
    }
    if (board[chk][r-1]!='.' || r>3 || chk>2) {
      ++stat;
      continue;
      /*if (stat > 9) {
        printf("input (a,b,c)(1,2,3)\n"
               "? a 1\n"
               "for row a, col 1, etc\n");
        stat = 0;
      }*/
    } else {
      board[chk][r-1] = who ? 'o' : 'x';
      flag = 0;
      break;
    }
  }
  return;
}

/*
int evaluate(NODEPTR p, char player)
{
  static int val;
  p->board;
  return val;
}
*/

void pboard(char board[3][3])
{
  short i, j;
  putchar('\n');
  for (i=0; i<3; ++i) {
    for (j=0; j<3; ++j) {
      printf("%c ", board[i][j]);
    }
    printf("%d\n", i+1);
  }
  puts("a b c\n");
}

#if DEBUG
NODEPTR getnode(void)
{
  NODEPTR p;
  p = (NODEPTR) malloc(sizeof(struct nodetype));
  if (!p) {
    fprintf(stderr,"%s: line=%d: allocation error\n",__FILE__,__LINE__);
    exit(EXIT_FAILURE);
  }
  return(p);
}

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
  for (i=0; i<3; ++i)
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
#endif /* DEBUG */
#endif /* TTT_H */
