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
const char *str="\x01?@A";

int main(int argc,char *argv[])
{
  char out='o';
  char bg=' ';
  int r;
  int a[2048];
  int n=~n+n;
  r=(int)&r;
  if(argc==2){
    out = argv[1][0];
    /*█*/
  }

  while((++n)^2048){
    n[a]=(r=(r*0x41C64E6D+12345)&0x7fffffff)&1024?1<<5:0;
  }

  //while(usleep('d'<<'\n'),n+=~n){
  while(usleep(rate),n+=~n){

    while((++n)^8192){

      if(a[((n>>2)+2048+str[n%4])%04000]&1<<5){
        a[n>>2]=-~a[n>>2];
      }

      if(a[((n>>2)+04000-str[n%4])%2048]&1<<5){
        a[n>>2]=-~a[n>>2];
      }

      if(n%4==3){
        a[n>>2]|=a[n>>2]^'\"'&&a[n>>2]^'#'?((a[n>>2]^3)?0:1<<4):1<<4;
      }
    }
    while((++n)^10240){

      if(putchar((a[n%2048]=a[n%2048]<<1&1<<5)?out:bg),!(63^n%0100)){
        putchar(10);
      }
    }
  }
}

