
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
  int x, y;
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

const scr_t.columns = 80;
const scr_t.rows = 50;
const scr_t.cursor = 1;

static bit_t.bit = 1;
static bit_t.byte = 8;
static bit_t.kilabyte = 1024;
static bit_t.megabyte = 1048576;
static bit_t.gigabyte = 1073741824;

char *
bin(int num)
{
  int k, count;
  char *p;

  count = 0;
  p = (char*)malloc(32+1);

  if (p == NULL)
    exit(EXIT_FAILURE);

  for (int i=31; i>=0; --i) {
    k = num>>i;
    if (k&1)
      *(p+count) = 1 + '0';
    else
      *(p+count) = 0 + '0';
    ++count;
  }
  *(p+count) = '\0';
  return p;
}

int
bin_(char *p)
{
  int num;
  //char *p;
  p = bin(num);
  printf("%s", p);
  printf("\n");
  free(p);
  return 0;
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


int 
dev_random(int r)
{
  return (rand() % r) + 1;
}

