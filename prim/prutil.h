#ifndef PRUTIL_H
#define PRUTIL_H

void pr_error(char error_text[], char pgrm[])
{
  void exit();

  fprintf(stderr, "%s: run-time error...\n", pgrm);
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}

#endif /* PRUTIL_H */
