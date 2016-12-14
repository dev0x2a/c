#include "rn.h"
#define STANDALONE

const char *rn_ident_local(void);

void draw(rni *a, FILE *o)
{
  int x;
  fprintf(o, "%d, %d, ", a->u,a->s);
  for (x=a->u-1; x>=0; --x) {
#if SIZEOF_RN_DGT == 4
    fprintf(o, "%081x ", a->dp[x]);
#else
    fprintf(o, "%01611x ", a->dp[x]);
#endif
    //fprintf(o, "%d", a->dp[x]);
  }
  fprintf(o, "\n");
}

int main(void)
{
#ifdef STANDALONE
  printf("%s\n", rn_ident_local());
#endif
  
  rni a, b, c;
  init(&a);
  init(&b);
  init(&c);

  a.s = b.s = c.s = ZPOS;

  rn_set(&a, 1);
  rn_set(&b, 1);
  rn_set(&c, 2);

  rn_read_radix(&a, "4", 10);
  rn_read_radix(&b, "3", 10);


//  draw(&a, stdout);
//  draw(&b, stdout);
 
  rn_add(&a, &b, &c);

  rn_printf(&a, 10, stdout);
  rn_printf(&b, 10, stdout);
  rn_printf(&c, 10, stdout);


//  draw(&c, stdout);
  putchar('\n');
  return 0;
}

void s_rn_add_local(rni *a, rni *b, rni *c)
{
  int x, y=MAX(a->u, b->u), ou=MIN(c->u, RN_SIZ);
  register rnw t=0;
  c->u = y;
  for (x=0; x<y; ++x) {
    t += ((rnw)a->dp[x])+((rnw)b->dp[x]);
    c->dp[x] = (rnd)t;
    t >>= DGT_BIT;
  }
  if (t!=0 && x<RN_SIZ) {
    c->dp[c->u++] = (rnd)t;
    ++x;
  }
  c->u = x;
  for (; x<ou; ++x)
    c->dp[x] = 0;
  rn_clamp(c);
}

const char *rn_ident_local(void)
{
  static char buf[1024];

  memset(buf, 0, sizeof(buf));
  snprintf(buf, sizeof(buf)-1,
      "\n-------------------------------------"
      "\nRBN " RN_VER_S "\n"

#if defined(RN_IDENT_BUILD_DATE)
      "Built on " __DATE__ " at " __TIME__ "\n"
#endif
      "\n  int_st  sizeof(rni) = %lu\n"
      "  digit   sizeof(rnd) = %lu\n"
      "  word    sizeof(rnw) = %lu\n\n"
      "  __SIZEOF_LONG__     = %u\n"
      "  DGT_BIT             = %u\n"
      "  MAX_SIZ             = %u\n"
      "  RN_SIZ              = %u\n"
      "  PR_SIZ              = %u\n\n"
      "  Using\n"
#ifdef __i386__
      "                         __i386__ "
#endif
#ifdef __x86_64__
      "                         __x86_64__ "
#endif
      "\n------------------------------------\n",
    (unsigned long)sizeof(rni),
    (unsigned long)sizeof(rnd),
    (unsigned long)sizeof(rnw),
    __SIZEOF_LONG__,
    DGT_BIT,
    MAX_SIZ,
    RN_SIZ,
    PR_SIZ);

  if (sizeof(rnd) == sizeof(rnw)) {
    strncat(buf, "WARNING:\n  sizeof(rnd) == sizeof(rnw), this build is "
                 "likely to not work properly\n\n",
                 sizeof(buf)-strlen(buf)-1);
  } else {
    strncat(buf, "No warning flags\n", sizeof(buf)-1);
  }
  return buf;
}

