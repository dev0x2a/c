
void qsort3(float *left, float *right)
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
    if (q-left < right-p) {
      if (left < q)
        qsort3(left, q);
      left = p;
      q = right;
    } else {
      if (p < right)
        qsort3(p, right);
      right = q;
      p = left;
    }
  } while (left < right);
}

