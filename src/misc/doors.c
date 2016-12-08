#include <stdio.h>

#define NUM_DOORS 100

int main(int argc, char *argv[])
{
  int open[NUM_DOORS] = { 0 };
  int *doorptr, *doorlim = open+NUM_DOORS;
  int pass;

  for (pass=NUM_DOORS; pass; --pass) {
    for (doorptr=open+(pass-1); doorptr<doorlim; doorptr+=pass) {
      (*doorptr) ^= 1;
    }
  }

  for (doorptr=open; doorptr!=doorlim; ++doorptr) {
    printf("door #%ld is %s\n",
        (doorptr-open)+1, (*doorptr) ? "open" : "closed");
  }
  return 0;
}

