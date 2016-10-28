#include <stdio.h>
#include <ctype.h>

#define LINELEN 1024
#define ENTRIES 50

extern int errno, sys_nerr;
extern char *sys_errlist[];

static void
oops(msg)
char *msg;
{
  int s_errno=errno;
  fprintf(stderr,"fingerd: %s: ", msg);
  if (s_errno<sys_nerr)
    fprintf(stderr,"%s\n", sys_errlist[s_errno]);
  else
    fprintf(stderr, "errno = %d\n", s_errno);
  exit(1);
}

static char *
parse(line)
char **line;
{
  register char *next, *search=*line;
  if (!search)
    return(NULL);
  while (*search && isspace(*search))
    search++;
  if (!*search)
    return(NULL);
  next=search+1;
  while (*next && !isspace(*next))
    next++;;
  if (*next)
  {
    *next='\0';
    *line=++next;
  }
  else
    *line=NULL;
  return(search);
}

static char *av[ENTRIES+1] = {"finger"};
static char line[LINELEN];

int
main()
{
  FILE *fp;
  register int ix, ch;
  int child, p[2];
  char *ap, *lp;
  if (!fgets(line, LINELEN, stdin))
    exit(1);
  for (lp=line, ix=1; ix<ENTRIES; ix++)
  {
    if ((ap=parse(&lp))==NULL)
      break;
    /*  RFC742: "/[Ww]" == "-/" */
    if (ap[0]=='/' && (ap[1]=='W'||ap[1]=='w'))
      ap="-|";
    av[ix]=ap;
  }
  av[ix]=NULL;
  /*  call the "finger" program */
  if (pipe(p)<0)
    oops("pipe");
  child=fork();
  if (child==0)
  {
    (void)close(p[0]);
    if (p[1]!=1)
    {
      (void)dup2(p[1], 1);
      (void)close(p[1]);
    }
    execv("/usr/ucb/finger", av);
    _exit(1);
  }
  else if (child==-1)
    oops("form");
  /*  else, parent process */ 
  (void)close(p[1]);
  if (!(fp=fdopen(p[0], "r")))
    oops("fdopen");
  while ((ch=getc(fp))!=EOF)
  {
    if ((char)ch=='\n')
      putchar('\r');
    putchar((char)ch);
  }
  (void)wait(&child);
  return(child);
}

