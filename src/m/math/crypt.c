/*
 * crypt.c
 * cryptography program
 */
#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  unsigned long int i = 0;
  char ch;
  char *file1, *file2;
  FILE *fp, *ft;

  if (argc != 3) {
    printf("%s <file1> <file2>\n", argv[0]);
    return(-1);
  }
  file1 = argv[1];
  file2 = argv[2];
  fp = fopen(file1, "r");
  ft = fopen(file2, "w");

  if (fp == NULL) {
    printf(("cannot open file\n\
        usage:  %s\n\
            [file1] encripted to [file2]\n\
            [file2] must already exist\n\
            [file2] will be overwritten\n"), argv[0]);
    return(-1);
  }
  while (!feof(fp)) {
    ch = getc(fp);
    ch = ~((ch^i));
    i += 2;

    if (i == 100000)
      i = 0;
    putc(ch, ft);
  }
  fclose(fp);
  fclose(ft);
  return 0;
}

