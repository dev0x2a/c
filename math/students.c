#include <stdio.h>
#include <stdlib.h>
int main(int argc,char*argv[])
{
  if (argc!=4){
    printf("%s <name> <roll> <age>\n",argv[0]);
    return(-1);
  }
  struct student{
    char*name;
    int roll;
    int age;
  };
  //struct student s1 = {"Ella", 11, 17};
  struct student s1;
  s1.name=argv[1];
  s1.roll=atoi(argv[2]);
  s1.age=atoi(argv[3]);
  printf("name: %s\n",s1.name);
  printf("roll: %d\n",s1.roll);
  printf("age:  %d\n",s1.age);
  return(0);
}

