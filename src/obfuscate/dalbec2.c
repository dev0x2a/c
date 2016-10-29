#include<stdio.h>
#include<stdlib.h>
int main(x,c,v,k,n)
int x,v,k,n;
char **c;
{
	return(
      !!x>=x?!x>=x?!!~x>=~x?!~x>=~x?!k?!x:k%2?
      k=main(x,c,v,k>>!!k,n),
      k=main(x-!x-!!x,c,k,k,n),
      k=main(x-!x-!!x,c,v,k,n),
      !(k-!x||x)?n-1:k
      :(k=main(x,c,v,k>>!!k,n),
        !(k-n+!x||x)?n-1:main(x-!x-!!x,c,k,k,n))
      :(v+k)%n
      :main(x-x/x-x/x,c,v,k+k/k,
        main(0,c,v,k,x-x-x)+x+1?1:printf("%d\t",x-x-x)+fflush(stdout))
      :main(x-x-x-x-x,c,x+x-x+x,x,0)
      :main(~!!x-!!x,c,atoi(c[1]),1,atoi(c[0])));
}

