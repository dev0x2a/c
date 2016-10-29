/* TIME.C: compute time used by /non/recursive functions */
#include<time.h>
double recfac(n);
double itfac(n);
int main()
{ long int t0,t1;
  int n,k,i,dt;
  double f,refrac(),itfac();
  printf("n to compute n! ");
  scanf("%d",&n);
  printf("k times to compute %d! ",n);
  scanf("%d",&k);

  time(&t0);
  for(i=0;i<k;i++)f=recfac(n);
  time(&t1); dt=t1-t0;
  printf("Recursion %d! = %1.0f, time %ds\n",n,f,dt);

  time(&t0);
  for(i=0;i<k;i++)f=itfac(n);
  time(&t1); dt=t1-t0;
  printf("Iteration %d! = %1.0f, time %ds\n",n,f,dt);
}
double recfac(n)int n;
{ return(n>1?n*recfac(n-1):1.0);
}
double itfac(n)int n;
{ double product=1.0;
  while(n>1)product*=n--;
  return(product);
}

