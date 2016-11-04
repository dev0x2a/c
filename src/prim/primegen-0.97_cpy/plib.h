#ifndef PLIB_H
#define PLIB_H
#include<sys/types.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<fcntl.h>
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef long int64;

extern unsigned int str_copy();
extern int str_diff();
extern int str_diffn();
extern unsigned int str_len();
extern unsigned int str_chr();
extern unsigned int str_rchr();
extern int str_start();

extern substdio *subfdin;
extern substdio *subfdinsmall;
extern substdio *subfdout;
extern substdio *subfdoutsmall;
extern substdio *subfderr;
extern int subfd_read();
extern int subfd_readsmall();
#define str_equal(s,t) (!str_diff((s),(t)))
#define HASRDTSC 1
#define PRIMEGEN_WORDS 2048

typedef struct{
  uint32 buf[16][PRIMEGEN_WORDS];
  uint64 p[512];/*p[num-1] ... p[0], in that order*/
  int num;
  int pos;/*next entry to use in buf; WORDS to restart*/
  uint64 base;
  uint64 L;
}primegen;
extern void primegen_sieve(primegen*);
extern void primegen_fill(primegen*);
extern void primegen_init(primegen*);
extern uint64 primegen_next(primegen*);
extern uint64 primegen_peek(primegen*);
extern uint64 primegen_count(primegen*,uint64 to);
extern void primegen_skipto(primegen*,uint64 to);

typedef struct substdio{
  char*x;
  int p;
  int n;
  int fd;
  int(*op)();
}substdio;

extern void substdio_fdbuf();
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
extern char*substdio_peek();
extern void substdio_seek();
extern int substdio_copy();

#define SUBSTDIO_FDBUF(op,fd,buf,len) { (buf),0,(len),(fd),(op) }
#define substdio_fileno(s) ((s)->fd)
#define SUBSTDIO_INSIZE 8192
#define SUBSTDIO_OUTSIZE 8192
#define substdio_PEEK(s) ((s)->x+(s)->n)
#define substdio_SEEK(s,len) (((s)->p-=(len)),((s)->n+=(len)))
#define substdio_BPUTC(s,c)\
(((s)->n!=(s)->p)?((s)->x[(s)->p++]=(c),0):substdio_bput((s),&(c),1))

void substdio_fdbuf(s,op,fd,buf,len)
register substdio*s;
register int(*op)();
register int fd;
register char*buf;
register int len;
{ s->x=buf;
  s->fd=fd;
  s->op=op;
  s->p=0;
  s->n=len;
}
int substdio_copy(ssout,ssin)
register substdio*ssout;
register substdio*ssin;
{ register int n;
  register char*x;
  for(;;){
    n=substdio_feed(ssin);
    if(n<0)return(-2);
    if(!n)return(0);
    x=substdio_PEEK(ssin);
    if(substdio_put(ssout,x,n)==-1)return(-3);
    substdio_SEEK(ssin,n);
  }
}
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

extern char *error_str();
extern int error_temp();

extern void _exit();

extern int open_read();
extern int open_excl();
extern int open_append();
extern int open_trunc();
extern int open_write();

int open_read(fn)char*fn;
{ return(open(fn,O_RDONLY|O_NDELAY));
}
int open_trunc(fn)char*fn;
{ return(open(fn,O_WRONLY|O_NDELAY|O_TRUNC|O_CREAT,0644));
}

extern char auto_home[];

void hier()
{ h(auto_home,-1,-1,0755);
  d(auto_home,"bin",-1,-1,0755);
  d(auto_home,"lib",-1,-1,0755);
  d(auto_home,"include",-1,-1,0755);
  d(auto_home,"man",-1,-1,0755);
  d(auto_home,"man/man1",-1,-1,0755);
  d(auto_home,"man/cat1",-1,-1,0755);
  d(auto_home,"man/man3",-1,-1,0755);
  d(auto_home,"man/cat3",-1,-1,0755);
  c(auto_home,"include","primegen.h",-1,-1,0644);
  c(auto_home,"lib","primegen.a",-1,-1,0644);
  c(auto_home,"bin","primes",-1,-1,0755);
  c(auto_home,"bin","primegaps",-1,-1,0755);
  c(auto_home,"man/man1","primes.1",-1,-1,0644);
  c(auto_home,"man/man1","primegaps.1",-1,-1,0644);
  c(auto_home,"man/man3","primegen.3",-1,-1,0644);
  c(auto_home,"man/cat1","primes.0",-1,-1,0644);
  c(auto_home,"man/cat1","primegaps.0",-1,-1,0644);
  c(auto_home,"man/cat3","primegen.0",-1,-1,0644);
}
extern unsigned int scan_uint64(char*,uint64*);
extern unsigned int fmt_uint64(char*,uint64);

unsigned int scan_uint64(char *s,uint64 *u)
{ unsigned int pos=0;
  uint64 result=0;
  uint64 c;
  while((c=(uint64)(unsigned char)(s[pos]-'0'))<10){
    result=result*10+c;
    ++pos;
  }*u=result;
  return(pos);
}
unsigned int fmt_uint64(char *s,uint64 u)
{ unsigned int len=1;
  uint64 q=u;
  while(q>9){++len;q/=10;}
  if(s){s+=len;do{*--s='0'+(u%10);u/=10;}while(u);}
  return(len);
}

void primegen_init(primegen *pg)
{ pg->L=1;
  pg->base=60;
  pg->pos=PRIMEGEN_WORDS;
  pg->p[0]=59;
  pg->p[1]=53;
  pg->p[2]=47;
  pg->p[3]=43;
  pg->p[4]=41;
  pg->p[5]=37;
  pg->p[6]=31;
  pg->p[7]=29;
  pg->p[8]=23;
  pg->p[9]=19;
  pg->p[10]=17;
  pg->p[11]=13;
  pg->p[12]=11;
  pg->p[13]=7;
  pg->p[14]=5;
  pg->p[15]=3;
  pg->p[16]=2;
  pg->num=17;
}
/*
B is 32 times X.
Total memory use for one generator is 2B bytes = 64X bytes.
Covers primes in an interval of length 1920X.
Working set size for one generator is B bits = 4X bytes.

Speedup by a factor of 2 or 3 for L1 cache instead of L2 cache.
Slowdown by a factor of roughly n for primes past (nB)^2.

Possible choices of X:
  2002 to fit inside an 8K L1 cache (e.g., Pentium).
  4004 to fit inside a 16K L1 cache (e.g., Pentium II).
  64064 to fit inside a 256K L2 cache.

There are various word-size limits on X; 1000000 should still be okay.
*/
#define B32 PRIMEGEN_WORDS
#define B (PRIMEGEN_WORDS*32)

extern unsigned int byte_chr();
extern unsigned int byte_rchr();
extern void byte_copy();
extern void byte_copyr();
extern int byte_diff();
extern void byte_zero();
#define byte_equal(s,n,t) (!byte_diff((s),(n),(t)))

void byte_copy(to,n,from)
register char*to;
register unsigned int n;
register char*from;
{ for(;;){
    if(!n)return;*to++=*from++;--n;
    if(!n)return;*to++=*from++;--n;
    if(!n)return;*to++=*from++;--n;
    if(!n)return;*to++=*from++;--n;
  }
}
void byte_copyr(to,n,from)
register char*to;
register unsigned int n;
register char*from;
{ to+=n;
  from+=n;
  for(;;){
    if(!n)return;*--to=*--from;--n;
    if(!n)return;*--to=*--from;--n;
    if(!n)return;*--to=*--from;--n;
    if(!n)return;*--to=*--from;--n;
  }
}

extern int read();
extern int write();
int open_read(fn)char*fn;
{ return(open(fn,O_RDONLY|O_NDELAY));
}
int open_trunc(fn)char*fn;
{ return(open(fn,O_WRONLY|O_NDELAY|O_TRUNC|O_CREAT,0644));
}
struct strerr{
  struct strerr*who;
  char*x;
  char*y;
  char*z;
};
extern struct strerr strerr_sys;
extern void strerr_sysinit();
extern char*strerr();
extern void strerr_warn();
extern void strerr_die();
#define STRERR(r,se,a) {se.who=0;se.x=a;se.y=0;se.z=0;return(r);}
#define STRERR_SYS(r,se,a) {se.who=&strerr_sys;se.x=a;se.y=0;se.z=0;return(r);}
#define STRERR_SYS3(r,se,a,b,c)\
{se.who=&strerr_sys;se.x=a;se.y=b;se.z=c;return(r);}
#define strerr_warn6(x1,x2,x3,x4,x5,x6,se)\
strerr_warn((x1),(x2),(x3),(x4),(x5),(x6),(struct strerr*)(se))
#define strerr_warn5(x1,x2,x3,x4,x5,se)\
strerr_warn((x1),(x2),(x3),(x4),(x5),(char*)0,(struct strerr*)(se))
#define strerr_warn4(x1,x2,x3,x4,se)\
strerr_warn((x1),(x2),(x3),(x4),(char*)0,(char*)0,(struct strerr*)(se))
#define strerr_warn3(x1,x2,x3,se)\
strerr_warn((x1),(x2),(x3),(char*)0,(char*)0,(char*)0,(struct strerr*)(se))
#define strerr_warn2(x1,x2,se)\
strerr_warn((x1),(x2),(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)(se))
#define strerr_warn1(x1,se)\
strerr_warn((x1),(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)(se))
#define strerr_die6(e,x1,x2,x3,x4,x5,x6,se)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(x6),(struct strerr*)(se))
#define strerr_die5(e,x1,x2,x3,x4,x5,se)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(char*)0,(struct strerr*)(se))
#define strerr_die4(e,x1,x2,x3,x4,se)\
strerr_die((e),(x1),(x2),(x3),(x4),(char*)0,(char*)0,(struct strerr*)(se))
#define strerr_die3(e,x1,x2,x3,se)\
strerr_die((e),(x1),(x2),(x3),(char*)0,(char*)0,(char*)0,(struct strerr*)(se))
#define strerr_die2(e,x1,x2,se)\
strerr_die((e),(x1),(x2),(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)(se))
#define strerr_die1(e,x1,se)\
strerr_die((e),(x1),(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)(se))
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
strerr_die((e),(x1),(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,&strerr_sys)
#define strerr_die6x(e,x1,x2,x3,x4,x5,x6)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(x6),(struct strerr*)0)
#define strerr_die5x(e,x1,x2,x3,x4,x5)\
strerr_die((e),(x1),(x2),(x3),(x4),(x5),(char*)0,(struct strerr*)0)
#define strerr_die4x(e,x1,x2,x3,x4)\
strerr_die((e),(x1),(x2),(x3),(x4),(char*)0,(char*)0,(struct strerr*)0)
#define strerr_die3x(e,x1,x2,x3)\
strerr_die((e),(x1),(x2),(x3),(char*)0,(char*)0,(char*)0,(struct strerr*)0)
#define strerr_die2x(e,x1,x2)\
strerr_die((e),(x1),(x2),(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)0)
#define strerr_die1x(e,x1)\
strerr_die((e),(x1),(char*)0,(char*)0,(char*)0,(char*)0,(char*)0,(struct strerr*)0)
char subfd_errbuf[256];
static substdio it=SUBSTDIO_FDBUF(write,2,subfd_errbuf,256);
substdio*subfderr=&it;
typedef struct timeval timing_basic;
#define timing_basic_now(x) gettimeofday((x),(struct timezone *) 0)
#define timing_basic_diff(x,y) (1000.0*((x)->tv_usec-(double)(y)->tv_usec)+1000000000.0*((x)->tv_sec-(double)(y)->tv_sec))
#ifdef HASRDTSC
typedef struct{unsigned long t[2];}timing;
#define timing_now(x) asm volatile(".byte 15;.byte 49":"=a"((x)->t[0]),"=d"((x)->t[1]))
#define timing_diff(x,y) (((x)->t[0]-(double)(y)->t[0])+4294967296.0*((x)->t[1]-(double)(y)->t[1]))
#else
#ifdef HASGETHRTIME
typedef struct{hrtime_t t;}timing;
#define timing_now(x) ((x)->t=gethrtime())
#define timing_diff(x,y) ((double)((x)->t-(y)->t))
#else
#define timing timing_basic
#define timing_now timing_basic_now
#define timing_diff timing_basic_diff
#endif
#endif

unsigned int str_len(s)
register char*s;
{ register char*t;
  t=s;
  for(;;){
    if(!*t)return(t-s);++t;
    if(!*t)return(t-s);++t;
    if(!*t)return(t-s);++t;
    if(!*t)return(t-s);++t;
  }
}
#endif
