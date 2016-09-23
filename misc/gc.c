/*
 * http://web.engr.illinois.edu/~maplant2/gc.html
 */

typedef struct header {
  unsigned int size;
  struct block *next;
} header_t;

/*  scan the free list, look for a place to put the block */
static void
add_to_free_list(header_t *bp)
{
  header_t *p;
  
  for (p = freep; !(bp > p && bp < p->next); p = p->next)
    if ( p >= p->next && (bp > p || bp < p->next))
      break;
  
  if (bp + bp->size == p->next) {
    bp->size += p->next->size;
    bp->next = p->next->next;
  } else
      bp ->next = p->next;
  
  if (p + p->size == bp) {
    p->size += bp->size;
    p->next = bp-> next;
  } else
      p->next = bp;
  
  freep = p;
}

#define MIN_ALLOC_SIZE 4096

/*  request more memory from the kernel */
static header_t *
morecore(size_t num_units)
{
  void *vp;
  header_t *up;
  
  if (num_units < MIN_ALLOC_SIZE)
    num_units = MIN_ALLOC_SIZE / sizeof(header_t);
  
  if ((vp = sbrk(num_units * sizeof(header_t))) == (void *) -1)
    return NULL;
  
  up = (header_t *) vp;
  up->size = num_units;
  add_to_free_list (up);
  return freep;
}

static header_t base; /*  zero sized block to start */
static header_t *usedp, *freep;

/*  find a chunk from the free list and put it in the used list */
void *
GC_malloc(size_t alloc_size)
{
  size_t num_units;
  header_t *p, *prevp;

  num_units = (alloc_size + sizeof(header_t) - 1) / sizeof(header_t) + 1;
  prevp = freep;

  for (p = prevp->next;; prevp = p, p = p->next) {
    if (p->size >= num_units) { /*  big enough  */
      if (p->size == num_units) /*  exact size  */
        prevp->next = p->next;
      else {
        p->size -= num_units;
        p += p->size;
        p->size = num_units;
      }

      freep = prevp;

      /*  add to p to the used list */
      if (usedp == NULL)
        usedp = p->next = p;
      else {
        p->next = used->next;
        usedp->next = p;
      }

      return (void *) (p + 1);
    }
    if (p == freep) { /*  not enough memory */
      p = morecore(num_units);
      if (p = NULL) /*  request for more memory failed  */
        return NULL;
    }
  }
}

#define UNTAG(p) (((unsigned int) (p)) & 0xfffffffc)

/*
 * scan a region of memory and mark any items in the used list
 */
static void
mark_from_region(unsigned int *sp, unsigned int *end)
{
  header_t *bp;

  for (; sp < end; sp++) {
    unsigned int v = *sp;
    bp = usedp;
    do {
      if (bp + 1 <= v &&
          bp + 1 + bp->size > v) {
              bp->next = ((unsigned int) bp->next) | 1;
              break;
      }
    } while ((bp = UNTAG(bp->next)) != usedp);
  }
}

/*
 * scan the marked blocks for references to other unmarked blocks
 */
static void
mark_from_heap(void)
{
  unsigned int *vp;
  header_t *bp, *up;

  for (bp = UNTAG(usedp->next); bp != usedp; bp = UNTAG(bp->next)) {
    if (!((unsigned int)bp->next & 1))
      continue;
    for (vp = (unsigned int *)(bp + 1);
         vp < (bp + bp->size + 1);
         vp++) {
      unsigned int v = *vp;
      up = UNTAG(bp->next);
      do {
        if (up != bp &&
            up + 1 <= v &&
            up + 1 + up->size > v) {
          up->next = ((unsigned int) up->next) | 1;
          break;
        }
      } while ((up = UNTAG(up->next)) != bp);
    }
  }
}

/*
 * find the absolute bottom of the stack, set up
 */
void
GC_init(void)
{
  static int initted;
  FILE *statfp;

  if (initted)
    return;

  initted = 1;

  statfp = fopen("/proc/self/stat", "r");
  assert(statfp != NULL);
  fscanf(statfp,
         "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
         "%*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld "
         "%*ld %*ld %*ld %*ld %*llu %*lu %*ld "
         "%*lu %*lu %*lu %lu", &stack_bottom);
  fclose(statfp);

  usedp = NULL;
  base.next = freep = &base;
  base.size = 0;
}

/*
 * mark blocks of memory in use and free those not in use
 */
void
GC_collect(void)
{
  header_t *p, *prevp, *tp;
  unsigned long stack_top;
  extern char end, etext; /*  provided by the linker  */

  if (usedp == NULL)
    return;

  /*  scan the BSS and initialized data segments  */
  mark_from_region(&etext, &end);

  /*  scan the stack  */
  asm volatile ("movl %%ebp, %0" : "=r" (stack_top));
  mark_from_region(stack_top, stack_bottom);

  /*  mark from the heap  */
  mark_from_heap();

  /*  and collect */
  for (prevp = usedp, p = UNTAG(usedp->next);; prevp = p, p = UNTAG(p->next)) {
  next_chunk:
    if (!((unsigned int)p->next & 1)) {
      /*
       * the chunk has not been marked
       * set it free
       */
      tp = p;
      p = UNTAG(p->next);
      add_to_free_list(tp);

      if (usedp == tp) {
        usedp = NULL;
        break;
      }

      prevp->next = (unsigned int)p | ((unsigned int) prevp->next & 1);
      goto next_chunk;
    }
    p->next = ((unsigned int) p->next) & ~1;
    if (p == usedp)
      break;
  }
}

