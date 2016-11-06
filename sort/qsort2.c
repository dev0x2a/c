/* qsort2.c: sort v[left]...v[right] into increasing order */
#include<stdio.h>
#define A 10
/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *s,char *t)
{
  for(; *s==*t; ++s,++t)
    if(*s=='\0')
      return(0);
  return(*s-*t);
}

void qsort(char *v[],int left,int right)
{
  int i,last;
  void swap(char *v[],int i,int j);

  if(left>=right)/*do nothing if array contains*/
    return;      /*fewer than 2 elements       */
  swap(v,left,(left+right)/2);/*move partition */
  last=left;                  /*elem to v[0]   */
  for(i=left+1; i<=right; ++i)      /*partition*/
    if(strcmp(v[i],v[left])<0)
      swap(v,++last,i);
  swap(v,left,last);   /*restore partition elem*/
  qsort(v,left,last-1);
  qsort(v,last+1,right);
}
/* swap: interchange v[i] and v[j] */
void swap(char *v[],int i,int j)
{
  char *tmp;
  tmp=v[i];
  v[i]=v[j];
  v[j]=tmp;
}

int main(int argc,char *argv[])
{
  int k;
  qsort(argv,0,A);
  //for(k=0; k<A; ++k)
  //  printf("%c ",argv[k]);
  putchar(10);
  return(0);
}

