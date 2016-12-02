#include <stdio.h>
#include <stdlib.h>

#define CELL(i,j)  (field[size*(i)+(j)])
#define ALIVE(i,j) t[size*(i)+(j)] = 1
#define DEAD(i,j)  t[size*(i)+(j)] = 0
#define SCELL(i,j) field[FIELD_SIZE*(i)+(j)] = 1

#define BLINK_SIZE 3
#define BLINK_GEN 3

#define FIELD_SIZE 75
#define FIELD_GEN 145

char smallblink[] = {
  0,0,0,
  1,1,1,
  0,0,0
};
char tmpblink[BLINK_SIZE*BLINK_SIZE];

char field[FIELD_SIZE*FIELD_GEN];
char tmpfield[FIELD_SIZE*FIELD_SIZE];

int alivecount(const char *field, int i, int j, int size)
{
  int x, y, a=0;
  for (x=i-1; x<=(i+1); ++x) {
    for (y=j-1; y<=(j+1); ++y) {
      if (x==i && y==j)
        continue;
      if (y<size && x<size && x>=0 && y>=0) {
        a += CELL(x,y);
      }
    }
  }
  return(a);
}

void evolve(const char *field, char *t, int size)
{
  int i, j, alive, cs;
  for (i=0; i<size; ++i) {
    for (j=0; j<size; ++j) {
      alive = alivecount(field, i, j, size);
      cs = CELL(i,j);
      if (cs) {
        if (alive>3 || alive<2)
          DEAD(i,j);
        else
          ALIVE(i,j);
      } else {
        if (alive == 3)
          ALIVE(i,j);
        else
          DEAD(i,j);
      }
    }
  }
}

void dumpfield(const char *f, int size)
{
  int i;
  for (i=0; i<(size*size); ++i) {
    if (i%size == 0)
      putchar('\n');
    printf("%c", f[i] ? 'x' : '.');
  }
  putchar('\n');
}

int main(int argc, char *argv[])
{
  int i;
  char *fa, *fb, *tt, op, ch;
  FILE *fp;

  if (argc > 1) {
    op = *argv[1];
  } else {
    op = 'b';
  }

  switch(op) {
    case 'B':
    case 'b':
      fa = smallblink;
      fb = tmpblink;
      for (i=0; i<BLINK_GEN; ++i) {
        dumpfield(fa, BLINK_SIZE);
        evolve(fa, fb, BLINK_SIZE);
        tt = fb;
        fb = fa;
        fa = tt;
      }
      return(0);
    case 'G':
    case 'g':
      for (i=0; i<(FIELD_SIZE*FIELD_SIZE); ++i)
        field[i] = 0;
                 SCELL(0,1);
                            SCELL(1,2);
      SCELL(2,0);SCELL(2,1);SCELL(2,2);
      fa = field;
      fb = tmpfield;
      for (i=0; i<FIELD_GEN; ++i) {
        dumpfield(fa, FIELD_SIZE);
        evolve(fa, fb, FIELD_SIZE);
        tt = fb;
        fb = fa;
        fa = tt;
      }
      return(0);
    case 'f':
    case 'F':
      for (i=0; i<(FIELD_SIZE*FIELD_SIZE); ++i)
        field[i] = 0;
      fp = fopen(argv[2], "r");
      if (!fp) {
        fprintf(stderr, "%s: file not found\n", argv[0]);
        break;
      }
      int u, v;
      //while (!feof(fp)) {
      //  fscanf(fp, "SCELL(%d,%d)", &u,&v);
      //  SCELL(u,v);
      //}
back:
      while (fscanf(fp, "(%d,%d)", &u,&v) == 2) {
        SCELL(u,v);
        goto back;
      }
      fa = field;
      fb = tmpfield;
      for (i=0; i<FIELD_GEN; ++i) {
        dumpfield(fa, FIELD_SIZE);
        evolve(fa, fb, FIELD_SIZE);
        tt = fb;
        fb = fa;
        fa = tt;
      }
      fclose(fp);
      return(0);
    default:
      fprintf(stderr, "%s: no CA available\n", argv[0]);
      break;
  }
  return(1);
}

