#include <stdio.h>

int partition(int a[], int beg, int end)
{
  int left, right, loc, pivot, flag = 0;
  
  loc=left=beg;
  right = end;
  pivot = a[loc];
  while (flag == 0) {
    while ((pivot<=a[right]) && (loc!=right))
      right--;
    if (loc == right)
      flag = 1;
    else {
      a[loc] = a[right];
      left = loc+1;
      loc = right;
    }
    while ((pivot>=a[left]) && (loc!=left))
      left++;
    if (loc == left)
      flag = 1;
    else {
      a[loc] = a[left];
      right = loc-1;
      loc = left;
    }
  }
  a[loc] = pivot;
  return(loc);
}

void quick_sort(int a[], int beg, int end)
{
  int loc;

  if (beg < end) {
    loc = partition(a, beg, end);
    quick_sort(a, beg, loc-1);
    quick_sort(a, loc+1, end);
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
  quick_sort(a, 0, c-1);
  puts("\nArray after sort:");
  print_array(a, c);
  putchar('\n');
  return(0);
}

