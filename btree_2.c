#include <stdint.h> // 15 line binary tree (0 = left node, 1 = right, 2 = key, 3 = value )
#include <stdlib.h> // by graphitemaster 2016 (the same guy who did the 15 line hashtable)

void *(*bnew(void))[4]
{
  return calloc(sizeof(void*[4]), 1);
}

void bdel(void *(*n)[4])
{
  if (n) {
    bdel((*n)[0]);
    bdel((*n)[1]);
    free(n);
  }
}

void *(*bput(void *(*n)[4], int k, int v))[4] {
  void *(**m)[4] = (void *(**)[4])&((*n)[!!(k < (uintptr_t)((*n)[2]))]);
  if (*m)
    return bput(*m, k, v);
  *m = bnew();
  (**m)[2] = (void *)(uintptr_t)k;
  (**m)[3] = (void *)(uintptr_t)v;
  return *m;
}

void *(*bget(void *(*n)[4], int k))[4]
{
  if (!n)
    return 0;
  if (k < (uintptr_t)(*n)[2])
    return bget((*n)[1], k);
  if (k == (uintptr_t)(*n)[2])
    return n;
  return bget((*n)[0], k);
}


// example of use
#include <stdio.h>

int main(void)
{
  void *(*n)[4] = bnew(); // make new one (root is key = 0, value = 0)

  // add some things
  bput(n, 100, 100);
  bput(n, 200, 500);
  bput(n, 10, 35);
  bput(n, 75, 500);
  bput(n, 6000, 1337);

  void *(*a)[4] = bget(n, 75); // 500
  void *(*b)[4] = bget(n, 6000); // 1337
  printf("%d\n", (int)(uintptr_t)(*a)[3]); // 3 is key, need to cast to int
  printf("%d\n", (int)(uintptr_t)(*b)[3]);

  // something not in there
  void *(*c)[4] = bget(n, 42);
  printf("search for 42 should be null: %p\n", c);

  bdel(n);
}

