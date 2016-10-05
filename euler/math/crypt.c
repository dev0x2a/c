/*
 * crypt.c
 * cryptography program
 */
#define PROGRAM_NAME "crypt"

#include <stdio.h>

int
main (int argc, char *argv[])
{
  unsigned long int i = 0;
  char ch;
  char file1[20], file2[20];
  FILE *fp, *ft;

  printf("src   ");
  scanf("%s", file1);
  printf("dest  ");
  scanf("%s", file2);
  fp = fopen(file1, "r");
  ft = fopen(file2, "w");

  if (fp == NULL) {
    printf(("cannot open file\n\n\
        usage:  %s\n\
            input file, encript to new file\n\
            new file must already exist\n"), PROGRAM_NAME);
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

