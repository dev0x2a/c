#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int n,p,lim;
  
  if (argc < 4) {
    puts("\nn (mod p), enter n,p,lim");
    scanf("%d %d %d", &n,&p,&lim);
  } else {
    n = atoi(argv[1]);
    p = atoi(argv[2]);
    lim = atoi(argv[3]);
  }

  for (; n<=lim; ++n)
    printf("%2d (mod %2d) = %2d\n", n,p,n%p);
  return(0);
}

