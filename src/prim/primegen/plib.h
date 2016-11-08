#ifndef PLIB_H
#define PLIB_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

typedef unsigned int uint32;
typedef unsigned long uint64;
typedef long int64;

typedef struct timeval timing_basic;
/*
 * B is 32 times X.
 * Total memory use for one generator is 2B bytes  =  64X bytes.
 * Covers primes in an interval of length 1920X.
 * Working set size for one generator is B bits  =  4X bytes.
 *
 * Speedup by a factor of 2 or 3 for L1 cache instead of L2 cache.
 * Slowdown by a factor of roughly n for primes past (nB)^2.
 *
 * Possible choices of X:
 *  2002 to fit inside an 8K L1 cache (e.g.,  Pentium).
 *  4004 to fit inside a 16K L1 cache (e.g.,  Pentium II).
 *  64064 to fit inside a 256K L2 cache.
 *
 * There are various word-size limits on X; 1000000 should still be okay.
 */
#define PRIMEGEN_WORDS 2048
#define B32 PRIMEGEN_WORDS
#define B (PRIMEGEN_WORDS*32)

#define HASRDTSC 1
#define HASGETHRTIME 0
#define SUBSTDIO_INSIZE 8192
#define SUBSTDIO_OUTSIZE 8192

#define substdio_fileno(s) ((s)->fd)
#define str_equal(s,t) (!str_diff((s),(t)))
#define byte_equal(s,n,t) (!byte_diff((s),(n),(t)))

#define substdio_PEEK(s) ((s)->x+(s)->n)
#define substdio_SEEK(s,len) (((s)->p-=(len)),((s)->n+=(len)))
#define substdio_BPUTC(s,c)\
(((s)->n!=(s)->p)?((s)->x[(s)->p++]=(c),0):substdio_bput((s),&(c),1))
#define SUBSTDIO_FDBUF(op,fd,buf,len) {(buf),0,(len),(fd),(op)}

typedef struct {
  uint32 buf[16][PRIMEGEN_WORDS];
  uint64 p[512];  /* p[num-1]...p[0],  in that order */
  int num, pos;   /* next entry to use in buf; WORDS to restart */
  uint64 base, L;
} primegen;

#include "primegen.h"

typedef struct substdio {
  char *x;
  int p, n, fd;
  int (*op)();
} substdio;

struct strerr {
  struct strerr *who;
  char *x, *y, *z;
};

#define timing_basic_now(x) gettimeofday((x),(struct timezone*)0)
#define timing_basic_diff(x,y) (1000.0*((x)->tv_usec-(double)(y)->tv_usec)+\
  1000000000.0*((x)->tv_sec-(double)(y)->tv_sec))

#ifdef HASRDTSC
typedef struct {
  uint64 t[2];
} timing;

#define timing_now(x)\
  asm volatile(".byte 15;.byte 49":"=a"((x)->t[0]),"=d"((x)->t[1]))
#define timing_diff(x,y)\
  (((x)->t[0]-(double)(y)->t[0])+4294967296.0*((x)->t[1]-(double)(y)->t[1]))

#else
#ifdef HASGETHRTIME
typedef struct {
  hrtime_t t;
} timing;

#define timing_now(x) ((x)->t = gethrtime())
#define timing_diff(x,y) ((double)((x)->t-(y)->t))

#else
#define timing timing_basic
#define timing_now timing_basic_now
#define timing_diff timing_basic_diff

#endif
#endif

#define STRERR(r,se,a)\
{se.who=0; se.x=a; se.y=0; se.z=0; return(r);}

#define STRERR_SYS(r,se,a)\
{se.who=&strerr_sys; se.x=a; se.y=0; se.z=0; return(r);}

#define STRERR_SYS3(r,se,a,b,c)\
{se.who=&strerr_sys; se.x=a; se.y=b; se.z=c; return(r);}

#define strerr_warn6(x1,x2,x3,x4,x5,x6,se)\
strerr_warn((x1),(x2),(x3),(x4),(x5),(x6),(struct strerr*)(se))

#define strerr_warn5(x1, x2, x3, x4, x5, se)\
strerr_warn((x1),(x2),(x3),(x4),(x5),(char*)0,(struct strerr*)(se))

#define strerr_warn4(x1,x2,x3,x4,se)\
strerr_warn((x1),(x2),(x3),(x4),\
(char*)0,(char*)0,(struct strerr*)(se))

#define strerr_warn3(x1,x2,x3,se)\
strerr_warn((x1),(x2),(x3),\
(char*)0,(char*)0,(char*)0,(struct strerr*)(se))

#define strerr_warn2(x1,x2,se)\
strerr_warn((x1),(x2),(char*)0,(char*)0,\
(char*)0,(char*)0,(struct strerr*)(se))

#define strerr_warn1(x1,se)\
strerr_warn((x1),\
(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)(se))

#define strerr_die6(e,x1,x2,x3,x4,x5,x6,se)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(x6),(struct strerr*)(se))

#define strerr_die5(e,x1,x2,x3,x4,x5,se)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),\
(char*)0,(struct strerr*)(se))

#define strerr_die4(e,x1,x2,x3,x4,se)\
strerr_die((e),(x1),(x2),(x3),(x4),\
(char*)0,(char*)0,(struct strerr*)(se))

#define strerr_die3(e,x1,x2,x3,se)\
strerr_die((e),(x1),(x2),(x3),\
(char*)0,(char*)0,(char*)0,(struct strerr*)(se))

#define strerr_die2(e,x1,x2,se)\
strerr_die((e),(x1),(x2),\
(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)(se))

#define strerr_die1(e,x1,se)\
strerr_die((e),(x1),\
(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)(se))

#define strerr_die6sys(e,x1,x2,x3,x4,x5,x6)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(x6),&strerr_sys)

#define strerr_die5sys(e,x1,x2,x3,x4,x5)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(char*)0,&strerr_sys)

#define strerr_die4sys(e,x1,x2,x3,x4)\
strerr_die((e),(x1),(x2),(x3),(x4),(char*)0,(char*)0,&strerr_sys)

#define strerr_die3sys(e,x1,x2,x3)\
strerr_die((e),(x1),(x2),(x3),(char*)0,(char*)0,(char*)0,&strerr_sys)

#define strerr_die2sys(e,x1,x2)\
strerr_die((e),(x1),(x2),(char*)0,(char*)0,(char*)0,(char*)0,&strerr_sys)

#define strerr_die1sys(e,x1)\
strerr_die((e),(x1),\
(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,&strerr_sys)

#define strerr_die6x(e,x1,x2,x3,x4,x5,x6)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(x6),(struct strerr*)0)

#define strerr_die5x(e,x1,x2,x3,x4,x5)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(char*)0,(struct strerr*)0)

#define strerr_die4x(e,x1,x2,x3,x4)\
strerr_die((e),(x1),(x2),(x3),(x4),(char*)0,(char*)0,(struct strerr*)0)

#define strerr_die3x(e,x1,x2,x3)\
strerr_die((e),(x1),(x2),(x3),(char*)0,(char*)0,(char*)0,(struct strerr*)0)

#define strerr_die2x(e,x1,x2)\
strerr_die((e),(x1),(x2),\
(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)0)

#define strerr_die1x(e,x1)\
strerr_die((e),(x1),\
(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)0)

char subfd_errbuf[256];
struct strerr strerr_sys;
extern struct strerr strerr_sys;
extern int read();
extern int write();
extern int str_diff();
extern int str_diffn();
extern int str_start();
extern int subfd_read();
extern int subfd_readsmall();
extern int substdio_flush();
extern int substdio_put();
extern int substdio_bput();
extern int substdio_putflush();
extern int substdio_puts();
extern int substdio_bputs();
extern int substdio_putsflush();
extern int substdio_get();
extern int substdio_bget();
extern int substdio_feed();
extern int substdio_copy();
extern int errno;
extern int error_intr;
extern int error_nomem;
extern int error_noent;
extern int error_txtbsy;
extern int error_io;
extern int error_exist;
extern int error_timeout;
extern int error_inprogress;
extern int error_wouldblock;
extern int error_again;
extern int error_pipe;
extern int error_perm;
extern int error_acces;
extern int error_temp();
extern int open_read();
extern int open_excl();
extern int open_append();
extern int open_trunc();
extern int open_write();
extern int byte_diff();
extern char *error_str();
extern char *substdio_peek();
extern char *strerr();
extern char auto_home[];
extern void _exit();
extern void strerr_sysinit();
extern void strerr_warn();
extern void strerr_die();
extern void primegen_sieve(primegen*);
extern void primegen_fill(primegen*);
extern void primegen_init(primegen*);
extern void primegen_skipto(primegen*, uint64 to);
extern void substdio_fdbuf();
extern void substdio_seek();
extern void byte_copy();
extern void byte_copyr();
extern void byte_zero();
extern uint32 str_copy();
extern uint32 str_len();
extern uint32 str_chr();
extern uint32 str_rchr();
extern uint32 scan_uint64(char*, uint64*);
extern uint32 fmt_uint64(char*, uint64);
extern uint32 byte_chr();
extern uint32 byte_rchr();
extern uint64 primegen_next(primegen*);
extern uint64 primegen_peek(primegen*);
extern uint64 primegen_count(primegen*, uint64 to);
extern substdio *subfdin;
extern substdio *subfdinsmall;
extern substdio *subfdout;
extern substdio *subfdoutsmall;
extern substdio *subfderr;

void strerr_sysinit(void)
{ 
  strerr_sys.who = 0;
  strerr_sys.x = error_str(errno);
  strerr_sys.y = "";
  strerr_sys.z = "";
}


void substdio_fdbuf(register substdio *s, register int (*op)(), 
    register int fd,register char *buf, register int len)
{ 
  s->x = buf;
  s->fd = fd;
  s->op = op;
  s->p = 0;
  s->n = len;
}


int substdio_copy(register substdio *ssout, register substdio *ssin)
{ 
  register int n;
  register char *x;
  for (;;) {
    n = substdio_feed(ssin);
    if (n < 0)
      return(-2);
    if (!n)
      return(0);
    x = substdio_PEEK(ssin);
    if (substdio_put(ssout, x, n) == -1)
      return(-3);
    substdio_SEEK(ssin, n);
  }
}


int open_read(char *fn)
{ 
  return(open(fn, O_RDONLY | O_NDELAY));
}


int open_trunc(char *fn)
{ 
  return(open(fn, O_WRONLY | O_NDELAY | O_TRUNC | O_CREAT, 0644));
}


uint32 scan_uint64(char *s, uint64 *u)
{ 
  uint32 pos = 0;
  uint64 c, result = 0;

  while ((c=(uint64)(unsigned char)(s[pos]-'0')) < 10) {
    result = result*10+c;
    ++pos;
  }
  *u = result;
  return(pos);
}


uint32 fmt_uint64(char *s, uint64 u)
{ 
  uint32 len = 1;
  uint64 q = u;
  while (q > 9) {
    ++len;
    q /= 10;
  }
  if (s) {
    s += len;
    do {
      *--s = '0'+(u%10);
      u /= 10;
    } while (u);
  }
  return(len);
}


void primegen_init(primegen *pg)
{ 
  pg->L = 1;
  pg->base = 60;
  pg->pos = PRIMEGEN_WORDS;
  pg->p[0] = 59;
  pg->p[1] = 53;
  pg->p[2] = 47;
  pg->p[3] = 43;
  pg->p[4] = 41;
  pg->p[5] = 37;
  pg->p[6] = 31;
  pg->p[7] = 29;
  pg->p[8] = 23;
  pg->p[9] = 19;
  pg->p[10] = 17;
  pg->p[11] = 13;
  pg->p[12] = 11;
  pg->p[13] = 7;
  pg->p[14] = 5;
  pg->p[15] = 3;
  pg->p[16] = 2;
  pg->num = 17;
}


void byte_copy(register char *to, register uint32 n,
    register char *from)
{ 
  for (;;) {
    if (!n) return;
    *to++ = *from++; --n;
    if (!n) return;
    *to++ = *from++; --n;
    if (!n) return;
    *to++ = *from++; --n;
    if (!n) return;
    *to++ = *from++; --n;
  }
}


void byte_copyr(register char *to,register uint32 n,
    register char *from)
{ 
  to += n;
  from += n;
  for (;;) {
    if (!n) return;
    *--to = *--from; --n;
    if (!n) return;
    *--to = *--from; --n;
    if (!n) return;
    *--to = *--from; --n;
    if (!n) return;
    *--to = *--from; --n;
  }
}


uint32 str_len(register char *s)
{ 
  register char *t = s;
  for (;;) {
    if (!*t) return(t-s);
    ++t;
    if (!*t) return(t-s);
    ++t;
    if (!*t) return(t-s);
    ++t;
    if (!*t) return(t-s);
    ++t;
  }
}


void primegen_fill(primegen *pg)
{ 
  int i;
  uint32 mask, bits0, bits1, bits2, bits3, bits4, bits5, bits6, bits7;
  uint32 bits8, bits9, bits10, bits11, bits12, bits13, bits14, bits15;
  uint64 base;

  i = pg->pos;
  if (i == B32) {
    primegen_sieve(pg);
    pg->L += B;
    i = 0;
  }
  pg->pos = i+1;
  bits0 = ~pg->buf[0][i];
  bits1 = ~pg->buf[1][i];
  bits2 = ~pg->buf[2][i];
  bits3 = ~pg->buf[3][i];
  bits4 = ~pg->buf[4][i];
  bits5 = ~pg->buf[5][i];
  bits6 = ~pg->buf[6][i];
  bits7 = ~pg->buf[7][i];
  bits8 = ~pg->buf[8][i];
  bits9 = ~pg->buf[9][i];
  bits10 = ~pg->buf[10][i];
  bits11 = ~pg->buf[11][i];
  bits12 = ~pg->buf[12][i];
  bits13 = ~pg->buf[13][i];
  bits14 = ~pg->buf[14][i];
  bits15 = ~pg->buf[15][i];
  base = pg->base+1920;
  pg->base = base;
  pg->num = 0;
  for (mask=0x80000000; mask; mask>>=1) {
    base -= 60;
    if (bits15&mask) pg->p[pg->num++] = base+59;
    if (bits14&mask) pg->p[pg->num++] = base+53;
    if (bits13&mask) pg->p[pg->num++] = base+49;
    if (bits12&mask) pg->p[pg->num++] = base+47;
    if (bits11&mask) pg->p[pg->num++] = base+43;
    if (bits10&mask) pg->p[pg->num++] = base+41;
    if (bits9&mask) pg->p[pg->num++] = base+37;
    if (bits8&mask) pg->p[pg->num++] = base+31;
    if (bits7&mask) pg->p[pg->num++] = base+29;
    if (bits6&mask) pg->p[pg->num++] = base+23;
    if (bits5&mask) pg->p[pg->num++] = base+19;
    if (bits4&mask) pg->p[pg->num++] = base+17;
    if (bits3&mask) pg->p[pg->num++] = base+13;
    if (bits2&mask) pg->p[pg->num++] = base+11;
    if (bits1&mask) pg->p[pg->num++] = base+7;
    if (bits0&mask) pg->p[pg->num++] = base+1;
  }
}


uint64 primegen_next(primegen *pg)
{ 
  while (!pg->num)
    primegen_fill(pg);
  return(pg->p[--pg->num]);
}


uint64 primegen_peek(primegen *pg)
{ 
  while (!pg->num)
    primegen_fill(pg);
  return(pg->p[pg->num-1]);
}


static const uint64 pop[256] = {
  0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};


uint64 primegen_count(primegen *pg, uint64 to)
{ 
  uint64 count = 0;
  register int pos, j;
  register uint32 bits, smallcount;
  for (;;) {
    while (pg->num) {
      if (pg->p[pg->num-1] >= to)
        return(count);
      ++count;
      --pg->num;
    }
    smallcount = 0;
    pos = pg->pos;
    while ((pos < B32)&&(pg->base+1920 < to)) {
      for (j=0; j<16; ++j) {
        bits = ~pg->buf[j][pos];
        smallcount += pop[bits&255]; bits >>= 8;
        smallcount += pop[bits&255]; bits >>= 8;
        smallcount += pop[bits&255]; bits >>= 8;
        smallcount += pop[bits&255];
      }
      pg->base += 1920;
      ++pos;
    }
    pg->pos = pos;
    count += smallcount;
    if (pos == B32)
      while (pg->base+B*60 < to) {
        primegen_sieve(pg);
        pg->L += B;
        smallcount = 0;
        for (j=0; j<16; ++j)
          for (pos=0; pos<B32; ++pos) {
            bits = ~pg->buf[j][pos];
            smallcount += pop[bits&255]; bits >>=  8;
            smallcount += pop[bits&255]; bits >>=  8;
            smallcount += pop[bits&255]; bits >>=  8;
            smallcount += pop[bits&255];
          }
        count += smallcount;
        pg->base += B*60;
      }
    primegen_fill(pg);
  }
}


void primegen_skipto(primegen *pg, uint64 to)
{ 
  int pos;
  for (;;) {
    while (pg->num) {
      if (pg->p[pg->num-1] >= to)
        return;
      --pg->num;
    }
    pos = pg->pos;
    while ((pos < B32)&&(pg->base+1920 < to)) {
      pg->base += 1920;
      ++pos;
    }
    pg->pos = pos;
    if (pos == B32)
      while (pg->base+B*60 < to) {
        pg->L += B;
        pg->base += B*60;
      }
    primegen_fill(pg);
  }
}


void strerr_warn(char *x1, char *x2, char *x3, char *x4,
    char *x5, char *x6, struct strerr *se)
{ 
  strerr_sysinit();
  if (x1)
    substdio_puts(subfderr, x1);
  if (x2)
    substdio_puts(subfderr, x2);
  if (x3)
    substdio_puts(subfderr, x3);
  if (x4)
    substdio_puts(subfderr, x4);
  if (x5)
    substdio_puts(subfderr, x5);
  if (x6)
    substdio_puts(subfderr, x6);
  while (se) {
    if (se->x)
      substdio_puts(subfderr, se->x);
    if (se->y)
      substdio_puts(subfderr, se->y);
    if (se->z)
      substdio_puts(subfderr, se->z);
    se = se->who;
  }
  substdio_puts(subfderr, "\n");
  substdio_flush(subfderr);
}


void strerr_die(int e, char *x1, char *x2, char *x3, char *x4,
    char *x5, char *x6, struct strerr *se)
{ 
  strerr_warn(x1, x2, x3, x4, x5, x6, se);
  _exit(e);
}


static int oneread(register int (*op)(), register int fd,
    register char *buf, register int len)
{ 
  register int r;
  for (;;) {
    r = op(fd, buf, len);
    if (r == -1)
      if (errno == error_intr)
        continue;
    return(r);
  }
}


static int getthis(register substdio *s, register char *buf,
    register int len)
{ 
  register int r, q;
  r = s->p;
  q = r-len;
  if (q>0) {
    r = len;
    s->p = q;
  } 
  else 
    s->p = 0;
  byte_copy(buf, r, s->x+s->n);
  s->n += r;
  return(r);
}


int substdio_feed(register substdio *s)
{ 
  register int r, q;
  if (s->p)
    return(s->p);
  q = s->n;
  r = oneread(s->op, s->fd, s->x, q);
  if (r <= 0)
    return(r);
  s->p = r;
  q -= r;
  s->n = q;
  if (q > 0)
    byte_copyr(s->x+q, r, s->x); /* have to shift */
  return(r);
}


int substdio_bget(register substdio *s, register char *buf,
    register int len)
{ 
  register int r;
  if (s->p>0)
    return(getthis(s, buf, len));
  r = s->n;
  if (r <= len)
    return(oneread(s->op, s->fd, buf, r));
  r = substdio_feed(s);
  if (r <= 0)
    return(r);
  return(getthis(s, buf, len));
}


int substdio_get(register substdio *s, register char *buf,
    register int len)
{ 
  register int r;
  if (s->p>0)
    return(getthis(s, buf, len));
  if (s->n <= len)
    return(oneread(s->op, s->fd, buf, len));
  r = substdio_feed(s);
  if (r <= 0)
    return(r);
  return(getthis(s, buf, len));
}


char *substdio_peek(register substdio *s)
{ 
  return(s->x+s->n);
}


void substdio_seek(register substdio *s, register int len)
{ 
  s->n += len;
  s->p -= len;
}


static int allwrite(register int (*op)(), register int fd,
    register char *buf, register int len)
{ 
  register int w;
  while (len) {
    w = op(fd, buf, len);
    if (w == -1) {
      if (errno == error_intr)
        continue;
      return(-1); /* note that some data may have been written */
    }
    if (w == 0); /* luser's fault */
    buf += w;
    len -= w;
  }
  return(0);
}


int substdio_flush(register substdio *s)
{ 
  register int p = s->p;
  if (!p)
    return(0);
  s->p = 0;
  return(allwrite(s->op, s->fd, s->x, p));
}


int substdio_bput(register substdio *s, register char *buf,
    register int len)
{ 
  register int n;
  while (len > (n=s->n-s->p)) {
    byte_copy(s->x+s->p, n, buf);
    s->p += n;
    buf += n;
    len -= n;
    if (substdio_flush(s) == -1)
      return(-1);
  }
  /* now len <= s->n - s->p */
  byte_copy(s->x+s->p, len, buf);
  s->p += len;
  return(0);
}


int substdio_put(register substdio *s, register char *buf,
    register int len)
{ 
  register int n = s->n;
  if (len > n-s->p) {
    if (substdio_flush(s) == -1)
      return(-1);
    /* now s->p == 0 */
    if (n < SUBSTDIO_OUTSIZE)
      n = SUBSTDIO_OUTSIZE;
    while (len>s->n) {
      if (n>len)
        n = len;
      if (allwrite(s->op, s->fd, buf, n) == -1)
        return(-1);
      buf += n;
      len -= n;
    }
  }
  /* now len <= s->n - s->p */
  byte_copy(s->x+s->p, len, buf);
  s->p += len;
  return(0);
}


int substdio_putflush(register substdio *s, register char *buf,
    register int len)
{ 
  if (substdio_flush(s) == -1)
    return(-1);
  return(allwrite(s->op, s->fd, buf, len));
}


int substdio_bputs(register substdio *s, register char *buf)
{ 
  return(substdio_bput(s, buf, str_len(buf)));
}


int substdio_puts(register substdio *s, register char  *buf)
{ 
  return(substdio_put(s, buf, str_len(buf)));
}


int substdio_putsflush(register substdio *s, register char *buf)
{ 
  return(substdio_putflush(s, buf, str_len(buf)));
}

static substdio it = SUBSTDIO_FDBUF(write, 2, subfd_errbuf, 256);
substdio *subfderr = &it;

/*warning: as coverage improves here,  should update error_{str, temp}*/
int error_intr = 
#ifdef EINTR
EINTR;
#else
-1;
#endif
int error_nomem = 
#ifdef ENOMEM
ENOMEM;
#else
-2;
#endif
int error_noent =  
#ifdef ENOENT
ENOENT;
#else
-3;
#endif
int error_txtbsy = 
#ifdef ETXTBSY
ETXTBSY;
#else
-4;
#endif
int error_io =
#ifdef EIO
EIO;
#else
-5;
#endif
int error_exist =
#ifdef EEXIST
EEXIST;
#else
-6;
#endif
int error_timeout = 
#ifdef ETIMEDOUT
ETIMEDOUT;
#else
-7;
#endif
int error_inprogress = 
#ifdef EINPROGRESS
EINPROGRESS;
#else
-8;
#endif
int error_wouldblock = 
#ifdef EWOULDBLOCK
EWOULDBLOCK;
#else
-9;
#endif
int error_again = 
#ifdef EAGAIN
EAGAIN;
#else
-10;
#endif
int error_pipe = 
#ifdef EPIPE
EPIPE;
#else
-11;
#endif
int error_perm = 
#ifdef EPERM
EPERM;
#else
-12;
#endif
int error_acces = 
#ifdef EACCES
EACCES;
#else
-13;
#endif
#define X(e, s) if (i == e)return(s);

char *error_str(int i)
{ 
  X(0, "no error")
  X(error_intr, "interrupted system call")
  X(error_nomem, "out of memory")
  X(error_noent, "file does not exist")
  X(error_txtbsy, "text busy")
  X(error_io, "input/output error")
  X(error_exist, "file already exists")
  X(error_timeout, "timed out")
  X(error_inprogress, "operation in progress")
  X(error_again, "temporary failure")
  X(error_wouldblock, "input/output would block")
  X(error_pipe, "broken pipe")
  X(error_perm, "permission denied")
  X(error_acces, "access denied")
#ifdef ESRCH
  X(ESRCH, "no such process")
#endif
#ifdef ENXIO
  X(ENXIO, "device not configured")
#endif
#ifdef E2BIG
  X(E2BIG, "argument list too long")
#endif
#ifdef ENOEXEC
  X(ENOEXEC, "exec format error")
#endif
#ifdef EBADF
  X(EBADF, "file descriptor not open")
#endif
#ifdef ECHILD
  X(ECHILD, "no child processes")
#endif
#ifdef EDEADLK
  X(EDEADLK, "operation would cause deadlock")
#endif
#ifdef EFAULT
  X(EFAULT, "bad address")
#endif
#ifdef ENOTBLK
  X(ENOTBLK, "not a block device")
#endif
#ifdef EBUSY
  X(EBUSY, "device busy")
#endif
#ifdef EXDEV
  X(EXDEV, "cross-device link")
#endif
#ifdef ENODEV
  X(ENODEV, "device does not support operation")
#endif
#ifdef ENOTDIR
  X(ENOTDIR, "not a directory")
#endif
#ifdef EISDIR
  X(EISDIR, "is a directory")
#endif
#ifdef EINVAL
  X(EINVAL, "invalid argument")
#endif
#ifdef ENFILE
  X(ENFILE, "system cannot open more files")
#endif
#ifdef EMFILE
  X(EMFILE, "process cannot open more files")
#endif
#ifdef ENOTTY
  X(ENOTTY, "not a tty")
#endif
#ifdef EFBIG
  X(EFBIG, "file too big")
#endif
#ifdef ENOSPC
  X(ENOSPC, "out of disk space")
#endif
#ifdef ESPIPE
  X(ESPIPE, "unseekable descriptor")
#endif
#ifdef EROFS
  X(EROFS, "read-only file system")
#endif
#ifdef EMLINK
  X(EMLINK, "too many links")
#endif
#ifdef EDOM
  X(EDOM, "input out of range")
#endif
#ifdef ERANGE
  X(ERANGE, "output out of range")
#endif
#ifdef EALREADY
  X(EALREADY, "operation already in progress")
#endif
#ifdef ENOTSOCK
  X(ENOTSOCK, "not a socket")
#endif
#ifdef EDESTADDRREQ
  X(EDESTADDRREQ, "destination address required")
#endif
#ifdef EMSGSIZE
  X(EMSGSIZE, "message too long")
#endif
#ifdef EPROTOTYPE
  X(EPROTOTYPE, "incorrect protocol type")
#endif
#ifdef ENOPROTOOPT
  X(ENOPROTOOPT, "protocol not available")
#endif
#ifdef EPROTONOSUPPORT
  X(EPROTONOSUPPORT, "protocol not supported")
#endif
#ifdef ESOCKTNOSUPPORT
  X(ESOCKTNOSUPPORT, "socket type not supported")
#endif
#ifdef EOPNOTSUPP
  X(EOPNOTSUPP, "operation not supported")
#endif
#ifdef EPFNOSUPPORT
  X(EPFNOSUPPORT, "protocol family not supported")
#endif
#ifdef EAFNOSUPPORT
  X(EAFNOSUPPORT, "address family not supported")
#endif
#ifdef EADDRINUSE
  X(EADDRINUSE, "address already used")
#endif
#ifdef EADDRNOTAVAIL
  X(EADDRNOTAVAIL, "address not available")
#endif
#ifdef ENETDOWN
  X(ENETDOWN, "network down")
#endif
#ifdef ENETUNREACH
  X(ENETUNREACH, "network unreachable")
#endif
#ifdef ENETRESET
  X(ENETRESET, "network reset")
#endif
#ifdef ECONNABORTED
  X(ECONNABORTED, "connection aborted")
#endif
#ifdef ECONNRESET
  X(ECONNRESET, "connection reset")
#endif
#ifdef ENOBUFS
  X(ENOBUFS, "out of buffer space")
#endif
#ifdef EISCONN
  X(EISCONN, "already connected")
#endif
#ifdef ENOTCONN
  X(ENOTCONN, "not connected")
#endif
#ifdef ESHUTDOWN
  X(ESHUTDOWN, "socket shut down")
#endif
#ifdef ETOOMANYREFS
  X(ETOOMANYREFS, "too many references")
#endif
#ifdef ECONNREFUSED
  X(ECONNREFUSED, "connection refused")
#endif
#ifdef ELOOP
  X(ELOOP, "symbolic link loop")
#endif
#ifdef ENAMETOOLONG
  X(ENAMETOOLONG, "file name too long")
#endif
#ifdef EHOSTDOWN
  X(EHOSTDOWN, "host down")
#endif
#ifdef EHOSTUNREACH
  X(EHOSTUNREACH, "host unreachable")
#endif
#ifdef ENOTEMPTY
  X(ENOTEMPTY, "directory not empty")
#endif
#ifdef EPROCLIM
  X(EPROCLIM, "too many processes")
#endif
#ifdef EUSERS
  X(EUSERS, "too many users")
#endif
#ifdef EDQUOT
  X(EDQUOT, "disk quota exceeded")
#endif
#ifdef ESTALE
  X(ESTALE, "stale NFS file handle")
#endif
#ifdef EREMOTE
  X(EREMOTE, "too many levels of remote in path")
#endif
#ifdef EBADRPC
  X(EBADRPC, "RPC structure is bad")
#endif
#ifdef ERPCMISMATCH
  X(ERPCMISMATCH, "RPC version mismatch")
#endif
#ifdef EPROGUNAVAIL
  X(EPROGUNAVAIL, "RPC program unavailable")
#endif
#ifdef EPROGMISMATCH
  X(EPROGMISMATCH, "program version mismatch")
#endif
#ifdef EPROCUNAVAIL
  X(EPROCUNAVAIL, "bad procedure for program")
#endif
#ifdef ENOLCK
  X(ENOLCK, "no locks available")
#endif
#ifdef ENOSYS
  X(ENOSYS, "system call not available")
#endif
#ifdef EFTYPE
  X(EFTYPE, "bad file type")
#endif
#ifdef EAUTH
  X(EAUTH, "authentication error")
#endif
#ifdef ENEEDAUTH
  X(ENEEDAUTH, "not authenticated")
#endif
#ifdef ENOSTR
  X(ENOSTR, "not a stream device")
#endif
#ifdef ETIME
  X(ETIME, "timer expired")
#endif
#ifdef ENOSR
  X(ENOSR, "out of stream resources")
#endif
#ifdef ENOMSG
  X(ENOMSG, "no message of desired type")
#endif
#ifdef EBADMSG
  X(EBADMSG, "bad message type")
#endif
#ifdef EIDRM
  X(EIDRM, "identifier removed")
#endif
#ifdef ENONET
  X(ENONET, "machine not on network")
#endif
#ifdef ERREMOTE
  X(ERREMOTE, "object not local")
#endif
#ifdef ENOLINK
  X(ENOLINK, "link severed")
#endif
#ifdef EADV
  X(EADV, "advertise error")
#endif
#ifdef ESRMNT
  X(ESRMNT, "srmount error")
#endif
#ifdef ECOMM
  X(ECOMM, "communication error")
#endif
#ifdef EPROTO
  X(EPROTO, "protocol error")
#endif
#ifdef EMULTIHOP
  X(EMULTIHOP, "multihop attempted")
#endif
#ifdef EREMCHG
  X(EREMCHG, "remote address changed")
#endif
  return("unknown error");
}

#endif /*PLIB_H*/

