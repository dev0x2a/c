void
unwind_n(size_t depth, size_t n, ...)
{
  size_t i, j;
  va_list ap;
  struct a { struct a *next; } *ebp;
  struct {
    size_t size;
    char *addr;
    ptrdiff_t offset;
  } vars[n];

#if __x86_64__
  asm volatile("movq      %%rbp, %0;" : "=r" (ebp));
#else
  asm volatile("movl      %%ebp, %0;" : "=r" (ebp));
#endif

  ebp = ebp->next;

  va_start(ap, n);
  for (i = 0; i < n; i++) {
    vars[i].offset = (vars[i].addr = va_arg(ap, char *))
      - (char *)ebp;
    vars[i].size = va_arg(ap, size_t);
  }
  va_end(ap);

  for (i = 0; i < depth; i++)
    ebp = ebp->next;

  for (i = 0; i < n; i++)
    for (j = 0; j < vars[i].size; j++)
      vars[i].addr[j] = (((char *)ebp + vars[i].offset))[j];

}

