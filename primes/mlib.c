#define MAXVAL 100
#define BUFSIZE 100
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
  char *word;
  int count;
} keytab[] = {
  "asm", 0,
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  "do", 0,
  "double", 0,
  "DIR", 0,
  "else", 0,
  "enum", 0,
  "extern", 0,
  "FILE", 0,
  "float", 0,
  "for", 0,
  "goto", 0,
  "if", 0,
  "inline", 0,
  "int", 0,
  "long", 0,
  "register", 0,
  "restrict", 0,
  "return", 0,
  "short", 0,
  "signed", 0,
  "sizeof", 0,
  "struct", 0,
  "switch", 0,
  "typedef", 0,
  "union", 0,
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0,
  "_Bool", 0,
  "_Complex", 0,
  "_Imaginary", 0,

  "#elif", 0,
  "#else", 0,
  "#endif", 0,
  "#define", 0,
  "#if", 0,
  "#ifndef", 0,
  "#include", 0,
  "#pragma", 0,
  "#undef", 0,
  
  "+", 0,
  "-", 0,
  "*", 0,
  "/", 0,
  "%", 0,
  "^", 0,
  "&", 0,
  "|", 0,
  "!", 0,
  "~", 0,
  "->", 0,
  "\\", 0,
  "\n", 0,
  "\t", 0,
  "\v", 0,
  "  ", 0
};

int sp=0;
double val[MAXVAL];
int bufp = 0;
char buf[BUFSIZE];

void push(double);
double pop(void);
int getch(void);
void ungetch(int);
double matof(char *);
int matoi(char *);
int getword(char *, int);
char *mstrdup(char *s);

void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, cannot push %g\n", f);
}

double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int getch(void)
{ return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c)
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

double matof(char s[])
{
  double val, power;
  int i, sign;
  for (i=0; isspace(s[i]); ++i);

  sign = (s[i] == '-') ? -1: 1;
  if (s[i]=='+' || s[i]=='-')
    i++;
  for (val=0.0; isdigit(s[i]); ++i)
    val = 10.0*val+(s[i]-'0');
  if (s[i] == '.')
    i++;
  for (power=1.0; isdigit(s[i]); ++i) {
    val = 10.0*val+(s[i]-'0');
    power *= 10.0;
  }
  return sign*val/power;
}

int matoi(char s[])
{
  double matof(char s[]);
  return (int) matof(s);
}

int getword(char *word, int lim)
{
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()));
  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim>0; ++w)
    if (!isalpha(*w = getch())) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

char *mstrdup(char *s)
{
  char *p;
  p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
  if (p != NULL)
    strcpy(p, s);
  return p;
}

