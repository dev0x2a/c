/*
 * http://web.engr.illinois.edu/~maplant2/gc.html
 */

typedef struct header {
  unsigned int size;
  struct block *next;
} header_t;

/*
 * scan the free list, look for a place to put the block
 */
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
