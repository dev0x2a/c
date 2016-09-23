/*
 * add.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROGRAM_NAME "add"
#define COMMAND_NAME "git"

void usage(void);
 
int main(int argc, char **argv)
{
  const char *input_file;
  const char *args[] = {"add", input_file};
  const char *binary_name = "git";
  char myoutput_array[5000];
  int argcount = 2;
  int help_check, switchcase;

  printf("%s %s:\t", COMMAND_NAME, PROGRAM_NAME);
  scanf("%s", input_file);
  help_check = strcmp(input_file, "help");

  if (help_check == 0) switchcase = 1;
  else if (help_check != 0) switchcase = 2;
  
  switch(switchcase)
  {
    case 1: usage();
            return 0;
            break;

    case 2: sprintf(myoutput_array, "%s", binary_name);
            for (int i = 0; i < argcount; ++i) {
              strcat(myoutput_array, " ");
              strcat(myoutput_array, args[i]);
            }
            printf("%s\n\n", myoutput_array);
            sleep(1);
            system(myoutput_array);
            break;

    default: usage();
             return (-1);
             break;
  }
  return 0;
}

void usage(void)
{
  fprintf(stdout, "\n\
        usage: %s: \n\
        \t  %s %s: [input_file]\n\
        ", PROGRAM_NAME, COMMAND_NAME, PROGRAM_NAME);
}

