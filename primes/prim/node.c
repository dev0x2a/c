#include <stdio.h>
#include "prutil.h"

#define NUMNODES 500
#define TRUE 1 
#define FALSE 0

int maketree(int);
int setleft(int, int);
int setright(int, int);

struct nodetype {
  int info;
  int used;
} node[NUMNODES];

extern char *name;;

int main(int argc, char *argv[])
{
  int p, q, num;

  char *name = argv[0];


  if (argc < 2) {
    scanf("%d", &num);
  }
  else
    pr_atoi(argv[1]);

  maketree(num);
  while (scanf("%d", &num) != EOF) {
    p = q = 0;
    while (q<NUMNODES && node[q].used && num!=node[p].info) {
      p = q;
      
      if (num < node[p].info)
        q = 2*p+1;
      else
        q = 2*p+2;
    }

    /* check for duplicates */
    if (num == node[p].info)
      printf("%d is a duplicate\n", num);
    else if (num < node[p].info)
      setleft(p, num);
    else
      setright(p, num);
  }
}

int maketree(int x)
{
  int p;

  node[0].info = x;
  node[0].used = TRUE;

  for (p=1; p<NUMNODES; ++p)
    node[p].used = FALSE;
}

int setleft(int p, int x)
{
  int q;
  char *name;

  q = 2*p+1;

  if (q >= NUMNODES)
    pr_error("array overflow", name);
  else if (node[q].used)
    pr_error("invalid insertion", name);
  else {
    node[q].info = x;
    node[q].used = TRUE;
  }
}

int setright(int p, int x)
{
  int q;
  char *name;

  q = 2*p+2;

  if (q >= NUMNODES)
    pr_error("array overflow", name);
  else if (node[q].used)
    pr_error("invalid insertion", name);
  else {
    node[q].info = x;
    node[q].used = TRUE;
  }
}

