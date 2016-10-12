#ifndef DIGITS_H
#define DIGITS_H

int
dgt(int dgt_t, int dgt_n)
{
  int dgt_arr[1000];
  int dgt_i, dgt_j, dgt_tmp, dgt_m, dgt_x;

  while (--dgt_t) {
    dgt_arr[0] = 1;
    dgt_m = 1;
    dgt_i = 2;
    int dgt_k = 1;
    dgt_tmp = 0;
    while (dgt_k <= dgt_n) {
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
      ++dgt_k;
    }
    for (dgt_i=dgt_m-1; dgt_i>=0; --dgt_i)
      printf("%d", dgt_arr[dgt_i]);
    printf("\n");
  }
  return 0;
}

#endif 

