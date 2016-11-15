#include <stdio.h>
#include <stdlib.h>

void draw(char *a[])
{
  printf("\033c");
  printf("\n %c | %c | %c\n", a[0][0],a[0][1],a[0][2]);
  printf("---+---+---\n");
  printf(" %c | %c | %c\n", 'x','x','x');
  printf("---+---+---\n");
  printf(" %c | %c | %c\n\n", 'x','x','x');
}

int main(int argc, char *argv[])
{
  int i, j;
  char a[3][3];



  for (i=j=0; i<4,j<4; ++i,++j) {
    a[i][j] = 'x';
  }
  printf("%c %c %c\n", a[0][0],a[0][1],a[0][2]);

  draw(a);

  exit(0);
}

