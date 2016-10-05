/*
 * catchblk.c
 * catches block comments with c syntax
 *
 * block comments must be formated as such:
 *
 * / *
 *   * comment line 1
 *   * comment line 2 
 *   * /
 *
 * with no spaces between '/' and '*';
 * an asterix '*' on each line is required;
 *
 * be careful when running on other systems 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROGRAM_NAME "catchblk"

void
usage(void);

int
main(int argc, char *argv[])
{
  const char *input_file;
  const char *args[] = {input_file ,"| grep '^.\\*'"};
  const char *binary_name = "cat";
  char myoutput_array[5000];
  int argcount = 2;
  int help_check, switchcase;

  printf("catch:\t");
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
             return(-1);
             break;
  }
  return 0;
}

void
usage(void)
{
  fprintf(stdout, "\n\
        usage: %s: \n\
        \t  catch: [input_file]\n\
        ", PROGRAM_NAME);
}

#if 0
  #include <sys/wait.h>
  #include <sys/types.h>
  static int exec_prog(const char **argv);
  if (argc != 2)
    return (-1);
  const char *my_argv[64] = {"cat", "*", "|", "grep", "'^.\\*'",  NULL};
  int rc = exec_prog(my_argv); 

static int exec_prog(const char **argv)
{
  pid_t my_pid;
  int status, timeout;  /*  unused ifdef WAIT_FOR_COMPLETION  */

  if (0 == (my_pid = fork())) {
    if (-1 == execve(argv[0], (char **)argv, NULL)) {
      perror("child process execve failed [%m]");
      return (-1);
    }
  }

#ifdef WAIT_FOR_COMPLETION
  timeout = 1000;

  while (0 == waitpid(my_pid, &status, WNOHANG)) {
    if (--timeout < 0) {
      perror("timeout");
      return (-1);
    }
    sleep(1);
  }
  printf("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n",
      argv[0], WEXITSTATUS(status), WIFEXITED(status), status);
  if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
    perror("%s failed, halt system");
    return (-1);
  }
#endif
  return 0;
}
#endif

