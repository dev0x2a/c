#ifndef NRUTIL_H
#define NRUTIL_H

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

/* Numerical Recipes standard error handler */
void nrerror(char error_text[])
{
  void exit();

  fprintf(stderr, "Numerical Recipes run-time error...\n");
  fprintf(stderr, "file=%s, line=%d\n", __FILE__,__LINE__);
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}

/* allocates a float vector with range [nl..nh] */
float *vector(int nl, int nh)
{
  float *v;

  v = (float *)malloc((unsigned) (nh-nl+1)*sizeof(float));

  if (!v)
    nrerror("allocation failure in vector()");
  return v-nl;
}

/* allocates an int vector with range [nl..nh] */
int *ivector(int nl, int nh)
{
  int *v;

  v = (int *)malloc((unsigned) (nh-nl+1)*sizeof(int));

  if (!v)
    nrerror("allocation failure in ivector()");
  return v-nl;
}

/* allocates a double vector with range [nl..nh] */
double *dvector(int nl, int nh)
{
  double *v;

  v = (double *)malloc((unsigned) (nh-nl+1)*sizeof(double));

  if (!v)
    nrerror("allocation failure in dvector()");
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
    nrerror("allocation failure 1 in matrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (float *)malloc((unsigned) (nch-ncl+1)*sizeof(float));
    if (!m[i])
      nrerror("allocation failure 2 in matrix()");
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
    nrerror("allocation failure 1 in dmatrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (double *)malloc((unsigned) (nch-ncl+1)*sizeof(double));
    if (!m[i])
      nrerror("allocation failure 2 in dmatrix()");
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
    nrerror("allocation failure 1 in imatrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (int *)malloc((unsigned) (nch-ncl+1)*sizeof(int));
    if (!m[i])
      nrerror("allocation failure 2 in imatrix()");
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
    nrerror("allocation failure in submatrix()");
  
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
    nrerror("allocation failure in convert_matrix()");
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

#endif /* NRUTIL_H */
