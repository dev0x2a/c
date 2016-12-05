#include<stdio.h>

#define _(a) putchar(q[a]);

int q[3]={10,42,46},
    a=24;

int main()
{
  while(--a) {
    _(a&1?0:1)
    _(!a)
    _(2)
    _(0)
  }
}

