/*
 * crypt.c
 * cryptography program
 */

#define PROGRAM_NAME "crypt"

#include <stdio.h>

int
main (void)
{
  unsigned long int i = 0;
  char ch;
  char name1[20], name2[20];
  FILE *fp, *ft;

  printf(":: enter source file         ");
  scanf("%s", name1);
  printf(":: enter destination file    ");
  scanf("%s", name2);
  fp = fopen(name1, "r");
  ft = fopen(name2, "w");

  if (fp == NULL) {
    printf(("::  cannot open file\n\n\
        usage:  %s\n\
            input file, encript to new file\n\
            new file must already exist\n"), PROGRAM_NAME);
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

