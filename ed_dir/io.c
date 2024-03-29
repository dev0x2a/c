/* io.c: i/o routines for the ed line editor */
#include "ed.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

/* print text to stdout */
static void put_tty_line(const char *p, int len, const int gflags) {
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
      if (ch >= 32 && ch <= 126 && ch != '\\')
        putchar(ch);
      else {
        char *const p = strchr(escapes, ch);
        ++col;
        putchar('\\');
        if (ch && p)
          putchar(escchars[p - escapes]);
        else {
          col += 2;
          putchar(((ch >> 6) & 7) + '0');
          putchar(((ch >> 3) & 7) + '0');
          putchar((ch & 7) + '0');
        }
      }
    }
  }
  if (!traditional() && (gflags & GLS))
    putchar('$');
  putchar('\n');
}

/* print a range of lines to stdout */
bool display_lines(int from, const int to, const int gflags) {
  line_t *const ep = search_line_node(inc_addr(to)),
                *bp = search_line_node(from);

  if (!from) {
    set_error_msg("Invalid address");
    return false;
  }
  while (bp != ep) {
    const char *const s = get_sbuf_line(bp);
    if (!s)
      return false;
    set_current_addr(from++);
    put_tty_line(s, bp->len, gflags);
    bp = bp->q_forw;
  }
  return true;
}

/* return the parity of escapes at the end of a string */
static bool trailing_escape(const char *const s, int len) {
  bool odd_escape = false;
  while (--len >= 0 && s[len] == '\\')
    odd_escape = !odd_escape;
  return odd_escape;
}

/* If *ibufpp contains an escaped newline, get an extended line (one
   with escaped newlines) from stdin */
bool get_extended_line(const char **const ibufpp, int *const lenp,
                       const bool strip_escaped_newlines) {
  static char *buf = 0;
  static int bufsz = 0;
  int len;

  for (len = 0; (*ibufpp)[len++] != '\n';)
    ;
  if (len < 2 || !trailing_escape(*ibufpp, len - 1)) {
    if (lenp)
      *lenp = len;
    return true;
  }
  if (!resize_buffer(&buf, &bufsz, len))
    return false;
  memcpy(buf, *ibufpp, len);
  --len;
  buf[len - 1] = '\n'; /* strip trailing esc */
  if (strip_escaped_newlines)
    --len; /* strip newline */
  while (true) {
    int len2;
    const char *const s = get_tty_line(&len2);
    if (!s)
      return false;
    if (len2 == 0 || s[len2 - 1] != '\n') {
      set_error_msg("Unexpected end-of-file");
      return false;
    }
    if (!resize_buffer(&buf, &bufsz, len + len2))
      return false;
    memcpy(buf + len, s, len2);
    len += len2;
    if (len2 < 2 || !trailing_escape(buf, len - 1))
      break;
    --len;
    buf[len - 1] = '\n'; /* strip trailing esc */
    if (strip_escaped_newlines)
      --len; /* strip newline */
  }
  if (!resize_buffer(&buf, &bufsz, len + 1))
    return false;
  buf[len] = 0;
  *ibufpp = buf;
  if (lenp)
    *lenp = len;
  return true;
}

/* Read a line of text from stdin.
   Returns pointer to buffer and line size (including trailing newline
   if it exists) */
const char *get_tty_line(int *const sizep) {
  static char *buf = 0;
  static int bufsz = 0;
  int i = 0;

  while (true) {
    const int c = getchar();
    if (!resize_buffer(&buf, &bufsz, i + 2)) {
      if (sizep)
        *sizep = 0;
      return 0;
    }
    if (c == EOF) {
      if (ferror(stdin)) {
        show_strerror("stdin", errno);
        set_error_msg("Cannot read stdin");
        clearerr(stdin);
        if (sizep)
          *sizep = 0;
        return 0;
      }
      if (feof(stdin)) {
        clearerr(stdin);
        buf[i] = 0;
        if (sizep)
          *sizep = i;
        return buf;
      }
    } else {
      buf[i++] = c;
      if (!c)
        set_binary();
      if (c != '\n')
        continue;
      buf[i] = 0;
      if (sizep)
        *sizep = i;
      return buf;
    }
  }
}

/* Read a line of text from a stream.
   Returns pointer to buffer and line size (including trailing newline
   if it exists and is not added now) */
static const char *read_stream_line(FILE *const fp, int *const sizep,
                                    bool *const newline_added_nowp) {
  static char *buf = 0;
  static int bufsz = 0;
  int c, i = 0;

  while (true) {
    if (!resize_buffer(&buf, &bufsz, i + 2))
      return 0;
    c = getc(fp);
    if (c == EOF)
      break;
    buf[i++] = c;
    if (!c)
      set_binary();
    else if (c == '\n')
      break;
  }
  buf[i] = 0;
  if (c == EOF) {
    if (ferror(fp)) {
      show_strerror(0, errno);
      set_error_msg("Cannot read input file");
      return 0;
    } else if (i) {
      buf[i] = '\n';
      buf[i + 1] = 0;
      *newline_added_nowp = true;
      if (!isbinary())
        ++i;
    }
  }
  *sizep = i;
  return buf;
}

/* read a stream into the editor buffer; return total size of data read */
static long read_stream(FILE *const fp, const int addr) {
  line_t *lp = search_line_node(addr);
  undo_t *up = 0;
  long total_size = 0;
  const bool o_isbinary = isbinary(), appended = (addr == last_addr());
  bool newline_added_now = false;

  set_current_addr(addr);
  while (true) {
    int size = 0;
    const char *const s = read_stream_line(fp, &size, &newline_added_now);
    if (!s)
      return -1;
    if (size > 0)
      total_size += size;
    else
      break;
    disable_interrupts();
    if (!put_sbuf_line(s, size + newline_added_now, current_addr())) {
      enable_interrupts();
      return -1;
    }
    lp = lp->q_forw;
    if (up)
      up->tail = lp;
    else {
      up = push_undo_atom(UADD, current_addr(), current_addr());
      if (!up) {
        enable_interrupts();
        return -1;
      }
    }
    enable_interrupts();
  }
  if (addr && appended && total_size && o_isbinary && newline_added())
    fputs("Newline inserted\n", stderr);
  else if (newline_added_now && (!appended || !isbinary()))
    fputs("Newline appended\n", stderr);
  if (isbinary() && !o_isbinary && newline_added_now && !appended)
    ++total_size;
  if (!total_size)
    newline_added_now = true;
  if (appended && newline_added_now)
    set_newline_added();
  return total_size;
}

/* read a named file/pipe into the buffer; return line count */
int read_file(const char *const filename, const int addr) {
  FILE *fp;
  long size;
  int ret;

  if (*filename == '!')
    fp = popen(filename + 1, "r");
  else
    fp = fopen(strip_escapes(filename), "r");
  if (!fp) {
    show_strerror(filename, errno);
    set_error_msg("Cannot open input file");
    return -1;
  }
  size = read_stream(fp, addr);
  if (*filename == '!')
    ret = pclose(fp);
  else
    ret = fclose(fp);
  if (size < 0)
    return -1;
  if (ret != 0) {
    show_strerror(filename, errno);
    set_error_msg("Cannot close input file");
    return -1;
  }
  if (!scripted())
    fprintf(stderr, "%lu\n", size);
  return current_addr() - addr;
}

/* write a range of lines to a stream */
static long write_stream(FILE *const fp, int from, const int to) {
  line_t *lp = search_line_node(from);
  long size = 0;

  while (from && from <= to) {
    int len;
    char *p = get_sbuf_line(lp);
    if (!p)
      return -1;
    len = lp->len;
    if (from != last_addr() || !isbinary() || !newline_added())
      p[len++] = '\n';
    size += len;
    while (--len >= 0)
      if (fputc(*p++, fp) == EOF) {
        show_strerror(0, errno);
        set_error_msg("Cannot write file");
        return -1;
      }
    ++from;
    lp = lp->q_forw;
  }
  return size;
}

/* write a range of lines to a named file/pipe; return line count */
int write_file(const char *const filename, const char *const mode,
               const int from, const int to) {
  FILE *fp;
  long size;
  int ret;

  if (*filename == '!')
    fp = popen(filename + 1, "w");
  else
    fp = fopen(strip_escapes(filename), mode);
  if (!fp) {
    show_strerror(filename, errno);
    set_error_msg("Cannot open output file");
    return -1;
  }
  size = write_stream(fp, from, to);
  if (*filename == '!')
    ret = pclose(fp);
  else
    ret = fclose(fp);
  if (size < 0)
    return -1;
  if (ret != 0) {
    show_strerror(filename, errno);
    set_error_msg("Cannot close output file");
    return -1;
  }
  if (!scripted())
    fprintf(stderr, "%lu\n", size);
  return (from && from <= to) ? to - from + 1 : 0;
}
