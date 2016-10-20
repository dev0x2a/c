#ifndef DIGITS_H
#define DIGITS_H

#include <stdlib.h>

int
dgt(int dgt_t, int dgt_n)
{
  int dgt_arr[200];
  int dgt_i, dgt_j, dgt_tmp, dgt_m, dgt_x;

  while (--dgt_t) {
    dgt_arr[0] = 1;
    dgt_m = 1;
    dgt_tmp = 0;
    for (dgt_i=1; dgt_i<=dgt_n; ++dgt_i) {
      for (dgt_j=0; dgt_j<dgt_m; ++dgt_j) {
        dgt_x = dgt_arr[dgt_j]*dgt_i+dgt_tmp;
        dgt_arr[dgt_j] = dgt_x%10;
        dgt_tmp = dgt_x/10;
      }
      while (dgt_tmp>0) {
        dgt_arr[dgt_m] = dgt_tmp%10;
        dgt_tmp /= 10;
        ++dgt_m;
      }
    }
    for (dgt_i=dgt_m-1; dgt_i>=0; --dgt_i)
      printf("%d", dgt_arr[dgt_i]);
  }
  printf("\n");
  return(0);
}

int dgt_max = 5000;
void
dgt_factorial(int arr[], int n)
{
  /*  factorial in array  */
  if (!n) 
    return;
  int carry = 0;
  for (int i=dgt_max-1; i>=0; --i) {
    arr[i] = (arr[i]*n)+carry;
    carry = arr[i]/10;
    arr[i] %= 10;
  }
  dgt_factorial(arr, n-1);
}

void
dgt_display(int arr[])
{
  /*  to print array  */
  int c = 0;
  int i = 0;
  for (i=0; i<dgt_max; ++i){
    if (!c && arr[i])      
      c = 1;
    if (c)
      printf("%d", arr[i]);
  }
}

int
dgt_main(int num)
{
  int *arr = calloc(dgt_max, sizeof(int));
  arr[dgt_max-1] = 1;
  //int num = 100;
  //printf("factorial of  %d is: ", num);
  dgt_factorial(arr, num);
  dgt_display(arr);
  free(arr);
  return 0;
}

#endif 

