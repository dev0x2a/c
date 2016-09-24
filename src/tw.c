/*
 * tw.c
 *
 * basic typewriter simulation
 * outputs text, char for char
 * modified k&r code
 *
 * takes file from same dir as program
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PROGRAM_NAME "tw"
#define AUTHORS \
  ("Ryan Keleti")

/*
 * #define RATE num
 * change the speed at which the output is displayed
 */
#define RATE 10000

void
tw_print(FILE *in, FILE *out)
{
  int c;

  while ((c = getc(in)) != EOF) {
    putc(c, out);
    usleep(RATE);
    fflush(stdout);
  }
}

int
main(int argc, char **argv)
{
  FILE *fp;
  char *name = argv[0];

  if (argc == 1)
    tw_print(stdin, stdout);
  else
    while (--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", name, *argv);
        exit(1);
      } else {
        tw_print(fp, stdout);
        fclose(fp);
      }
  if (ferror(stdout)) {
    fprintf(stderr, "%s: error writing to stdout\n", name);
    exit(2);
  }
  exit(0);
}

