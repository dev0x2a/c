/* gnu libc | p 37 */
/* psuedocode */

somefunction()
{
  char *line = NULL;
  size_t len = 0;
  unsigned int lineno = 0;

  error_message_count = 0;
  while (!feof_unlocked(fp)) {
    
    ssize_t n = getline(&line, &len, fp);
    if (n <= 0)
      /* EOF or error */
      break;
    ++lineno;

    /* process the line */
    ...
    
    if ( Detect error in line ) {
      error_at_line(0, errval, filename, lineno,
          "some error text %s", some_variable);
    }
    if (error_message_count != 0)
      error(EXIT_FAILURE, 0, "%u errors found", error_message_count);
}

