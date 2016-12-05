#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *q;
  struct node *n;
  struct node *y;
} node;

int y_n(char *q)
{
  char a[3];
  printf("%s? [y/n] ", q);
  fgets(a, 3, stdin);
  return a[0] == 'y';
}

node *create(char *q)
{
  node *n = malloc(sizeof(node));
  n->q = strdup(q);
  n->n = NULL;
  n->y = NULL;
  return n;
}
void release(node *n)
{
  if (n) {
    if (n->n)
      release(n->n);
    if (n->y)
      release(n->y);
    if (n->q)
      free(n->q);
    free(n);
  }
}

int main(void)
{
  char q[80];
  char s[20];
  node *start = create("enter suspect ");
  start->n = create("ella");
  start->y = create("emma");

  node *tmp;
  do {
    tmp = start;
    while (1) {
      if (y_n(tmp->q)) {
        if (tmp->y) {
          tmp = tmp->y;
        } else {
          puts("IDENTIFIED");
          break;
        }
      } else if (tmp->n) {
        tmp = tmp->n;
      } else {
        printf("name ");
        fgets(s, 20, stdin);
        node *y = create(s);
        tmp->y = y;

        node *n = create(tmp->q);
        tmp->n = n;

        printf("question true for %s yet not for %s? ", s,tmp->q);
        fgets(q, 80, stdin);
        tmp->q = strdup(q);
        break;
      }
    }
  } while (y_n("Run again"));
  release(start);
  return 0;
}

