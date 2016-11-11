#include <malloc.h>
#include <stdio.h>

/* Numerical Recipes standard error handler */
void nrerror(char error_text[])
{
  void exit();

  fprintf(stderr, "Numerical Recipes run-time error...\n");
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
double *ivector(int nl, int nh)
{
  double *v;

  v = (double *)malloc((unsigned) (nh-nl+1)*sizeof(double));

  if (!v)
    nrerror("allocation failure in dvector()");
  return v-nl;
}

/* allocates a float matrix with range [nrl..nrh][ncl] */
float **matrix(int ncl, int nrh, int ncl, int nch)
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
double **dmatrix(int ncl, int nrh, int ncl, int nch)
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
int **imatrix(int ncl, int nrh, int ncl, int nch)
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

