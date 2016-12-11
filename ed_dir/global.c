/* global.c: global command routines for the ed line editor */
#include "ed.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* list of lines active in a global command */
static const line_t **active_list = 0; 
static int active_size = 0;/* size (in bytes) of active_list */
static int active_len = 0; /* number of lines in active_list */
static int active_ptr = 0; /* active_list index ( non-decreasing ) */
static int active_ndx = 0; /* active_list index ( modulo active_last ) */

/* clear the global-active list */
void clear_active_list(void)
{
  disable_interrupts();
  if (active_list)
    free(active_list);
  active_list = 0;
  active_size = active_len = active_ptr = active_ndx = 0;
  enable_interrupts();
}

/* return the next global-active line node */
const line_t *next_active_node(void)
{
  while (active_ptr<active_len && !active_list[active_ptr])
    ++active_ptr;
  return (active_ptr<active_len) ? active_list[active_ptr++] : 0;
}

/* add a line node to the global-active list */
bool set_active_node(const line_t *const lp)
{
  disable_interrupts();
  if (!resize_line_buffer(&active_list, &active_size,
                          (active_len+1)*sizeof(line_t **))) {
    show_strerror(0, errno);
    set_error_msg("Memory exhausted");
    enable_interrupts();
    return false;
  }
  enable_interrupts();
  active_list[active_len++] = lp;
  return true;
}

/* remove a range of lines from the global-active list */
void unset_active_nodes(const line_t *bp, const line_t *const ep)
{
  while (bp != ep) {
    int i;
    for (i=0; i<active_len; ++i) {
      if (++active_ndx >= active_len)
        active_ndx = 0;
      if (active_list[active_ndx] == bp) {
        active_list[active_ndx] = 0;
        break;
      }
    }
    bp = bp->q_forw;
  }
}

