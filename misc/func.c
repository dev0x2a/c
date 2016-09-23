#include <stdio.h>

void swap(int p1, int p2);

int main()
{
  int a = 10;
  int b = 20;

  printf("before:\tvalue of a = %d and value of b = %d\n", a, b);
  swap(a, b);
  printf("after: \tvalue of a = %d and value of b = %d\n\n", a, b);
}

void swap(int p1, int p2)
{
  int t;

  t = p2;
  p2 = p1;
  p1= t;
  printf("value of a(p1) = %d and value of b(p2) = %d\n", p1, p2);
}

