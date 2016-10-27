/*  COMPARE.C: This program compares two subsequences of
 *              integer arrays
 */
#define NULL 0
int readint();
int equalseq(p,q,n);
int main(){
  int na,nb,i,j,n,*a,*b;
  char *malloc();
  printf("Seq lengths na & nb: ");
  na=readint();
  nb=readint();
  a=(int*)malloc((na+1)*sizeof(int));
  b=(int*)malloc((nb+1)*sizeof(int));
  /*  na+1, nb+1 to accommodate sentinels */
  if (a==NULL||b==NULL){
    printf("Not enough memory\n");
    exit(1);
  }
  printf("Enter a[0], a[1], ..., a[na-1]:\n");
  for (i=0; i<na; i++) a[i]=readint();
  printf("Enter b[0], b[1], ..., b[nb-1]:\n");
  for (j=0; j<nb; j++) b[i]=readint();
  do{
    printf("\nEnter i, j, n, to compare the subseqs\n");
    printf("a[i], a[i+1], ..., a[i+n-1]   and\n");
    printf("b[j], b[j+1], ..., b[j+n-1]   with each other.\n");
    printf("(Restrictions: i+n <= %d\n", na);
    printf("(              j+n <= %d\n", nb);
    printf("(              i>=0, j>=0, n>=0):\n");
    i=readint();
    j=readint();
    n=readint();
  } while (i+n>na || j+n>nb || i<0 || j<0 || n<0);
  printf("The two sequences are%s identical.\n",
      equalseq(a+i, b+j, n)?"":" not");
}

int readint()
{
  int x;
  if (scanf("%d", &x)<1){
    printf("Invalid char\n");
    exit(1);
  }
  return(x);
}

int equalseq(p, q, n) int *p, *q, n;
{
  int tmp, *qn;
  qn=q+n;
  tmp=*qn;
  *qn=*(p+n)+1;
  /*  now sentinel q[n] differs from p[n] */
  while (*p++==*q++) ;
  *qn=tmp;  /*  restore old q[n]  */
  return(q>qn);
}

