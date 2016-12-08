/*
 * convert the source file timestamp into a localized date string
 * this code is /intentionally/ faulty, it's an exercise
 */

char *
localized_time(char *filename)
{
  struct tm *tm_ptr;
  struct stat stat_block;
  char buffer[120];

  /*  get the source file's timestamp in format time_t  */
  stat(filename, &stat_block);

  /*  convert UNIX time_t into a struct tm holding local time */
  tm_ptr = localtime(&stat_block.st_mtime);

  /*  convert tm struct into a string in local format */
  strftime(buffer, sizeof(buffer). "%a %b %e %T %Y", tm_ptr);

  return buffer;
}

