/* gnu libc | p 35 */

#define _GNU_SOURCE

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *open_sesame(char *name)
{
  FILE *stream;

  errno = 0;
  stream = fopen(name, "r");
  if (stream == NULL) {
    fprintf(stderr, "%s: couldn't open file %s; %s\n",
        program_invocation_short_name, name, strerror(errno));
    exit(EXIT_FAILURE);
  }
  else
    return(stream);
}

