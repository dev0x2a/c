#include<stdio.h>
#include<stdlib.h>

int main(z,c,k,x,n)
int z,k,x,n;
char **c;
{
	return(
      !!z>=z ? !z>=z ? !!~z>=~z ? !~z>=~z ? !x ? !z : x%2 ? 
      x=main(z,c,k,x>>!!x,n),
      x=main(z-!z-!!z,c,x,x,n),
      x=main(z-!z-!!z,c,k,x,n),
      !(x-!z||z)
        ? n-1 : x : (x=main(z,c,k,x>>!!x,n),!(x-n+!z||z) 
        ? n-1 : main(z-!z-!!z,c,x,x,n)) :
        (k+x)%n : 
    main(z-z/z-z/z,c,k,x+x/x, main(0,c,k,x,z-z-z)+z+1 ? 1 : 
    printf("%d\t",z-z-z)+fflush(stdout)):
      main(z-z-z-z-z,c,z+z-z+z,z,0) : 
      main(~!!z-!!z,c,atoi(c[1]),1,atoi(c[0]));
}

