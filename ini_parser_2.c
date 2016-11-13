#include <stdint.h> // 15 line binary tree (0 = left node, 1 = right, 2 = key, 3 = value )
#include <stdlib.h> // by graphitemaster 2016 (the same guy who did the 15 line hashtable)
void *(*bnew(void))[4] {
  return calloc(sizeof(void*[4]), 1);
}
void bdel(void *(*l)[4]) {
  if (l) bdel((*l)[0]), bdel((*l)[1]), free(l);
}
void *(*bput(void *(*l)[4], int k, int v))[4] {
  void *(**m)[4] = (void *(**)[4])&((*l)[!!(k < (uintptr_t)((*l)[2]))]);
  return *m ? bput(*m, k, v) : (*m = bnew(), (**m)[2] = (void *)(uintptr_t)k, (**m)[3] = (void *)(uintptr_t)v), *m;
}
void *(*bget(void *(*l)[4], int k))[4] {
  return l ? (k < (uintptr_t)(*l)[2]) ? bget((*l)[1], k) : (k == (uintptr_t)(*l)[2]) ? l : bget((*l)[0], k) : 0;
}


// example of use
#include <stdio.h>
int main() {
  void *(*l)[4] = bnew(); // make new one (root is key = 0, value = 0)

  // add some things
  bput(l, 100, 100);
  bput(l, 200, 500);
  bput(l, 10, 35);
  bput(l, 75, 500);
  bput(l, 6000, 1337);

  void *(*a)[4] = bget(l, 75); // 500
  void *(*b)[4] = bget(l, 6000); // 1337
  printf("%d\n", (int)(uintptr_t)(*a)[3]); // 3 is key, need to cast to int
  printf("%d\n", (int)(uintptr_t)(*b)[3]);

  // something not in there
  void *(*c)[4] = bget(l, 42);
  printf("search for 42 should be null: %p\n",  c);

  bdel(l);
}
