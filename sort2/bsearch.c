#if 0
/*
 #include <stdlib.h>

       void *bsearch(const void *key, const void *base,
                     size_t nmemb, size_t size,
                     int (*compar)(const void *, const void *));

       The  bsearch() function searches an array of nmemb objects, the initial member of which is pointed to by base, 
       for a member that matches the object pointed to by key.  The size of each member of the array is specified by size.

       The contents of the array should be in ascending sorted order according to the comparison function referenced by compar.
       The compar routine  is  expected  to have two arguments which point to the key object and to an array member, in that order,
        and should return an integer less than, equal to, or greater than zero if the key object is found, respectively, 
        to be less than, to match, or be greater than the array member.

       ┌──────────┬───────────────┬─────────┐
       │Interface │ Attribute     │ Value   │
       ├──────────┼───────────────┼─────────┤
       │bsearch() │ Thread safety │ MT-Safe │
       └──────────┴───────────────┴─────────┘
       hsearch(3), lsearch(3), qsort(3), tsearch(3)
*/
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mi {
  int nr;
  char *name;
} months[] = {{ 1, "jan" }, { 2, "feb" }, { 3, "mar" }, { 4, "apr" },
              { 5, "may" }, { 6, "jun" }, { 7, "jul" }, { 8, "aug" },
              { 9, "sep" }, {10, "oct" }, {11, "nov" }, {12, "dec" }};

#define nr_of_months (sizeof(months)/sizeof(months[0]))

static int
compmi(const void *m1, const void *m2)
{
  struct mi *mi1 = (struct mi *) m1;
  struct mi *mi2 = (struct mi *) m2;
  return strcmp(mi1->name, mi2->name);
}
  
int 
main(int argc, char *argv[])
{
  int i;
  
  qsort(months, nr_of_months, sizeof(struct mi), compmi);
  for (i=1; i<argc; ++i) {
    struct mi key, *res;
    key.name = argv[i];
    res = bsearch(&key, months, nr_of_months,
        sizeof(struct mi), compmi);
    if (res == NULL)
      printf("'%s': unknown month\n", argv[i]);
    else
      printf("%s: month #%d\n", res->name, res->nr);
  }
  exit(EXIT_SUCCESS);
}

