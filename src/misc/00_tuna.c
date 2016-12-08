#include <stdio.h>
#include <time.h>

int
main(int argc, char *argv[])
{
  time_t tuna = 0x7FFFFFFF;
  
  printf("time_t tuna wrap: %s\n", asctime(gmtime(&tuna)));
  return 0;
}

