/*
 * calc.c
 * rudimentary calculator
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
  float m, n, k;
  char op;

  if (argc != 4) {
    fprintf(stderr, "%s <num> <+,-,x,/> <num>\n", argv[0]);
    return(-1);
  }
  m = atof(argv[1]);
  op = argv[2][0];
  n = atof(argv[3]);

  for (int i=0; i<=0; ++i) {
    switch(op) {
      case '+': k = m+n; break;
      case '-': k = m-n; break;
      case 'x': k = m*n; break;
      case '/': k = m/n; break;
      default : printf("error\n"); break;
    }
    printf("%f\n", k);
  }
  return 0;
}

