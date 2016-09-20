#include <stdio.h>

#define ROW 20
#define COL 20

int main(void)
{
  char grid[ROW][COL];
  int i, j, row, col;

  printf(":\t");
  scanf("%d %d", &row, &col);

  for (i = 0; i < row; ++i) {
    for (j = 0; j < col; ++j) {
      grid[i][j] = '.';
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
  return 0;
}

