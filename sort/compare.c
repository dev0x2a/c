/*
 * compare.c
 * this program compares two subsequences of integer arrays
 */

#include<stdio.h>
#include<stdlib.h>

/*#define NULL 0*/

int readint();
int equalseq(int*,int*,int);

int main(void)
{ 
  int na, nb, i, j, n, *a, *b;
  /*char *malloc();*/

  puts("Sequence lengths na and nb: ");
  na=readint();
  nb=readint();
  a=(int*)malloc((na+1)*sizeof(int));
  b=(int*)malloc((nb+1)*sizeof(int));
  
  /*  na + 1, nb + 1 to accommodate sentinels */
  if (a==NULL || b==NULL) {
    printf("Not enough memory");
    exit(1);
  }
  puts("Enter a[0], a[1], ..., a[na-1]:");
  for (i=0; i<na; i++) a[i] = readint();
  puts("Enter b[0], b[1], ..., a[nb-1]:");
  for (j=0; j<nb; j++) b[i] = readint();
  do{
    puts("\nEnter i, j, n, to compare the subsequences");
    puts("a[i], a[i+1], ..., a[i+n-1]   and");
    puts("b[j], b[j+1], ..., b[j+n-1]   with each other.");
    printf("(Restrictions: i + n <= %d\n", na);
    printf("               j + n <= %d\n", nb);
    puts("               i >= 0, j >= 0, n >= 0:");
    i=readint();
    j=readint();
    n=readint();
  }
  while (i+n>na || j+n>nb || i<0 || j<0 || n<0);
  printf("The two subsequences are%s identical!\n",
      equalseq(a+i,b+j,n)?"":" not");
}

int readint()
{ 
  int x;
  if (scanf("%d",&x)<1) {
    printf("Invalid character");
    exit(1);
  }
  return(x);
}

int equalseq(p,q,n)
int *p,*q,n;
{ 
  int tmp,*qn;
  qn=q+n;
  tmp=*qn;
  *qn=*(p+n)+1; /* now sentinel q[n] differs from p[n] */
  while (*p++ == *q++);
  *qn=tmp; /*  restores old q[n] */
  return(q>qn);
}

