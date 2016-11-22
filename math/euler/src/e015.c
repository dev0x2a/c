#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("%s <num>\n", argv[0]);
    return(-1);
  }
  int i, j, n=atoi(argv[1])+1;
  unsigned long long a[n][n];

  for(i=0; i<n; ++i){
    a[i][0]=1;
    a[0][i]=1;
  }
  for(i=1; i<n; ++i){
    for(j=1; j<n; ++j){
      a[i][j]=a[i-1][j]+a[i][j-1];
    }
  }
  printf("%lld\n", a[n-1][n-1]);
  return(0);
}

