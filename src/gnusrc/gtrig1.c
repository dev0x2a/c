#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 60
#define HEIGHT 20
#define X WIDTH / 2
#define Y HEIGHT / 2
#define XMAX WIDTH - X - 1
#define XMIN -(WIDTH - X)
#define YMAX HEIGHT - Y
#define YMIN -(HEIGHT - Y) + 1
#define PI 3.14159

char grid[HEIGHT][WIDTH];
int plot(int x, int y, char o);
double f(char *t, double r);
void init(void);
void show(void);

int main(int argc, char **argv) {
  double a, r, k;
  double x, y;
  char out = '*';
  a = 1.0;
  r = 0.0;
  k = 0.0;
  // if(argc>1)out=argv[1][0];
  if (argc > 2) {
    a = atof(argv[2]);
    r = atof(argv[3]);
    k = atof(argv[4]);
  }
  init();
  for (x = -PI; x <= PI; x += 0.1) {
    // switch(t)
    y = a * sin(x + r) + k;
    plot(rintf(x * 10), rintf(y * 8), out);
  }
  show();
  return (0);
}

int plot(int x, int y, char o) {
  if (x > XMAX || x < XMIN || y > YMAX || y < YMIN)
    return (-1);
  grid[Y - y][X + x] = o;
  return (1);
}
double f(char *t, double r) {}
void init(void) {
  int x, y;
  for (y = 0; y < HEIGHT; ++y)
    for (x = 0; x < WIDTH; ++x)
      grid[y][x] = ' ';
  for (y = 0; y < HEIGHT; ++y)
    grid[y][X] = '|';
  for (x = 0; x < WIDTH; ++x)
    grid[Y][x] = '-';
  grid[Y][X] = '+';
}
void show(void) {
  int x, y;
  for (y = 0; y < HEIGHT; ++y) {
    for (x = 0; x < WIDTH; ++x)
      putchar(grid[y][x]);
    putchar(10);
  }
}
