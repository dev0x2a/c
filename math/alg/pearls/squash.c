/*
 * squash.c: print anagram classes on a single line
 * (c)1999 Lucent Tech
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORDMAX 100

int main(void)
{
  char word[WORDMAX], sig[WORDMAX], oldsig[WORDMAX];
  int linenum = 0;
  
  strcpy(oldsig, "");
  while (scanf("%s %s", sig,word) != EOF) {
    if (strcmp(oldsig, sig)!=0 && linenum>0)
      putchar('\n');
    strcpy(oldsig, sig);
    linenum++;
    printf("%s ", word);
  }
  putchar('\n');
  return 0;
}

