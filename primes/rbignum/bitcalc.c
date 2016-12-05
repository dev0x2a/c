#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM '0'    /* signal that a number was found */
#define MAXOP 100  /* max size of operand or operator */
#define MAXVAL 100 /* max depth of val stack */
#define BUFSIZE 100

int getop(char *);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

char charset[] = {
  '+', '-', '*', '/', '>', '<', '^', '&', '|', '!', '~',
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'q',
  ' ', '\t', '\n'
};
static int err;

int main(int argc, char *argv[])
{
  int type;
  char s[MAXOP];
  double op;

  while ((type=getop(s)) != EOF) {
    switch (type) {
      case NUM:
        push(atof(s));
        break;
      case '+': /* + */
        push(pop()+pop());
        break;
      case '*': /* * */
        push(pop()*pop());
        break;
      case '-': /* - */
        op = pop();
        push(pop()-op);
        break;
      case '/': /* / */
        op = pop();
        if (op != 0.0) {
          push(pop()/op);
        }
        else {
          printf("err: divide by 0\n");
          err = 1;
        }
        break;
      case '>': /* >> */
        op = pop();
        push( ((int)pop()) >> (int)op);
        break;
      case '<': /* << */
        op = pop();
        push( ((int)pop()) << (int)op);
        break;
      case '^': /* ^ */
        push( ((int)pop()) ^ ((int)pop()) );
        break;
      case '&': /* & */
        push( ((int)pop()) & ((int)pop()) );
        break;
      case '|': /* | */
        push( ((int)pop()) | ((int)pop()) );
        break;
      case '!': /* ! */
        push( !((int)pop()) );
        break;
      case '~': /* ~ */
        push( ~((int)pop()) );
        break;
      case '\n':
        printf("\t%.08g\n", pop());
        break;
      case 'q':
        printf("kill signal received\n");
        exit(err);
      default:
        printf("err: unknown op %s\n", s);
        err = 1;
        break;
    }
  }
  return err;
}

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else {
    printf("err: stack full, cannot push %g\n", f);
    err = 1;
  }
}

double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else {
    printf("err: stack empty\n");
    err = 1;
    return 0.0;
  }
}

int getop(char *s)
{
  int i, c;

  while ((s[0]=c=getch()) == ' ' || c == '\t');
  s[1]= '\0';
  if (!isdigit(c) && c != '.')
    return c; /* nan */
  i = 0;
  if (isdigit(c))
    while (isdigit(s[++i]=c=getch()));
  if (c == '.')
    while (isdigit(s[++i]=c=getch()));
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUM;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many chars\n");
    err = 1;
  } else
    buf[bufp++] = c;
}

