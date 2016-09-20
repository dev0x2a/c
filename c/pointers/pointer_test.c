#include <stdio.h>

int main()
{
  int my_variable = 6, other_variable = 10;
  int *my_pointer;

  printf("\n\n\taddress of my_variable        %p\n", &my_variable);
  printf("\taddress of other_variable     %p\n", &other_variable);

  my_pointer = &my_variable;

  printf("\n\nafter \"my_pointer = &my_variable\":\n\n");
  printf("\tthe value of my_pointer is    %p\n", my_pointer);
  printf("\tthe value at that address is  %d\n", *my_pointer);

  my_pointer = &other_variable;

  printf("\n\nafter \"my_pointer = &other_variable\":\n\n");
  printf("\tthe value of my_pointer is    %p\n", my_pointer);
  printf("\tthe value at that address is  %d\n\n", *my_pointer);

  return 0;
}

