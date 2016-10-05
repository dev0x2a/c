/*
 * .c
 * 
 */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  int n;

  if (argc != 2) {
    fprintf(stderr, "%s <num>\n", argv[0]);
    return(-1);
  }
  n = atol(argv[1]);

  do {

  } while ();

  printf("\n");
  return 0;
}

