#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 100
#define STACKSIZE 100
struct stack {
  int top;
  int items[STACKSIZE];
};


void partition(int x[], int lb, int ub, int *pj)
{
  int a, down, up, tmp;
  a = x[lb];
  up = ub;
  down = lb;
  while (down < up) {
    while (x[down]<=a && down<ub)
      down++;
    while(x[up] > a)
      up--;
    if (down < up) {
      tmp = x[down];
      x[down] = x[up];
      x[up] = tmp;
    }
  }
  x[lb] = x[up];
  x[up] = a;
  *pj = up;
}
#if 1
int empty(struct stack *ps)
{
  return (ps->top == -1);
}
#endif
int pop(struct stack *ps)
{
  if (empty(ps)) {
    puts("stack underflow");
    exit(1);
  }
  return (ps->items[ps->top--]);
}
#if 1
void push(struct stack *ps, int x)
{
  if (ps->top == STACKSIZE-1) {
    puts("stack overflow");
    exit(1);
  } else
    ps->items[++(ps->top)] = x;
  return;
}
#endif

void quicksort(int x[], int n)
{
  int i, j;
  struct bndtype {
    int lb;
    int ub;
  } newbnds;
  struct {
    int top;
    struct bndtype bounds[MAXSTACK];
  } stack;
  stack.top = -1;
  newbnds.lb = 0;
  newbnds.ub = n-1;
  push(&stack, &newbnds);
  while (!empty(&stack)) {
    popsub(&stack, &newbnds);
    while (newbnds.ub > newbnds.lb) {
      partition(x, newbnds.lb, newbnds.ub, &j);
      if (j-newbnds.lb > newbnds.ub-j) {
        i = newbnds.ub;
        newbnds.ub = j-1;
        push(&stack, &newbnds);
        newbnds.lb = j+1;
        newbnds.ub = i;
      } else {
        i = newbnds.lb;
        newbnds.lb = j+1;
        push(&stack, &newbnds);
        newbnds.lb = i;
        newbnds.ub = j-1;
      }
    }
  }
}

