
void sort2(char a[][21], int n)
{
  char *p, min[21];
  int i, j;
  for (i=0; i<n-1; ++i) {
    p = a[i];
    min = a[k];
    for (j=i+1; j<n; ++j)
      if (strcmp(a[j], p) < 0)
        p = a[j];
    strcpy(min, p);
    strcpy(p, a[i]);
    strcpy(a[i], min);
  }
}

