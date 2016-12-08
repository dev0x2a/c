#if 0
/*
       #include <dirent.h>

       int scandir(const char *dirp, struct dirent ***namelist,
              int (*filter)(const struct dirent *),
              int (*compar)(const struct dirent **, const struct dirent **));

       int alphasort(const struct dirent **a, const struct dirent **b);

       int versionsort(const struct dirent **a, const struct dirent **b);

       #include <fcntl.h>          / * Definition of AT_* constants * /
       #include <dirent.h>

       int scandirat(int dirfd, const char *dirp, struct dirent ***namelist,
              int (*filter)(const struct dirent *),
              int (*compar)(const struct dirent **, const struct dirent **));

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       scandir(), alphasort():
           / * Since glibc 2.10: * / _POSIX_C_SOURCE >= 200809L
               || / * Glibc versions <= 2.19: * / _BSD_SOURCE || _SVID_SOURCE

       versionsort(): _GNU_SOURCE

       scandirat(): _GNU_SOURCE

DESCRIPTION
       The  scandir()  function scans the directory dirp, calling filter() on each directory entry.  Entries for which filter() returns nonzero are stored in strings
       allocated via malloc(3), sorted using qsort(3) with the comparison function compar(), and collected in array namelist which is allocated  via  malloc(3).   If
       filter is NULL, all entries are selected.

       The  alphasort() and versionsort() functions can be used as the comparison function compar().  The former sorts directory entries using strcoll(3), the latter
       using strverscmp(3) on the strings (*a)->d_name and (*b)->d_name.

   scandirat()
       The scandirat() function operates in exactly the same way as scandir(), except for the differences described here.

       If the pathname given in dirp is relative, then it is interpreted relative to the directory referred to by the file descriptor dirfd (rather than relative  to
       the current working directory of the calling process, as is done by scandir() for a relative pathname).

       If  dirp  is relative and dirfd is the special value AT_FDCWD, then dirp is interpreted relative to the current working directory of the calling process (like
       scandir()).

       If dirp is absolute, then dirfd is ignored.

       See openat(2) for an explanation of the need for scandirat().
*/
#endif

#define _DEFAULT_SOURCE
/* print files in current directory in reverse order */
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  struct dirent **namelist;
  int n;

  n = scandir(".", &namelist, NULL, alphasort);
  if (n < 0)
    perror("scandir");
  else {
    while (n--) {
      printf("%s\n", namelist[n]->d_name);
      free(namelist[n]);
    }
    free(namelist);
  }
}

/*
SEE ALSO
       closedir(3), fnmatch(3), opendir(3), readdir(3), rewinddir(3), seekdir(3), strcmp(3), strcoll(3), strverscmp(3), telldir(3)
*/

