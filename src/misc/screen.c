#include <stdio.h>
#include <math.h>

struct point {
  int x, y;
}

struct rect {
  struct point pt1;
  struct point pt2;
};

struct point pt;
struct point maxpt = { 320, 200 };

struct rect screen;
struct point middle;
struct point makepoint(int, int);


double dist = sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);

struct point makepoint(int x, int y)
{
  struct point tmp;

  tmp.x = x;
  tmp.y = y;
  return tmp;
}

#define XMAX 10
#define YMAX 10
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

screen.pt1 = makepoint(0, 0);
screen.pt2 = makepoint(XMAX, YMAX);
middle = makepoint(
    (screen.pt1.x + screen.pt2.x)/2,
    (screen.pt1.y + screen.pt2.y)/2);

struct point addpoint(struct point p1, struct point p2)
{
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}

int ptinrect(struct point p, struct rect r)
{ /* return 1 if p in r, else 0 if not */
  return p.x >= r.pt1.x && p.x <= pt2.x
    && p.y >= r.pt1.y && p.y <= r.pt2.y;
}

struct canonrect(struct rect r)
{
  struct rect tmp;

  tmp.pt1.x = min(r.pt1.x, r.pt2.x);
  tmp.pt1.y = min(r.pt1.y, r.pt2.y);
  tmp.pt2.x = max(r.pt1.x, r.pt2.x);
  tmp.pt2.y = max(r.pt1.y, r.pt2.y);
  return tmp;
}

struct point origin, *pp;

pp = &origin;
printf("origin is (%d.%d)\n", (*pp).x, (*pp).y);
printf("origin is (%d.%d)\n", pp->x, pp->y);

struct rect r, *rp = r;

/* all virtually the same */
r.pt1.x
rp->pt1.x
(r.pt1).x
(rp->pt1).x

struct {
  int len;
  char *str;
} *p;

++p->len; /* increments len */
++(p->len); /* is implied by ++p->len */
(++p)->len; /* inc then access len */
(p++)->len; /* inc after, () not req */

*p->str; /* fetches whatever str points to */
*p->str++; /* inc str after accessing whatever it points to,
              similar to (*s++) */
(*p->str)++; /* inc whatever str points to */
*p++->str; /* inc p after accessing whatever str points to*/

#define NKEYS 10

char *keyword[NKEYS];
int keycount[NKEYS];

struct key1 {
  char *word ;
  int count;
} keytab_[NKEYS];
//or
struct key2 {
  char *word;
  int count;
};
struct key2 keytab[NKEYS];
//or

struct key {
  char *word;
  int count;
} keytab[] = {
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  "int", 0,
  "long", 0,
  "signed", 0,
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0,
  "do", 0,
  "if", 0,
  "else", 0,
  "for", 0,
  "asm", 0,
  "goto", 0,
  "inline", 0,
  "register", 0,
  "struct", 0,
  "typedef", 0,
  "#define", 0,
  "#if", 0,
  "#else", 0,
  "#endif", 0,
  "#ifndef", 0,
  "#include", 0
};

