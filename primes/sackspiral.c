/* 
 *
 * r = sqrt n } every non-negative real number n
 * theta = sqrt n }
 * theta in rotations, not radians
 * one rotation=360 deg
 *
 * x = r*cos(2*pi*theta)
 * y = r*sin(2*pi*theta)
 */
#include <stdio.h>
#include <stdlib.h>

/* not actual code, just testing */
int main(int argc, char *argv[])
{
  int ip,a[10][10],i=0,j=0,k=1,num,size;
  ip=atoi(argv[1]);
  size=ip;
  while(1) {
    for(num=0;num<ip;num++)   //moving right
    a[i][j++]=k++;
    ip--;
    if(ip==0) break;
    i++; j--;                              //moving down
    for(num=0;num<ip;num++)
    a[i++][j]=k++;
    i--; j--;                               //moving left
    for(num=0;num<ip;num++)
      a[i][j--]=k++;
    ip--;
    if(ip==0) break;
    i--; j++;                             //moving up
    for(num=0;num<ip;num++)
      a[i--][j]=k++;
    i++; j++;
  }
  for(i=0;i<size;i++) {             //printing output
    printf("\n");
    for(j=0;j<size;j++)
      printf("\t%d", a[i][j]);
  }
  printf("\n");
  return 0;
}

