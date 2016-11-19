
void sort3(float *a, int n)
{
  float *left=a, *right=a+n-1, *start=a, *p, *q, x;
  do {
    for (p=left; p<right; ++p) {
      q = p+1;
      if (*p > *q) {
        x = *q;
        *q = *p;
        *p = x;
        start = p;
      }
    }
    right = start;
    for (p=right; p>left; --p) {
      q = p-1;
      if (*q > *p) {
        x = *q;
        *q = *p;
        *p = x;
        start = p;
      }
    }
    left = start;
  } while (left < right);
}

