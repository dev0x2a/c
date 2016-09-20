#include <stdio.h>

int main()
{
  char *ptr;
  char arrayChars[8] = {'F','r','i','e','n','d','s','\0'};

  ptr = arrayChars;

  printf("\nthe array reads %s.\n", arrayChars);
  printf("let's change it....\n");

  *ptr = 'f';   /*  ptr points to the first element */

  printf("now it reads %s.\n", arrayChars);
  printf("the 3rd character of the array is %c.\n", *(ptr+=2));
  printf("let's change it again....\n");
  
  *(ptr - 1) = ' ';

  printf("now it reads %s.\n\n", arrayChars);
  return 0;
}

