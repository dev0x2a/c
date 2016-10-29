/*
 * grade.c
 * compute letter grade from scores entered
 */
#include <stdio.h>
#include <stdlib.h>
int main(int argc,char*argv[])
{ int score,count,g;
  float sum,average;
  char grade;
  sum=0.0;
  count=0;
  do{
    printf("score(%d) =>  ",count+1);
    scanf("%d",&score);
    if(score>=0){
      ++count;
      sum+=score;
    }
  }while(score>=0);
  average=sum/count;
  g=(int)(average/100);
  switch(g){
    case 10:grade='A';break;
    case  9:grade='A';break;
    case  8:grade='B';break;
    case  7:grade='C';break;
    case  6:grade='D';break;
    default:grade='E';break;
  }
  printf("avg ==> %.2f, grade(%c)\n",average,grade);
  return(0);
}

