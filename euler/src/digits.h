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
      while (dgt_tmp > 0) {
        dgt_arr[dgt_m] = dgt_tmp%10;
        dgt_tmp /= 10;
        ++dgt_m;
      }
    }
    for (dgt_i=dgt_m-1; dgt_i>=0; --dgt_i)
      printf("%d", dgt_arr[dgt_i]);
  }
  printf("\n");
  return 0;
}

int max = 5000;
void
factorial(int arr[], int n)
{
  //factorial in array
  if (!n) 
    return;
  int carry = 0;
  int i = max-1;
  for (i=max-1; i>=0; --i) {
    arr[i] = (arr[i] * n) + carry;
    carry = arr[i]/10;
    arr[i] %= 10;
  }
  factorial(arr,n-1);
}

void
display(int arr[])
{
  // to print array
  int ctr = 0;
  int i=0;
  for (i=0; i<max; i++){
    if (!ctr && arr[i])      
      ctr = 1;
    if(ctr)
      printf("%d", arr[i]);
  }
}

int
dgt_main()
{
  int *arr = calloc(max, sizeof(int));
  arr[max-1] = 1;
  int num = 100;
  printf("factorial of  %d is: ",num);
  factorial(arr,num);
  display(arr);
  free(arr);
  return 0;
}

#endif 

