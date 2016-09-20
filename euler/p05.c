#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int gcd(int a, int b) {
  while (a != b) {
    if (a > b) a -= b;
    else b -= a;
  }
  return a;
}

int lcm(int x, int y) {
  return (x / gcd(x,y) * y);
}

int main() {

  int n = 1;

  bool found = false;
  for (int i = 1; i < 21; i++) {
    n = lcm(n, i+1);
  }
  found = true;
  
  if (found == true) printf("%d\n", n);
  return 0;

}

