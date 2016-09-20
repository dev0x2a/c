/*
 * tail.c
 * tail recursion
 */
#include <stdio.h>

int addnumbers();
int s=0;

int main()
{
  addnumbers();;
  printf("\nThe sum is: %d\n", s);
}
/*
int addnumbers()  //  recursive version
{
  int x;
  if (scanf("%d", &x) > 0) { s += x; addnumbers(); }
}
*/
int addnumbers()  //  nonrecursive version
{
  int x;
  while (scanf("%d", &x) > 0) s += x;
}

