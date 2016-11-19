#ifndef PHYSUTIL_H
#define PHYSUTIL_H

#include "typedef.h"

/* use integer vector/matrix functions */
#define USEVECTOR 0 

/*
void pr_error(char*, char*);
void inerror(char*, char*);
int pr_atoi(const char*);
int pr_rand(void);
void pr_srand(uint);
void catoi(int, int, char*);
void pr_exit(int, char*);
void tprint(char*);
*/

/* standard error handler */
void pr_error(char error_text[], char pgrm[])
{
  fprintf(stderr, "%s: run-time error...\n", pgrm);
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}

/* function standard error handler */
void inerror(char error_text[], char cmd[])
{
  fprintf(stderr, "%s run-time error...\n", cmd);
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}

int pr_atoi(const char s[])
{
  int i, n = 0;
  for (i=0; s[i]>='0' && s[i]<='9'; ++i)
    n = 10*n+(s[i]-'0');
  return n;
}

int pr_rand(void)
{
  anext = anext*1103515245+12345;
  return((unsigned)(anext/65536)%32768);
}

void pr_srand(uint seed)
{ anext = seed; }

/* count argc */
void catoi(int n, int argc, char args[])
{
  if (argc < n) {
    fprintf(stderr, "\nInvalid argument count (argc > %d)\n\n", n);
    fprintf(stderr, "use: ./prog %s\n\n", args);
    exit(-1);
  }
}

/* exit w/ message */
void pr_exit(int n, char pgrm[])
{
  fprintf(stdout, "\n***Terminating %s***\n\n", pgrm);
  exit(n);
}

/* print title for program */
void tprint(char pgrm[])
{
  printf("\n***%s***\n\n", pgrm);
}

#if USEVECTOR

/* allocates an int vector with range [nl..nh] */
int *ivector(int nl, int nh)
{
  int *v;
  v = (int *)malloc((unsigned) (nh-nl+1)*sizeof(int));
  if (!v)
    inerror("allocation failure", "ivector()");
  return v-nl;
}

/* allocates an int matrix with range [nrl..nrh][ncl] */
int **imatrix(int nrl, int nrh, int ncl, int nch)
{
  int i, **m;
  /* allocate pointers to rows */
  m = (int **)malloc((unsigned) (nrh-nrl+1)*sizeof(int *));
  if (!m)
    inerror("allocation failure 1", "imatrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (int *)malloc((unsigned) (nch-ncl+1)*sizeof(int));
    if (!m[i])
      inerror("allocation failure 2", "imatrix()");
    m[i] -= ncl;
  }

  /* return pointer to array of pointers to rows */
  return m;
}

/* frees an int vector allocated by ivector() */
void free_ivector(int *v, int nl, int nh)
{
  free((char *) (v+nl));
}

/* frees a matrix allocated with imatrix() */
void free_imatrix(int **m, int nrl, int nrh, int ncl, int nch)
{
  int i;
  for (i=nrh; i>=nrl; --i)
    free((char *) (m[i]+ncl));
  free((char *) (m+nrl));
}

#endif /* USEVECTOR */
#endif /* PHYSUTIL_H */
