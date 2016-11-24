#include <stdio.h>
#include <stdlib.h>

enum { X=0,O };
enum { OFF=0, ON };

typedef struct user {
  char *stat;
  char *turn;
  char *who;
} *usr_t;

void pboard(char board[3][3])
{
  char i, j;
  putchar('\n');
  for (i=0; i<3; ++i) {
    for (j=0; j<3; ++j) {
      printf("%c ", board[i][j]);
    }
    printf("%d\n", i+1);
  }
  puts("a b c\n");
}

int main(void)
{
  char board[3][3] = {'.','.','.','.','.','.','.','.','.'};
  char n;

  usr_t p1, p2;

  puts("x(0) or o(1)?");
  scanf("%d", &n);
  p1->who = &n;
  //p2->who = !n;
  
  printf("%c goes first\n", p1->who ? 'o' : 'x');
  printf("%c", p2->who);
  //p1->turn = ON;
  //p2->turn = OFF;
  //pboard(board);



  return 0;
}
