#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "mlib.c"

#if 0
int table[489720];
int lookup(unsigned char *key)
{
  int index = hash(key);
  return table[index];
}

struct entry {
  unsigned char *key;
  int value;
  struct entry *next;
} *table[1<<20];

int lookup(unsigned char *key){
  int index = hash(key) % (1<<20);
  
  for (struct entry *e=table[index]; e!=NULL; e=e->next) {
    if (!strcmp(key, e->key))
      return e->value;
  }
  // not found
}

int hashstring(const char *s)
{
  /* take the result % hash table size */
  int key = 0;
  while (*s) {
    key = key*37 + *s++;
  }
  return key;
}
#endif

struct nlist { /* table entry */
  struct nlist *next; /* next entry in chain */
  char *name; /* defined name */
  char *defn; /* replacement name */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */


unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval=0; *s != '\0'; ++s)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
  struct nlist *np;

  /* for (ptr=head; ptr!=NULL; ptr=ptr->next) ... */
  for (np=hashtab[hash(s)]; np != NULL; np=np->next)
    if (strcmp(s, np->name) == 0)
      return np; /* found */
  return NULL;   /* not found */
}

/* put (name,defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;

  if ((np=lookup(name)) == NULL) { /* not found */
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = mstrdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else /* already there */
    free((void *) np->defn); /* free prev defn */
  if ((np->defn = mstrdup(defn)) == NULL)
    return NULL;
  return np;
}

