/* gnu libc | pg 865-866 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

int main(void)
{
  /* hashed form of "GNU libc manual" */
  const char *const pass = "$1$/iSaq7rB$EoUw5jJPPvAPECNaaWzMK/";

  char *result;
  int ok;

  /* read user's password and encrypt it,
   passing the encrypted password as salt */
  result = crypt(getpass("Password: "), pass);

  /* test result */
  ok = strcmp(result, pass) == 0;

  puts(ok ? "Access granted." : "Access denied.");

  return(ok ? 0 : 1);
}

