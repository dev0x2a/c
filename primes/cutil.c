
inline void cerror(char error_text[])
{
  void exit();
  fprintf(stderr, "Numerical Recipes run-time error...\n");
  fprintf(stderr, "file=%s, line=%d\n", __FILE__,__LINE__);
  fprintf(stderr, "%s\n", error_text);
  fprintf(stderr, "...now exiting to system...\n");
  exit(1);
}

/* allocates float vector [nl..nh] */
float *vector(int nl, int nh)
{
  float *v;
  v = (float *)malloc((unsigned) (nh-nl+1)*sizeof(float));
  if (!v)
    cerror("allocation failure in vector()");
  return v-nl;
}

/* allocates int vector [nl..nh] */
int *ivector(int nl, int nh)
{
  int *v;
  v = (int *)malloc((unsigned) (nh-nl+1)*sizeof(int));
  if (!v)
    cerror("allocation failure in ivector()");
  return v-nl;
}

/* allocates double vector [nl..nh] */
double *dvector(int nl, int nh)
{
  double *v;
  v = (double *)malloc((unsigned) (nh-nl+1)*sizeof(double));
  if (!v)
    cerror("allocation failure in dvector()");
  return v-nl;
}

/* allocates float matrix [nrl..nrh][ncl] */
float **matrix(int nrl, int nrh, int ncl, int nch)
{
  int i;
  float **m;

  /* allocate pointers to rows */
  m = (float **)malloc((unsigned) (nrh-nrl+1)*sizeof(float *));
  if (!m)
    cerror("allocation failure 1 in matrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (float *)malloc((unsigned) (nch-ncl+1)*sizeof(float));
    if (!m[i])
      cerror("allocation failure 2 in matrix()");
    m[i] -= ncl;
  }
  /* return pointer to array of pointers to rows */
  return m;
}

/* allocates double matrix [nrl..nrh][ncl] */
double **dmatrix(int nrl, int nrh, int ncl, int nch)
{
  int i;
  double **m;

  /* allocate pointers to rows */
  m = (double **)malloc((unsigned) (nrh-nrl+1)*sizeof(double *));
  if (!m)
    cerror("allocation failure 1 in dmatrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (double *)malloc((unsigned) (nch-ncl+1)*sizeof(double));
    if (!m[i])
      cerror("allocation failure 2 in dmatrix()");
    m[i] -= ncl;
  }
  /* return pointer to array of pointers to rows */
  return m;
}

/* allocates double matrix [nrl..nrh][ncl] */
int **imatrix(int nrl, int nrh, int ncl, int nch)
{
  int i, **m;

  /* allocate pointers to rows */
  m = (int **)malloc((unsigned) (nrh-nrl+1)*sizeof(int *));
  if (!m)
    cerror("allocation failure 1 in imatrix()");
  m -= nrl;

  /* allocate rows and set pointers to them */
  for (i=nrl; i<=nrh; ++i) {
    m[i] = (int *)malloc((unsigned) (nch-ncl+1)*sizeof(int));
    if (!m[i])
      cerror("allocation failure 2 in imatrix()");
    m[i] -= ncl;
  }
  /* return pointer to array of pointers to rows */
  return m;
}

/* returns submatrix with range
 *    [newrl..newrl+(oldrh-oldrl)][newcl..newcl+(oldch-oldcl)]
 * pointing to the existing matrix range
 *    a[oldrl..oldrh][oldcl..oldch] */
float **submatrix(float **a, int oldrl, int oldrh, int oldcl, int oldch,
    int newrl, int newcl)
{
  int i, j;
  float **m;

  /* allocate pointers to arrows */
  m = (float **)malloc((unsigned) (oldrh-oldrl+1)*sizeof(float *));
  if (!m)
    cerror("allocation failure in submatrix()");
  
  /* set pointers to rows */
  for (i=oldrl,j=newrl; i<=oldrh; ++i,++j)
    m[j] = a[i]+oldcl-newcl;

  /* return pointer to array of pointer to rows */
  return m;
}

void free_vector(float *v, int nl)
{ free((char *) (v+nl)); }

void free_ivector(int *v, int nl)
{ free((char *) (v+nl)); }

void free_dvector(double *v, int nl)
{ free((char *) (v+nl)); }

void free_matrix(float **m, int nrl, int nrh, int ncl)
{
  int i;
  for (i=nrh; i>=nrl; --i)
    free((char *) (m[i]+ncl));
  free((char *) (m+nrl));
}

void free_dmatrix(double **m, int nrl, int nrh, int ncl)
{
  int i;
  for (i=nrh; i>=nrl; --i)
    free((char *) (m[i]+ncl));
  free((char *) (m+nrl));
}

void free_imatrix(int **m, int nrl, int nrh, int ncl)
{
  int i;
  for (i=nrh; i>=nrl; --i)
    free((char *) (m[i]+ncl));
  free((char *) (m+nrl));
}

void free_submatrix(float **b, int nrl)
{ free((char *) (b+nrl)); }

/* allocate float matrix m[nrl..nrh][ncl..nch] that points to the 
 * matrix a declared in the standard C manner as a[nrow][ncol], where
 * nrow = nrh-nrl+1 and ncol = nch-ncl+1. The routine should be called
 * with the address &a[0][0] as the first arguement */
float **convert_matrix(float *a, int nrl, int nrh, int ncl, int nch)
{
  int i, j, nrow, ncol;
  float **m;

  nrow = nrh-nrl+1;
  ncol = nch-ncl+1;
  /* allocate pointers to rows */
  m = (float **)malloc((unsigned) (nrow)*sizeof(float *));
  if (!m)
    cerror("allocation failure in convert_matrix()");
  m -= nrl;

  for (i=0,j=nrl; i<=nrow-1; ++i,++j)
    m[j] = a+ncol*i-ncl; /* set pointers to rows */
  return m; /* return pointer to array of pointers tp rows */
}

void free_convert_matrix(float **b, int nrl)
{ free((char *) (b+nrl)); }

