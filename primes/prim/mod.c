#include <stdio.h>
#include <stdlib.h>

int mod2[2] = {0,1};
int mod3[3] = {0,1,2}; 
int mod4[4] = {0,1,2,3}; 
int mod5[5] = {0,1,2,3,4}; 
int mod6[6] = {0,1,2,3,4,5}; 
int mod7[7] = {0,1,2,3,4,5,6}; 
int mod8[8] = {0,1,2,3,4,5,6,7}; 
int mod9[9] = {0,1,2,3,4,5,6,7,8}; 
int mod10[10] = {0,1,2,3,4,5,6,7,8,9}; 


int main(int argc, char *argv[])
{
  int n, p, lim;
  
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

