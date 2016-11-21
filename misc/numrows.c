#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
  const int nrow = atoi(argv[1]);
  const int ncol = atoi(argv[2]);

  int m[nrow][ncol];
  int row, col;

  for (row=0; row<nrow; ++row)
    for (col=0; col<ncol; ++col)
      m[row][col] = col+(row*ncol);

  for (row=0; row<nrow; ++row) {
    for (col=0; col<ncol; ++col) {
      printf("%4d ", m[row][col]);
    }
    putchar('\n');
  }
  return 0;
}

