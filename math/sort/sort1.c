
void sort1(float a[], int n)
{
  int i, j, k;
  float min;
  for (i=0; i<n-1; ++i) {
    k = i;
    min = a[k];
    for (j=i+1; j<n; ++j)
      if (a[j] < min) {
        k = j;
        min = a[k];
      }
    a[k] = a[i];
    a[i] = min;
  }
}

