#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
tw(FILE *i, FILE *o)
{
  int c;
  int r=50000;
  while ((c=getc(i))!=EOF) {
    putc(c,o);
    usleep(r);
    fflush(stdout);
  }
}

void
main(int argc, char *argv[])
{
  FILE *fp;
  char *name=argv[0];

  if (argc==1)
    tw(stdin, stdout);
  else
    while (--argc>0) {
      if ((fp=fopen(*++argv,"r"))==NULL) {
        fprintf(stderr,"%s: can't open %s\n", name,*argv);
        exit(1);
      } else {
        tw(fp,stdout);
        fclose(fp);
      }
    }
  if (ferror(stdout)) {
    fprintf(stderr, "%s: error writing to stdout\n", name);
    exit(2);
  }
  exit(0);
}

