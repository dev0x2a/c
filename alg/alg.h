#ifndef ALG_H
#define ALG_H
/*
 * "Introduction to Algorithms"
 *
 * standard header by Ryan Keleti
 * uses some code from "Numerical Recipes"
 * 
 * @ryankeleti
 */

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#define LRAND_MAX 2147483647

/* algorithm standard error handler */
void aerror(char error_text[], char pgrm[])
{
  void exit();

  fprintf(stderr, "%s: run-time error...\n", pgrm);
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}
/* internal algorithm standard error handler */
void inerror(char error_text[], char cmd[])
{
  void exit();

  fprintf(stderr, "***%s*** run-time error...\n", cmd);
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}

void c_atoi(int k, int argc, char args[])
{
  if (argc < k) {
    fprintf(stderr, "\nInvalid argument count (argc > %d)\n\n", k);
    fprintf(stderr, "use: ./prog %s\n\n", args);
    exit(-1);
  }
}

void aexit(int k, char pgrm[])
{
  void exit();

  fprintf(stdout, "\n***Terminating %s***\n\n", pgrm);
  exit(k);
}

/* prints title for program */
void tprint(char pgrm[])
{
  printf("\n***%s***\n\n", pgrm);
}

int m_atoi(const char s[])
{
  int i, n;

  n = 0;
  for (i=0; s[i]>='0' && s[i]<='9'; ++i) {
    n = 10*n+(s[i]-'0');
  }
  return n;
}

static unsigned long int anext = 1;
int m_rand(void)
{
  anext = anext*1103515245+12345;
  return((unsigned)(anext/65536)%32768);
}

void m_srand(unsigned int seed)
{
  anext = seed;
}

/* allocates a float vector with range [nl..nh] */
float *vector(int nl, int nh)
{
  float *v;
  v = (float *)malloc((unsigned) (nh-nl+1)*sizeof(float));

  if (!v)
    inerror("allocation failure","vector()");
  return v-nl;
}

/* allocates an int vector with range [nl..nh] */
int *ivector(int nl, int nh)
{
  int *v;
  v = (int *)malloc((unsigned) (nh-nl+1)*sizeof(int));

  if (!v)
    inerror("allocation failure", "ivector()");
  return v-nl;
}

/* allocates a double vector with range [nl..nh] */
double *dvector(int nl, int nh)
{
  double *v;
  v = (double *)malloc((unsigned) (nh-nl+1)*sizeof(double));

  if (!v)
    inerror("allocation failure","dvector()");
  return v-nl;
}

/* allocates a float matrix with range [nrl..nrh][ncl] */
float **matrix(int nrl, int nrh, int ncl, int nch)
{
  int i;
  float **m;

  /* allocate pointers to rows */
  m = (float **)malloc((unsigned) (nrh-nrl+1)*sizeof(float *));
  if (!m)
    inerror("allocation failure 1", "matrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (float *)malloc((unsigned) (nch-ncl+1)*sizeof(float));
    if (!m[i])
      inerror("allocation failure 2", "matrix()");
    m[i] -= ncl;
  }

  /* return pointer to array of pointers to rows */
  return m;
}

/* allocates a double matrix with range [nrl..nrh][ncl] */
double **dmatrix(int nrl, int nrh, int ncl, int nch)
{
  int i;
  double **m;

  /* allocate pointers to rows */
  m = (double **)malloc((unsigned) (nrh-nrl+1)*sizeof(double *));
  if (!m)
    inerror("allocation failure 1", "dmatrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (double *)malloc((unsigned) (nch-ncl+1)*sizeof(double));
    if (!m[i])
      inerror("allocation failure 2", "dmatrix()");
    m[i] -= ncl;
  }

  /* return pointer to array of pointers to rows */
  return m;
}

/* allocates a double matrix with range [nrl..nrh][ncl] */
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

/* returns a submatrix with range
 *    [newrl..newrl+(oldrh-oldrl)][newcl..newcl+(oldch-oldcl)]
 * pointing to the existing matrix range
 *    a[oldrl..oldrh][oldcl..oldch]
 */
float **submatrix(float **a, int oldrl, int oldrh, int oldcl, int oldch,
    int newrl, int newcl)
{
  int i, j;
  float **m;

  /* allocate pointers to arrows */
  m = (float **)malloc((unsigned) (oldrh-oldrl+1)*sizeof(float *));
  if (!m)
    inerror("allocation failure", "submatrix()");
  
  /* set pointers to rows */
  for (i=oldrl,j=newrl; i<=oldrh; ++i,++j)
    m[j] = a[i]+oldcl-newcl;

  /* return pointer to array of pointer to rows */
  return m;
}

/* frees a float vector allocated by vector() */
void free_vector(float *v, int nl, int nh)
{
  free((char *) (v+nl));
}

/* frees an int vector allocated by ivector() */
void free_ivector(int *v, int nl, int nh)
{
  free((char *) (v+nl));
}

/* frees a double vector allocated by dvector() */
void free_dvector(double *v, int nl, int nh)
{
  free((char *) (v+nl));
}

/* frees a matrix allocated with matrix() */
void free_matrix(float **m, int nrl, int nrh, int ncl, int nch)
{
  int i;

  for (i=nrh; i>=nrl; --i)
    free((char *) (m[i]+ncl));
  free((char *) (m+nrl));
}

/* frees a matrix allocated with dmatrix() */
void free_dmatrix(double **m, int nrl, int nrh, int ncl, int nch)
{
  int i;

  for (i=nrh; i>=nrl; --i)
    free((char *) (m[i]+ncl));
  free((char *) (m+nrl));
}

/* frees a matrix allocated with imatrix() */
void free_imatrix(int **m, int nrl, int nrh, int ncl, int nch)
{
  int i;

  for (i=nrh; i>=nrl; --i)
    free((char *) (m[i]+ncl));
  free((char *) (m+nrl));
}

/* frees a submatrix allocated by submatrix() */
void free_submatrix(float **b, int nrl, int nrh, int ncl, int nch)
{
  free((char *) (b+nrl));
}

/* allocate a float matrix m[nrl..nrh][ncl..nch] that points to the 
 * matrix a declared in the standard C manner as a[nrow][ncol], where
 * nrow = nrh-nrl+1 and ncol = nch-ncl+1. The routine should be called
 * with the address &a[0][0] as the first arguement
 */
float **convert_matrix(float *a, int nrl, int nrh, int ncl, int nch)
{
  int i, j, nrow, ncol;
  float **m;

  nrow = nrh-nrl+1;
  ncol = nch-ncl+1;

  /* allocate pointers to rows */
  m = (float **)malloc((unsigned) (nrow)*sizeof(float *));
  if (!m)
    inerror("allocation failure", "convert_matrix()");
  m -= nrl;

  for (i=0,j=nrl; i<=nrow-1; ++i,++j)
    m[j] = a+ncol*i-ncl; /* set pointers to rows */
  return m; /* return pointer to array of pointers tp rows */
}

/* free a matrix allocated by convert_matrix() */
void free_convert_matrix(float **b, int nrl, int nrh, int ncl, int nch)
{
  free((char *) (b+nrl));
}

#endif /* ALG_H */
