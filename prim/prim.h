#ifndef PRIM_H
#define PRIM_H

#define PRAND_MAX 2147483647


int p_atoi(const char*);
int p_rand(void);
void p_srand(unsigned int);

static unsigned long int anext = 1;


int p_atoi(const char s[])
{
  int i, n;

  n = 0;
  for (i=0; s[i]>='0' && s[i]<='9'; ++i) {
    n = 10*n+(s[i]-'0');
  }
  return n;
}

int p_rand(void)
{
  anext = anext*1103515245+12345;

  return((unsigned)(anext/65536)%32768);
}

void p_srand(unsigned int seed)
{
  anext = seed;
}

#endif /* PRIM_H */
