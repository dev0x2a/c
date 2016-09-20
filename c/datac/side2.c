/*
 * side2.c
 * second program to demonstrate side effects
 */
#include <stdio.h>

int i=5;
int f();
int g();

int main()
{
  printf("%d", f() + g());
}

int f()
{
  return ++i;
}

int g()
{
  return i *= 10;
}

