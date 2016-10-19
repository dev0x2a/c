/*
 * cblk.c
 * catches block comments with c syntax
 * '*' must be on lines
 *
 * ryan keleti
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stdout, "%s [FILE]\n", argv[0]);
    return(-1);
  }
  const char *in = argv[1];
  const char *arr[] = {in ,"| grep '^.\\*'"};
  const char *bin = "cat";
  char out[5000];

  sprintf(out, "%s", bin);
  for (int i=0; i<2; ++i) {
    strcat(out, " ");
    strcat(out, arr[i]);
  }
  system(out);
  return(0);
}

