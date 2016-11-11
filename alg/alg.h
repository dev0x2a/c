#ifndef ALG_H
#define ALG_H

#define LRAND_MAX 2147483647


int m_atoi(const char*);
int m_rand(void);
void m_srand(unsigned int);

static unsigned long int anext = 1;


int m_atoi(const char s[])
{
  int i, n;

  n = 0;
  for (i=0; s[i]>='0' && s[i]<='9'; ++i) {
    n = 10*n+(s[i]-'0');
  }
  return n;
}

int m_rand(void)
{
  anext = anext*1103515245+12345;

  return((unsigned)(anext/65536)%32768);
}

void m_srand(unsigned int seed)
{
  anext = seed;
}

#endif /* ALG_H */
