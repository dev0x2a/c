#include "alg.h"
#define PGRM "Merge Sort"
#define DEBUG 0

void merge(int a[], int low, int high, int mid)
{
  int i, j, k, c[100];

  i = low;
  j = mid+1;
  k = low;
  while ((i<=mid) && (j<=high)) {
    if (a[i] < a[j]) {
      c[k] = a[i];
      k++;
      i++;
    } else {
      c[k] = a[j];
      k++;
      j++;
    }
  }
  while (i <= mid) {
    c[k] = a[i];
    k++;
    i++;
  }
  while (j <= high) {
    c[k] = a[j];
    k++;
    j++;
  }
  for (i=low; i<k; ++i)
    a[i] = c[i];
}

void merge_sort(int a[], int low, int high)
{
  int mid;
  if (low < high) {
    mid = (low+high)/2;
    merge_sort(a, low, mid);
    merge_sort(a, mid+1, high);
    merge(a, low, high, mid);
  }
}

void print_array(int a[], int n)
{
  int i;
  for (i=0; i<n; ++i)
    printf("%5d", a[i]);
}

int main(void)
{
  int i, c, a[100];
  printf("Give number of elements: ");
  scanf("%d", &c);
  puts("\nEnter elements\n");
  for (i=0; i<c; ++i) {
    printf("num[%d] = ", i);
    scanf("%d", &a[i]);
  }
  puts("Array before sort:");
  print_array(a, c);
  merge_sort(a, 0, c-1);
  puts("\nArray after sort:");
  print_array(a, c);
  putchar('\n');
  return(0);
}

