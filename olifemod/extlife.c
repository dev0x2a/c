#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define for_x for (int x=0; x<w; ++x)
#define for_y for (int y=0; y<w; ++y)
#define SCELL(i,j) uinv[(i)][(j)] = 1

void show(void *, int, int);
void evolve(void *, int, int);

void show(void *u, int w, int h)
{
  int(*uinv)[w] = u;
  
  printf("\033[H");
  for_y {
    for_x
      printf(uinv[y][x] ? "\033[07m  \033[m" : "  ");
    printf("\033[E");
  }
  fflush(stdout);
}

void evolve(void *u, int w, int h)
{
  unsigned(*uinv)[w] = u;
  unsigned new[h][w];

  for_y
    for_x {
      int n = 0;
      for (int y1 = y - 1; y1 <= y + 1; ++y1)
        for (int x1 = x - 1; x1 <= x + 1; ++x1)
          if (uinv[(y1 + h) % h][(x1 + w) % w])
            n++;
      if (uinv[y][x])
        n--;
      new[y][x] = (n == 3 || (n == 2 && uinv[y][x]));
    }

  for_y
    for_x
      uinv[y][x] = new[y][x];
}

int main(int argc, char *argv[])
{
  int w=0, h=0;
  FILE *fp;
  char ch;

  if (argc > 1)
    w = atoi(argv[1]);
  if (argc > 2)
    h = atoi(argv[2]);
  if (w <= 0)
    w = 30;
  if (h <= 0)
    h = 30;
  unsigned field[w][h];
  unsigned uinv[h][w];
  //if (argv[1][0] == '-') {
  if (argv[1][0] == '-') {
    ch = argv[1][1];
    switch (ch) {

    case 'f':
    case 'F':
      fp = fopen(argv[2], "r");
      if (!fp) {
        fprintf(stderr, "%s: file not found\n", argv[0]);
        return 1;
      }
      int u=0, v=0;
      while (!feof(fp)) {
        fscanf(fp, "(%d,%d)", &u, &v);
        SCELL(u, v);
      }
      fclose(fp);
      break;

    case 'g':
    case 'G':
      SCELL(0, 1);
      SCELL(1, 2);
      SCELL(2, 0);
      SCELL(2, 1);
      SCELL(2, 2);
      break;
    default:
      for_x for_y uinv[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
      break;
    }
  } else {
    for_x for_y uinv[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
  }
  //fprintf(stderr, "usage: %s (-f [FILE]  |  - for rand)\n", argv[0]);
  while (1) {
    show(uinv, w, h);
    evolve(uinv, w, h);
    usleep(200000);
  }
  return 0;
}
