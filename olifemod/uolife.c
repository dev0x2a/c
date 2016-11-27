#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* for usleep() */

/*  
 *  conway's game of life
 *  mod  @ryankeleti
 *  orig @theduckscientist
 */

/*rate of output*/
const int rate=20000; 
const char *str="\x01?@A";

int main(int argc,char *argv[])
{
  char out = 'o'; /* foreground  */
  char bkg = ' '; /* background  */
  int s = (int)&s;/* seed        */
  int a[2048];    /* holds cells */
  int n = ~n+n;   /* index       */
  if (argc>1)     /* input fg    */
    out = argv[1][0];
                   /* █<--lets see if I can implement
                    * this later*/
  while ((++n)^2048)
    n[a] = (s=(s*0x41C64E6D+12345)&0x7fffffff)&1024?1<<5:0;
  
  /*while(usleep('d'<<'\n'),n+=~n){*/
  while (usleep(rate),n+=~n) {
    while ((++n)^8192) {
      
      if (a[((n>>2)+2048+str[n%4])%04000]&1<<5)
        a[n>>2] = -~a[n>>2];

      if (a[((n>>2)+04000-str[n%4])%2048]&1<<5)
        a[n>>2] = -~a[n>>2];

      if (n%4 == 3)
        a[n>>2] |= a[n>>2]^'\"'&&a[n>>2]^'#'?((a[n>>2]^3)?0:1<<4):1<<4;
    }
    while ((++n)^10240) {
      if (putchar((a[n%2048]=a[n%2048]<<1&1<<5)?out:bkg),!(63^n%0100))
        putchar('\n');
    }
  }
  exit(0);
}

