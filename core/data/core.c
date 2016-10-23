#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

void tw(FILE *i, FILE *o, int r);
  
int
main()
{
  FILE *fp;
  char *file[1] = {"tw.c"};
  
  if ((fp=fopen(*file,"r"))!=NULL) {
    tw(fp,stdout,10000);
    fclose(fp);
  }

  return(0);
}

void
tw(FILE *i, FILE *o, int r)
{
  int c;
  while ((c=getc(i))!=EOF) {
    putc(c,o);
    usleep(r);
    fflush(stdout);
  }
}

