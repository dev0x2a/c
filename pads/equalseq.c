#include<stdio.h>
int equalseq(p, q, n) int *p, *q, n;
{ int tmp, *qn;
  qn=q+n;
  tmp=*qn;
  *qn=*(p+n)+1;
  /*  now sentinel q[n] differs from p[n] */
  while (*p++==*q++) ;
  *qn=tmp;  /*  restore old q[n]  */
  return(q>qn);
}
int
main(){int a[3]={1,2,3}, b[3]={1,2,3};printf("%d\n",equalseq(a,b,2));};

