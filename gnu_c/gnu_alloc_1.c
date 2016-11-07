/* gnu libc | p 51-52 */

/* Prototypes for __malloc_hook, __free_hook */
#include <stdio.h>

/* Prototypes for our hooks */
static void my_init_hook(void);
static void *my_malloc_hook(size_t, const void *);
static void my_free_hook(void*, const void *);

static void
my_init_hook(void)
{
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
}

static void *
my_malloc_hook(size_t size, const void *caller)
{
  void *result;
  /* restore all old hooks */
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  /* call recursively */
  result = malloc(size);
  /* save underlying hooks */
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  /* printf might call malloc, so protect it too */
  printf("malloc (%u) returns %p\n", (unsigned int)size, result);
  /* restore our hooks */
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
  return(result);
}

static void
my_free_hook(void *ptr, const void *caller)
{
  /* restore all old hooks */
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;
  /* call recursively */
  free(ptr);
  /* save underlying hooks */
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  /* printf might call free, so protect it too */
  printf("freed pointer %p\n", ptr);
  /* restore our hooks */
  __malloc_hook = my_malloc_hook;
  __free_hook = my_free_hook;
}

int
main()
{
  my_init_hook();
}

