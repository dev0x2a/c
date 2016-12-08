#include <stdio.h>

int main()
{
  int i;
  char c;
  void *the_data;

  i = 6;
  c = 'a';

  the_data = &i;
  printf("\nthe_data points to the integer value %d\n", *(int*) the_data);

  /* "*(int*) the_data" is type casting. 
   * Type is used to caste a variable from one datatype to another datatype
   * to make it compatible to the lvalue.
   *
   * "lvalue"
   * something which is used to the left side of a statement and in which
   * we can assign some value. A constant cannot be an lvalue because we cannot
   * assign any value in contact.
   * For example --
   *    x = y
   * here x is "lvalue"
   * and  y is "rvalue"
   */

  the_data = &c;
  printf("the_data now points to the character %c\n", *(char*) the_data);

  return 0;
}

