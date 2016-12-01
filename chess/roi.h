#ifndef ROI_H
#define ROI_H

#include <string.h>
#include <stdbool.h>

static int window_lines_ = 22;
static int window_columns_ = 72;
static int current_addr_ = 0;     /* current address in editor buffer */
static bool traditional_ = false; /* if set, be backwards compatible */
static char errmsg[80] = "";      /* error message buffer */

int window_columns(void) { return window_columns_; }
int window_lines(void) { return window_lines_; }
int current_addr(void) { return current_addr_; }
bool traditional(void) { return traditional_; }
void set_current_addr(const int addr) { current_addr_ = addr; }

enum Gflags {
  GLB = 0x01, /* global command */
  GLS = 0x02, /* list after command */
  GNP = 0x04, /* enumerate after command */
  GPR = 0x08, /* print after command */
  GSG = 0x10  /* global substitute */
};

typedef struct line { /* Line node */
  struct line *q_forw, *q_back;
  long pos; /* position of text in scratch buffer */
  int len;  /* length of line ('\n' is not stored) */
} line_t;

typedef struct {
  enum { UADD=0, UDEL=1, UMOV=2, VMOV=3 } type;
  line_t *head, *tail; /* head, tail of list */
} undo_t;

#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

void set_err_msg(const char *msg)
{
  if (!msg)
    msg = "";
  strncpy(errmsg, msg, sizeof errmsg);
  errmsg[sizeof(errmsg)-1] = 0;
}

static void put_tty_line(const char *p, int len, const int gflags)
{
  const char escapes[] = "\a\b\f\n\r\t\v\\";
  const char escchars[] = "abfnrtv\\";
  int col = 0;

  if (gflags & GNP) {
    printf("%d\t", current_addr());
    col = 8;
  }
  while (--len >= 0) {
    const unsigned char ch = *p++;
    if (!(gflags & GLS))
      putchar(ch);
    else {
      if (++col > window_columns()) {
        col = 1;
        fputs("\\\n", stdout);
      }
      if (ch>=32 && ch<=126 && ch!='\\')
        putchar(ch);
      else {
        char *const p = strchr(escapes, ch);
        ++col;
        putchar('\\');
        if (ch && p)
          putchar(escchars[p-escapes]);
        else {
          col += 2;
          putchar(((ch>>6)&7)+'0');
          putchar(((ch>>3)&7)+'0');
          putchar((ch&7)+'0');
        }
      }
    }
  }
  if (!traditional() && (gflags & GLS))
    putchar('$');
  putchar('\n');
}

#endif /* ROI_H */
