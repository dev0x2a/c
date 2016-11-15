/*
 * crypt.c
 * cryptography program
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  if (argc < 2) {
    printf("%s [file1] [file2] (default out.txt)\n", argv[0]);
    exit(-1);
  }
  char ch;
  char *file1, *file2;
  FILE *fp, *ft;
  unsigned long int i = 0;

  file1 = argv[1];
  fp = fopen(file1, "r");

  if (!fp) {
    printf("%s: cannot open file %s\n"
           "[file1] encripted to [file2]\n",
            file1,argv[0]);
    exit(-1);
  }
  file2 = argv[2];
  ft = fopen(file2, "w");
  if (!ft) {
    ft = fopen("out.txt", "w");
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
  exit(0);
}

