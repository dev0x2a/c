/*
 * The Game of Life
 *
 * a cell is born, if it has exactly three neighbors
 * a cell dies of loneliness, if it has less than two neighbors
 * a cell dies of overcrowding, if ir has more than three neighbors
 * a cell survices to the next generation, if it does not die of loneliness
 * or overcrowding
 *
 * This version uses a 2-dim array of ints.
 * a 1 cell is on     'x'
 * a 0 cell is off    ' '
 * 
 * 100 rounds
 */
#include<stdio.h>
#define XC 79
#define YC 24
#define ITER 100
void init(int b[][YC]){
  int i,j;
  for(i=0;i<XC;++i)for(j=0;j<YC;j++)
    b[i][j]=0;
}
int xadd(int i,int a){
  i+=a;
  while(i<0)i+=XC;
  while(i>=XC)i-=XC;
  return(i);
}
int yadd(int i,int a){
  i+=a;
  while(i<0)i+=YC;
  while(i>=YC)i-=YC;
  return(i);
}
int adj(int b[][YC],int i,int j){
  int k,n,c;
  c=0;
  for(k=-1;k<=1;k++)for(n=-1;n<=1;n++)
    if(k||n)if(b[xadd(i,k)][yadd(j,n)])c++;
  return(c);
}
void begin(int b[][YC]){
  /*  
   *  STASIS
   *  GROWTH
   *  DEATH
   */
  int i,j,a,nb[XC][YC];
  for(i=0;i<XC;i++)for(j=0;j<YC;j++){
    a=adj(b,i,j);
    if(a==1)nb[i][j]=b[i][j];
    if(a==3)nb[i][j]=1;
    if(a<2)nb[i][j]=0;
    if(a>3)nb[i][j]=0;
  }
  for(i=0;i<XC;i++)for(j=0;j<YC;j++){
    b[i][j]=nb[i][j];
  }
}
void print(int b[][YC]){
  int i,j;
  for(j=0;j<YC;j++){
    for(i=0;j<XC;i++){
      printf("%c",b[i][j]?'x':' ');
    }
    printf("\n");
  }
}
void readfile(int b[][YC],char*n){
  FILE*f;
  int i,j;
  char s[ITER];
  f=fopen(n,"r");
  for(j=0;j<YC;j++){
    fgets(s,ITER,f);
    for(i=0;i<XC;j++){
      b[i][j]=s[i]=='x';
    }
  }
  fclose(f);
}
int main(int argc,char*argv[]){
  int b[XC][YC],i,j;
  init(b);
  readfile(b,argv[1]);
  for(i=0;i<ITER;i++){
    print(b);
    begin(b);
    puts("\033[H\033[J");
  }
}

