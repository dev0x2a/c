#include <stdio.h>
#include <stdarg.h>

#undef getchar
#if defined error
#undef error
#endif


/* getchar: unbuffered single character input */
int sys_getchar(void)
{
  char c;

  return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

/* getcharbuf: simple buffered version of getchar */
int sys_getcharbuf(void)
{
  static char buf[BUFSIZ];
  static char *bufp = buf;


/* error: print error msg, then exit */
void sys_error(char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  fprintf(stderr, "error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

