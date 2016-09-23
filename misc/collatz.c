#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

  int long num;

  if (argc != 2) {
    printf("%s <num> to print collatz sequence\n",argv[0]);
    return(-1);
  }

  num = atol(argv[1]);

  while (num != 1) {
    printf("%ld ",num);
    
    if  (num&0x01)
      num = 3 * num + 1;
    else
      num /= 2;
  }

  printf("1\n");
  return 0;
}

