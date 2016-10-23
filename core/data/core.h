#ifndef CORE_H
#define CORE_H
#if 0
typedef uint64_t u64;
typedef char *out;

typedef struct system {
  char *host;
  char *date;
  char *load;
  char *root;
  char *user;
  char *kernel;
  char *uptime;
} sys_t;

typedef struct sys_t *root_dir {
  char *fslash;
} root_t;

typedef struct screen {
  int columns;
  int rows;
  int cursor;
  int x;
  int y;
} scr_t;

typedef struct prompt {
  char *put;

  int ret;
  int status;

  char *ls;
  char *cd;
  char *pwd;
  char *input;
  char *output;
} pro_t;

typedef struct currency {
  u64 bit;
  u64 byte;
  u64 kilabyte;
  u64 megabyte;
  u64 gigabyte;
  u64 terabyte;
  /*  ... */
} bit_t;

const scr_t.columns=80;
const scr_t.rows=25;
const scr_t.cursor=1;

static bit_t.bit=1;
static bit_t.byte=8;
static bit_t.kilabyte=1024;
static bit_t.megabyte=1048576;
static bit_t.gigabyte=1073741824;

char *
bin(int n)
{
  int c;
  char *p;
  c=0;
  p=(char*)malloc(32+1);
  if (p==NULL)
    exit(EXIT_FAILURE);
  for (int i=31; i>=0; --i) {
    if ((n>>i)&1)
      *(p+c)=1+'0';
    else
      *(p+c)=0+'0';
    ++count;
  }
  *(p+c)='\0';
  return(p);
}

void
bin_out(char *p)
{
  int n;
  p=bin(n);
  printf("%s", p);
  printf("\n");
  free(p);
}

out buffer;
out *output;
out spc;
int out_index;
int out_head;
int out_tail;
typedef int status;
status on;
status off;
status who;
clock_t last;
struct sys_t wd;
#endif
int 
dev_random(int r)
{
  return((rand()%r)+1);
}

void
tw(FILE *i, FILE *o)
{
  int c;
  int r=50000;
  while ((c=getc(i))!=EOF) {
    putc(c,o);
    usleep(r);
    fflush(stdout);
  }
}

void
tw_main(int argc, char *argv[])
{
  FILE *fp;
  char *name=argv[0];
  if (argc==1)
    tw(stdin, stdout);
  else
    while (--argc>0) {
      if ((fp=fopen(*++argv,"r"))==NULL) {
        fprintf(stderr,"%s: can't open %s\n", name,*argv);
        exit(1);
      } else {
        tw(fp,stdout);
        fclose(fp);
      }
    }
  if (ferror(stdout)) {
    fprintf(stderr, "%s: error writing to stdout\n", name);
    exit(2);
  }
  exit(0);
}
#endif

