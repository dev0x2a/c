
void qsort2(float *left, float *right)
{
  float *p=left, *q=right, w, x;
  do {
    x = *(left+(right-left>>1));
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
      qsort2(left, q);
    left = p;
    q = right;
  } while (left < right);
}

