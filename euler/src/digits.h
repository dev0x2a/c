#ifndef DIGITS_H
#define DIGITS_H

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

#endif 

