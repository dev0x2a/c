#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int power(int b,unsigned int e)
{
  int i,res=1;
  for(i=0; i<e; ++i) res*=b;
  return(res);
}

int main(void)
{ int s1,s2,ds;
  for(int i=1; i<=100; ++i)s1+=power(i,2);
  for (int j=1; j<=100; ++j)s2+=j;
  s2=power(s2,2);
  ds=s2-s1;
  printf("%d\n%d\n%d\n",s1,s2,ds);
  return(0);
}

