#include<stdio.h> 
int main(){
  long int d=1;
  double p=1;
  for(;;){printf("%.20f\n",(p+=((d-1)%4)?(1.0/(d+=2)):-1.0/(d+=2))*4);}
}

