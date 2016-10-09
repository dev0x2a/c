#include <stdio.h>

int
main(int argc, char *argv[])
{
  int hashval=0;
  /*  PJW hash function 
   *  @ Aho, Sethi, Ullman
   *  */
  while (cp < bound)
  {
    unsigned int overflow;
    hashval=(hashval<<4) + *cp++;
    if ((overflow = hashval & (((unsigned long)0xF)<<28)) != 0)
      hashval ^= overflow | (overflow>>24);
  }
  hashval %= SR_HASHSIZE;   /*  choose start bucket */
  /*
   * look through each table, in turn, for the name.
   * if fail => save string, enter string's pointer,
   * and return it.
   */
  for (hp = &st_ihash; ; hp = hp->st_hnext) {
    int probeval = hashval+0; /*  next probe value  */
  }
}

