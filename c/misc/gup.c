/*
 * C program
 * This is a test
 */

#include <getopt.h>
#include <stdio.h>
#include <sys/types.h>

//#include "system.h"

#define PROGRAM_NAME "rtest"

#define AUTHORS \
  proper_name ("Ryan Keleti")

#define EXIT_SUCCESS 0


void 
usage (int status)
{
  if (status != EXIT_SUCCESS)
    //emit_try_help ();
    ;
  else {
    printf (_("\
          usage: %s [OPTION]\n"),
        program_name);
    fputs (_("\
          This is a test C program.\n\
          \n\
          "), stdout);
    fputs (_("\
          -O, --option\t\ttest option 1\n\
          "), stdout);
  }
  exit (status);
}

int
main (int argc, char **argv)
{
  char isuser;

  printf("::  are you default user    ");
  scanf("%c", &isuser);
  printf("%c", isuser;

  return 0;
}
