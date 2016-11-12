#ifndef PRUTIL_H
#define PRUTIL_H

static unsigned long int anext = 1;
unsigned char pr_bittab[] = {
  1,2,4,8,16,32,64,128
};

void pr_error(char error_text[], char pgrm[])
{
  void exit();

  fprintf(stderr, "%s: run-time error...\n", pgrm);
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}


int pr_atoi(const char s[])
{
  int i, n;

  n = 0;
  for (i=0; s[i]>='0' && s[i]<='9'; ++i) {
    n = 10*n+(s[i]-'0');
  }
  return n;
}

int pr_rand(void)
{
  anext = anext*1103515245+12345;
  return((unsigned)(anext/65536)%32768);
}

void pr_srand(unsigned int seed)
{
  anext = seed;
}

#endif /* PRUTIL_H */

