#include<stdint.h>
#include<stdlib.h>
void*(*bnew(void))[4]{return(calloc(sizeof(void*[4]),1));}
void bdel(void*(*n)[4]){if(n)bdel((*n)[0]),bdel((*n)[1]),free(n);}
void*(*bput(void*(*n)[4],int k,int v))[4]{
  void*(**m)[4]=(void*(**)[4])&((*n)[!!(k<(uintptr_t)((*n)[2]))]);
  return(*m?bput(*m,k,v):(*m=bnew(),(**m)[2]=(void*)(uintptr_t)k,(**m)[3]=(void*)(uintptr_t)v),*m);}
void*(*bget(void*(*n)[4],int k))[4]{
  return(n?(k<(uintptr_t)(*n)[2])?bget((*n)[1],k):(k==(uintptr_t)(*n)[2])?n:bget((*n)[0],k):0);}
/*******************************/
#include<stdio.h>
int main(void)
{ void*(*n)[4]=bnew();
  /* examples */
  bput(n,100,100);
  bput(n,200,500);
  bput(n,10,35);
  bput(n,75,500);
  bput(n,6000,1337);
  void*(*a)[4]=bget(n,75);
  void*(*b)[4]=bget(n,6000);
  printf("%d\n",(int)(uintptr_t)(*a)[3]);
  printf("%d\n",(int)(uintptr_t)(*b)[3]);
  void*(*c)[4]=bget(n,42);
  printf("search for 42 shound be null: %p\n",c);
  bdel(n);
  return(0);
}

