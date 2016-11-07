/* gnu libc | p 56 */

#include <stdio.h>
#include <mcheck.h>
#include <signal.h>

static void
enable(int sig)
{
  mtrace();
  signal(SIGUSR1, enable);
}

static void
disable(int sig)
{
  muntrace();
  signal(SIGUSR2, disable);
}

int
main(int argc, char *argv[])
{
  signal(SIGUSR1, enable);
  signal(SIGUSR2, disable);
}

