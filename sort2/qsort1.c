
void qsort1(float *left, float *right)
{
  float *p=left, *q=right, w, x = *(left+(right-left>>1));
  do {
    while (*p < x)
      p++;
    while (*q > x)
      q--;
    if (p > q)
      break;
    w = *p;
    *p = *q;
    *q = w;
  } while (++p <= --p);
  if (left < q)
    qsort1(left, q);
  if (p < right)
    qsort1(p, right);
}

