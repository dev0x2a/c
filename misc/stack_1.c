void
unwind(size_t depth, char *addr, size_t len)
{
  size_t i;
  struct a { struct a *next; } *ebp;
  ptrdiff_t offset;

#if __x86_64__
  asm volatile("movq      %%rbp, %0;" : "=r" (ebp));
#else
  asm volatile("movl      %%ebp, %0;" : "=r" (ebp));
#endif

  /*  enter the first stack frame and get the offset of the variable  */
  ebp = ebp->next;
  offset = addr - (char *)ebp;

  for (i = 0; i < depth; i++)
    ebp = ebp->next;

  for (i = 0; i < len; i++)
    addr[i] = (((char *)ebp + offset))[i];
}

#define UNWIND(d, v) unwind(d, (char *)&v, sizeof(v))

