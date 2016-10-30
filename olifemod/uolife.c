#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

/*  
 *  conway's game of life
 *  mod  @ryankeleti
 *  orig @theduckscientist
 */
const int rate=20000;

int main(int argc,char *argv[])
{
  char out='o';
  char bg=' ';
  if(argc==2){
    int n=atoi(argv[1]);
    switch(n){
      case 0:out='.';break;
      case 1:out='_';break;
      case 2:out='*';break;
      case 3:out='L';break;
      case 4:out='x';break;
      case 5:out=' ';bg='+';break;
      //case 5:out='█';break;
      default:out='#';break;
    }
  }
  int r;
  int a[2048];
  int n=~n+n;
  r=(int)&r;

  while((++n)^2048)
    n[a]=(r=(r*0x41C64E6D+12345)&0x7fffffff)&1024?1<<5:0;
  
  //while(usleep('d'<<'\n'),n+=~n){
  while(usleep(rate),n+=~n){

    while((++n)^8192){

      if(a[((n>>2)+2048+"\x01?@A"[n%4])%04000]&1<<5)
        *(a+(n>>2))=-~a[n>>2];

      if(a[((n>>2)+04000-"\x01?@A"[n%4])%2048]&1<<5)
        *(a+(n>>2))=-~a[n>>2];

      if(n%4==3)
        a[n>>2]|=a[n>>2]^'\"'&&a[n>>2]^'#'?((a[n>>2]^3)?0:1<<4):1<<4;
    }
    while((++n)^10240)

      if(putchar((a[n%2048]=a[n%2048]<<1&1<<5)?out:bg),!(63^n%0100))
        putchar(10);
  }
}

