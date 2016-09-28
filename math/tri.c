/*
 * tri.c
 * triangle calculations
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PROGRAM_NAME "tri"

#define AUTHORS \
  ("Ryan Keleti")

int
main (int argc, char **argv)
{
  int type;

  printf("which do you wish to solve --\n\n\
      1\t\tright triangle\n\
      2\t\tnon-right triangle\n\n\
      enter (default 1)   ");
  scanf("%d", &type);
  if (type != 1 || 2) type = 1;

  switch (type)
  {
    case 1:
      fputs("\nfor a² + b² = c²\n\n", stdout);
      break;
    case 2:
      fputs("\nlaw of sines 'n cosines\n\n", stdout);
      break;
    default:
      fputs("\nfor a² + b² = c²\n\n", stdout);
      break;
  }
  return 0;
}

