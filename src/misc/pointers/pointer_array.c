#include <stdio.h>

int main()
{
  int *ptr;
  int arrayInts[10] = {1,2,3,4,5,6,7,8,9,10};

  ptr = arrayInts;  /*  ptr = &arrayInts[0]; works as well  */

  printf("pointer points to the first ");
  printf("array element, %d.\n", *ptr);
  printf("increment it....\n\n");

  ptr++;

  printf("now it should point to the next element,");
  printf(" which is %d.\n", *ptr);
  printf("but suppose we point to the 3rd: %d and 4th: %d.\n\n", *(ptr+1), *(ptr+2));

  ptr+=2;

  printf("now skip the next 4 to point to the 8th: %d.\n", *(ptr+=4));

  ptr--;

  printf("missed %d?\n", *(ptr++));
  printf("back to the 8th... %d.\n\n", *ptr);

  return 0;
}

