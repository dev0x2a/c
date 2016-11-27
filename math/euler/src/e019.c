#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { JAN=1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

struct mi {
  int nr;
  char *name;
};

struct sun {
  int 

struct mi months[] = {
  { JAN, "jan" }, { FEB, "feb" }, { MAR, "mar" }, { APR, "apr" },
  { MAY, "may" }, { JUN, "jun" }, { JUL, "jul" }, { AUG, "aug" },
  { SEP, "sep" }, { OCT, "oct" }, { NOV, "nov" }, { DEC, "dec" }
};

#define nr_of_months (sizeof(months)/sizeof(months[0]))

#define START 1+JAN+1900


static int compmi(const void *m1, const void *m2)
{
  struct mi *mi1 = (struct mi *)m1;
  struct mi *mi2 = (struct mi *)m2;
  return strcmp(mi1->name, mi2->name);
}
  
int main(int argc, char *argv[])
{
  qsort(months, nr_of_months, sizeof(struct mi), compmi);
  
  for (int i=1; i<argc; ++i) {
    struct mi key, *res;
    key.name = argv[i];
    res = bsearch(&key, months, nr_of_months, sizeof(struct mi), compmi);
    if (!res)
      printf("'%s': unknown month\n", argv[i]);
    else
      printf("%s: month #%d\n", res->name,res->nr);
  }
  exit(EXIT_SUCCESS);
}

