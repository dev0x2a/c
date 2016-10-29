#include<stdio.h>
int turn;
int main(void){
  do{
    if(!turn++)puts("1: P-K4");
    else{
      puts("I resign");
      return(0);
    }
  }while(1);
}

