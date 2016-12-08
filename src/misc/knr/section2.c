/* strlen: return length of s */
int _strlen(char s[])
{
  int i;

  i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}

enum boolean { NO, YES };

enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t',
               NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };

enum months { JAN = 1, FEB, MAR, APR, MAY, JUN,
              JUL, AUG, SEP, OCT, NOV, DEC };
              /* FEB is 2, MAR is 3, etc. */

if ((year%4 == 0 && year%100 != 0) || year%400 == 0) printf("%d is a leap year\n", year);
else printf("%d is not a leap year\n", year);
  
/* atoi: convert s to integer */
int _atoi(char s[])
{
  int i, n;

  n = 0;
  for (i=0; s[i]>='0' && s[i]<='9'; ++i)
    n = 10*n+(s[i]-'0');
  return n;
}

/* lower: convert c to lower case; ASCII only */
int _lower(int c)
{
  if (c >= 'A' && c <= 'Z')
    return c+'a'-'A';
  else
    return c;
}

unsigned long int next = 1;

/* rand: return psuedo-random integer on 0..32767 */
int _rand(void)
{
  next = next*1103515245+12345;
  return (unsigned int)(next/65536)%32768;
}

/* srand: set seed for rand */
void _srand(unsigned int seed)
{
  next = seed;
}

/* squeeze: delete all c from s */
void _squeeze(char s[], int c)
{
  int i, j;

  for (i=j=0; s[i]!='\0'; i++)
    if (s[i] != c)
      s[j++] = s[i];
  s[j] = '\0';
}

/* strcat: concatenate t to end of s; s must be big enougb */
void _strcat(char s[], char t[])
{
  int i, j;

  i = j = 0;
  while (s[i] != '\0') /* find end of s */
    i++;
  while ((s[i++] = t[j++]) != '\0') /* copy t */
    ;
}

/* sets to zero all but the low-order 7 bits of n */
n = n & 0177;

/* turns bits on */
x = x | SET_ON;

/* converts each 1-bit into a 0-bit and vice versa */
x = x & ~077;

/* getbits: get n bits from position p */
unsigned _getbits(unsigned x, int p, int n)
{
  return (x >> (p+1-n)) & ~(~0 << n);
}

/* bitcount: count 1 bits in x */
int _bitcount(unsigned x)
{
  int b;

  for (b=0; x!=0; x>>=1)
    if (x & 01)
      b++;
  return b;
}

z = (a > b) ? a : b; /* z = max(a, b) */

