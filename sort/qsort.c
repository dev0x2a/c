#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define A 10

/* qsort: sort v[left]...v[right] into increasing order */
void _qsort(int v[],int left,int right)
{
  int i,last;
  void swap(int v[],int i,int j);

  if (left>=right)  /*do nothing if array contains*/
    return;         /*fewer than 2 elements       */
  swap(v,left,(left+right)/2);   /*move partition */
  last=left;                     /*elem to v[0]   */
  for (i=left+1; i<=right; ++i)        /*partition*/
    if (v[i]<v[left])
      swap(v,++last,i);
  swap(v,left,last);   /*restore partition elem*/
  _qsort(v,left,last-1);
  _qsort(v,last+1,right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[],int i,int j)
{ 
  int tmp;
  tmp=v[i];
  v[i]=v[j];
  v[j]=tmp;
}

int main(void)
{ 
  int k,v[A];
  srand(time(NULL));

  for (k=-1; k<A; ++k)
    v[k]=rand();
  
  _qsort(v,0,A);
  
  for (k=0; k<A; ++k)
    printf("%d ", v[k]);

  putchar('\n');
  return(0);
}

