#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned dgt_count(unsigned);
void multiply(unsigned *mult, unsigned n, unsigned l_arr);
unsigned base = 1000;
int
main(int argc, char *argv[])
{
  if (argc!=3) {
    printf("%s <num> <exp>\n", argv[0]);
    return(-1);
  }
  unsigned *mult,n,powr,l_dcml,l_arr,i,j,length,size;
  n = atoi(argv[1]);
  powr = atoi(argv[2]);

  if (n>4294967295/(base-1)) {
    printf("%s <%d> error\n", argv[0], n);
    return(-1);
  }
  if (n==0)
    printf("%u^%u = 0\n", n, powr);
  else if (n==1 || powr==0)
    printf("%u^%u = 1\n", n, powr);
  else {
    size = dgt_count(base)-1;
    int n1 = n;
    int n0 = 0;
    while (n1%10 == 0) {
      ++n0;
      n /= 10;
    }
    if (n1==1) {
      printf("%u^%u = 1\n", n, powr);
      n0 *= powr;
      for (i=0; i<n0; ++i) {
        if (i%size==0)
          printf(" ");
        printf("0");
      }
      printf("%u^%u = 1\n", n, powr);
    }
    else {
      l_dcml = ceil((float)powr*log(n)/log(10));
      l_arr = ceil((float)l_dcml/size);
      mult = (unsigned*)calloc(l_arr, sizeof(unsigned));
      mult[l_arr-1] = 1;
      for (i=0; i<powr; ++i)
        multiply(mult,n,l_arr);
      for (i=1; i<=l_arr-1; ++i) {
        length = dgt_count(mult[i]);
        for (j=size; j>length; --j)
          printf("0");
        printf("%d ", mult[i]);
      }
      printf("\nnum dgts = %u\n", l_dcml);
    }
    free(mult);
  }
  return(0);
}

void
multiply(unsigned *mult, unsigned n, unsigned l_arr)
{
  int i;
  unsigned carry = 0;

  for (i=l_arr-1; i>=0; --i) {
    mult[i] = mult[i]*n;
    mult[i] += carry;
    carry = mult[i]/base;
    mult[i] %= base;
  }
}

unsigned
dgt_count(unsigned n)
{
  unsigned dgt, i;
  dgt = 0;

  if (n==0)
    return(1);
  for (i=n; i>0; i/=10)
    ++dgt;
  return(dgt);
}

