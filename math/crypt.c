/*
 * crypt.c
 * cryptography program
 */
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{ 
  if (argc != 3) {
    printf("%s <file1> <file2>\n", argv[0]);
    return(-1);
  }
  char ch, *file1, *file2;
  FILE *fp, *ft;
  unsigned long int i;
  
  i = 0;
  file1 = argv[1];
  file2 = argv[2];
  fp = fopen(file1, "r");
  if (!fp) {
    printf("%s: cannot open file %s\n"
           "[file1] encripted to [file2]\n"
           "[file2] will be overwritten\n",
            argv[0],file1);
    return(-1);
  }
  ft = fopen(file2, "w");
  while (!feof(fp)) {
    ch = getc(fp);
    ch = ~((ch^i));
    i += 2;
    if (i == 100000)
      i = 0;
    putc(ch,ft);
  }
  fclose(fp);
  fclose(ft);
  return(0);
}

