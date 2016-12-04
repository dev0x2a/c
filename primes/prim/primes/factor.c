#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>

#define whsiz (sizeof(wheel) / sizeof(wheel[0]))
#define OREAD 0
#define OWRITE 1
#define ORDWR 2
#define OEXEC 3
#define OTRUNC 16
#define OCEXEC 32
#define ORCLOSE 64
#define ODIRECT 128
#define ONONBLOCK 256
#define OEXCL 0x1000
#define OLOCK 0x2000
#define OAPPEND 0x4000
#define BGETC(bp)                                                              \
  ((bp)->icount ? (bp)->bbuf[(bp)->bsize + (bp)->icount++] : Bgetc((bp)))
#define BPUTC(bp, c)                                                           \
  ((bp)->ocount ? (bp)->bbuf[(bp)->bsize + (bp)->ocount++] = (c),              \
   0 : Bputc((bp), (c)))
#define BOFFSET(bp)                                                            \
  (((bp)->state == Bractive)                                                   \
       ? (bp)->offset + (bp)->icount                                           \
       : (((bp)->state == Bwactive)                                            \
              ? (bp)->offset + ((bp)->bsize + (bp)->ocount)                    \
              : -1))
#define BLINELEN(bp) (bp)->rdline
#define BFILDES(bp) (bp)->fid

typedef struct Biobuf Biobuf;
enum {
  Bsize = 8 * 1024,
  Bungetsize = 4,
  Bmagic = 0x314159,
  Beof = -1,
  Bbad = -2,

  Binactive = 0,
  Bractive,
  Bwactive,
  Bracteof,

  Bend
};

struct Biobuf {
  int icount;
  int ocount;
  int rdline;
  int runesize;
  int state;
  int fid;
  int flag;
  long long offset;
  int bsize;
  unsigned char *bbuf;
  unsigned char *ebuf;
  unsigned char *gbuf;
  unsigned char b[Bungetsize + Bsize];
};

double wheel[] = {
    2, 10, 2, 4, 2, 4, 6, 2, 6, 4, 2, 4, 6, 6, 2, 6, 4, 2, 6, 4, 6, 8, 4, 2,
    4, 2,  4, 8, 6, 4, 6, 2, 4, 6, 2, 6, 6, 4, 2, 4, 6, 2, 6, 4, 2, 4, 2, 10,
};

Biobuf bin;

int Binit(Biobuf *, int, int);
void *Brdline(Biobuf *, int);
int Bflush(Biobuf *);

void factor(double);

void main(int argc, char *argv[]) {
  double n;
  int i;
  char *l;

  if (argc > 1) {
    for (i = 1; i < argc; ++i) {
      n = atof(argv[i]);
      factor(n);
    }
    exit(0);
  }

  Binit(&bin, 0, OREAD);
  for (;;) {
    l = Brdline(&bin, '\n');
    if (l == 0)
      break;
    n = atof(l);
    if (n <= 0)
      break;
    factor(n);
  }
  exit(0);
}

void factor(double n) {
  double quot, d, s;
  int i;

  printf("%.0f\n", n);
  if (n == 0)
    return;
  s = sqrt(n) + 1;
  while (modf(n / 2, &quot) == 0) {
    printf("     2\n");
    n = quot;
    s = sqrt(n) + 1;
  }
  while (modf(n / 3, &quot) == 0) {
    printf("     3\n");
    n = quot;
    s = sqrt(n) + 1;
  }
  while (modf(n / 5, &quot) == 0) {
    printf("     5\n");
    n = quot;
    s = sqrt(n) + 1;
  }
  while (modf(n / 7, &quot) == 0) {
    printf("     7\n");
    n = quot;
    s = sqrt(n) + 1;
  }
  d = 1;
  for (i = 1;;) {
    d += wheel[i];
    while (modf(n / d, &quot) == 0) {
      printf("     %.0f\n", d);
      n = quot;
      s = sqrt(n) + 1;
    }
    ++i;
    if (i >= whsiz) {
      i = 0;
      if (d > s)
        break;
    }
  }
  if (n > 1)
    printf("     %.0f\n", n);
  printf("\n");
}

enum { MAXBUFS = 20 };

static Biobuf *wbufs[MAXBUFS];
static int atexitflag;

static void batexit(void) {
  Biobuf *bp;
  int i;

  for (i = 0; i < MAXBUFS; ++i) {
    bp = wbufs[i];
    if (bp != 0) {
      wbufs[i] = 0;
      Bflush(bp);
    }
  }
}

static void deinstall(Biobuf *bp) {
  int i;

  for (i = 0; i < MAXBUFS; ++i)
    if (wbufs[i] == bp)
      wbufs[i] = 0;
}

static void install(Biobuf *bp) {
  int i;

  deinstall(bp);
  for (i = 0; i < MAXBUFS; ++i)
    if (wbufs[i] == 0) {
      wbufs[i] = bp;
      break;
    }
  if (atexitflag == 0) {
    atexitflag = 1;
    atexit(batexit);
  }
}

int Binits(Biobuf *bp, int f, int mode, unsigned char *p, int size) {

  p += Bungetsize; /* make room for Bungets */
  size -= Bungetsize;

  switch (mode & ~(OCEXEC | ORCLOSE | OTRUNC)) {
  default:
    fprintf(stderr, "Bopen: unknown mode %d\n", mode);
    return Beof;

  case OREAD:
    bp->state = Bractive;
    bp->ocount = 0;
    break;

  case Owrite:
    install(bp);
    bp->state = Bwactive;
    bp->ocount = -size;
    break;
  }
  bp->bbuf = p;
  bp->ebuf = p + size;
  bp->bsize = size;
  bp->icount = 0;
  bp->gbuf = bp->ebuf;
  bp->fid = f;
  bp->flag = 0;
  bp->rdline = 0;
  bp->offset = 0;
  bp->runesize = 0;
  return 0;
}

int Binit(Biobuf *bp, int f, int mode) {
  return Binits(bp, f, mode, bp->b, sizeof(bp->b));
}

Biobuf *Bfdopen(int f, int mode) {
  Biobuf *bp;

  bp = malloc(sizeof(Biobuf));
  if (bp == 0)
    return 0;
  Binits(bp, f, mode, bp->b, sizeof(bp->b));
  bp->flag = Bmagic;
  return bp;
}

Biobuf *Bopen(char *name, int mode) {
  Biobuf *bp;
  int f;

  switch (mode & ~(OCEXEC | ORCLOSE | OTRUNC)) {
  default:
    fprintf(stderr, "Bopen: unknown mode %d\n", mode);
    return 0;

  case OREAD:
    f = open(name, mode);
    if (f < 0)
      return 0;
    break;

  case Owrite:
    f = create(name, mode, 0666);
    if (f < 0)
      return 0;
  }
  bp = Bfdopen(f, mode);
  if (bp == 0)
    close(f);
  return bp;
}

int Bterm(Biobuf *bp) {
  deinstall(bp);
  Bflush(bp);
  if (bp->flag == Bmagic) {
    bp->flag = 0;
    close(bp->fid);
    free(bp);
  }
  return 0;
}

void *Brdline(Biobuf *bp, int delim) {
  char *ip, *ep;
  int i, j;

  i = -bp->icount;
  if (i == 0) {
    /*
     * eof or other error
     */
    if (bp->state != Bractive) {
      if (bp->state == Bracteof)
        bp->state = Bractive;
      bp->rdline = 0;
      bp->gbuf = bp->ebuf;
      return 0;
    }
  }

  /*
   * first try in remainder of buffer (gbuf doesn't change)
   */
  ip = (char *)bp->ebuf - i;
  ep = memchr(ip, delim, i);
  if (ep) {
    j = (ep - ip) + 1;
    bp->rdline = j;
    bp->icount += j;
    return ip;
  }

  /*
   * copy data to beginning of buffer
   */
  if (i < bp->bsize)
    memmove(bp->bbuf, ip, i);
  bp->gbuf = bp->bbuf;

  /*
   * append to buffer looking for the delim
   */
  ip = (char *)bp->bbuf + i;
  while (i < bp->bsize) {
    j = read(bp->fid, ip, bp->bsize - i);
    if (j <= 0) {
      /*
       * end of file with no delim
       */
      memmove(bp->ebuf - i, bp->bbuf, i);
      bp->rdline = i;
      bp->icount = -i;
      bp->gbuf = bp->ebuf - i;
      return 0;
    }
    bp->offset += j;
    i += j;
    ep = memchr(ip, delim, j);
    if (ep) {
      /*
       * found in new piece
       * copy back up and reset everything
       */
      ip = (char *)bp->ebuf - i;
      if (i < bp->bsize) {
        memmove(ip, bp->bbuf, i);
        bp->gbuf = (unsigned char *)ip;
      }
      j = (ep - (char *)bp->bbuf) + 1;
      bp->rdline = j;
      bp->icount = j - i;
      return ip;
    }
    ip += j;
  }

  /*
   * full buffer without finding
   */
  bp->rdline = bp->bsize;
  bp->icount = -bp->bsize;
  bp->gbuf = bp->bbuf;
  return 0;
}

int Blinelen(Biobuf *bp) { return bp->rdline; }

int Bflush(Biobuf *bp) {
  int n, c;

  switch (bp->state) {
  case Bwactive:
    n = bp->bsize + bp->ocount;
    if (n == 0)
      return 0;
    c = write(bp->fid, bp->bbuf, n);
    if (n == c) {
      bp->offset += n;
      bp->ocount = -bp->bsize;
      return 0;
    }
    bp->state = Binactive;
    bp->ocount = 0;
    break;

  case Bracteof:
    bp->state = Bractive;

  case Bractive:
    bp->icount = 0;
    bp->gbuf = bp->ebuf;
    return 0;
  }
  return Beof;
}

int p9create(char *path, int mode, ulong perm) {
  int fd, cexec, umode, rclose, lock, rdwr;
  struct flock fl;

  rdwr = mode & 3;
  lock = mode & OLOCK;
  cexec = mode & OCEXEC;
  rclose = mode & ORCLOSE;
  mode &= ~(ORCLOSE | OCEXEC | OLOCK);

  /* XX X should get mode mask right? */
  fd = -1;
  if (perm & DMDIR) {
    if (mode != OREAD) {
      werrstr("bad mode in directory create");
      goto out;
    }
    if (mkdir(path, perm & 0777) < 0)
      goto out;
    fd = open(path, O_RDONLY);
  } else {
    umode = (mode & 3) | O_CREAT | O_TRUNC;
    mode &= ~(3 | OTRUNC);
    if (mode & ODIRECT) {
      umode |= O_DIRECT;
      mode &= ~ODIRECT;
    }
    if (mode & OEXCL) {
      umode |= O_EXCL;
      mode &= ~OEXCL;
    }
    if (mode & OAPPEND) {
      umode |= O_APPEND;
      mode &= ~OAPPEND;
    }
    if (mode) {
      werrstr("unsupported mode in create");
      goto out;
    }
    fd = open(path, umode, perm);
  }
out:
  if (fd >= 0) {
    if (lock) {
      fl.l_type = (rdwr == OREAD) ? F_RDLCK : F_WRLCK;
      fl.l_whence = SEEK_SET;
      fl.l_start = 0;
      fl.l_len = 0;
      if (fcntl(fd, F_SETLK, &fl) < 0) {
        close(fd);
        werrstr("lock: %r");
        return -1;
      }
    }
    if (cexec)
      fcntl(fd, F_SETFL, FD_CLOEXEC);
    if (rclose)
      remove(path);
  }
  return fd;
}

long p9write(int f, void *av, long n) {
  char *a;
  long m, t;

  a = av;
  t = 0;
  while (t < n) {
    m = write(f, a + t, n - t);
    if (m <= 0) {
      if (t == 0)
        return m;
      break;
    }
    t += m;
  }
  return t;
}
