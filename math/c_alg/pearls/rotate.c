/*
 * rotate.c: time alg for rotating a vector
 *           *  1: reversal alg
 *           *  2: juggling alg
 *           * 22: juggling alg w/ mod (rather than if)
 *           *  3: gcd alg
 *           *  4: slide (don't rotate): baseline alg for timing
 *        To test the algs, add a call to testrot() w/in main()
 *
 * (c)1999 Lucent Tech
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 10000000

int x[MAXN];
int rotdist, n;

/* a1: rotatae by reversal */
void reverse(int i, int j)
{
  int t;
  while (i < j) {
    t = x[i];
    x[i] = x[j];
    x[j] = t;
    i++;
    j--;
  }
}

void revrot(int rotdist, int n)
{
  reverse(0, rotdist-1);
  reverse(rotdist, n-1);
  reverse(0, n-1);
}

/* a2: juggling (dolphin) rotation */
int gcd(int i, int j)
{
  int t;
  while (i != 0) {
    if (j >= i)
      j -= i;
    else {
      t = i;
      i = j;
      j = t;
    }
  }
  return j;
}

void jugglerot(int rotdist, int n)
{
  int cycles, i, j, k, t;

  cycles = gcd(rotdist, n);
  for (i=0; i<cycles; ++i) {
    /* move i-th values of blocks */
    t = x[i];
    j = i;
    for (;;) {
      k = j+rotdist;
      if (k >= n)
        k -= n;
      if (k == i)
        break;
      x[j] = x[k];
      j = k;
    }
    x[j] = t;
  }
}

void jugglerot2(int rotdist, int n)
{
  int cycles, i, j, k, t;

  cycles = gcd(rotdist, n);
  for (i=0; i<cycles; ++i) {
    /* move i-th values of blocks */
    t = x[i];
    j = i;
    for (;;) {
      /* replace w/ mod below
       * k = j+rotdist;
       * if (k >= n)
       * k -= n;
       */
      k = (j+rotdist)%n;
      if (k == i)
        break;
      x[j] = x[k];
      j = k;
    }
    x[j] = t;
  }
}

/* a3: recursive rotate (w/ gcd structure) */

void swap(int i, int j, int k) /* swap x[i..i+k-1] w/ 
                                *      x[j..j+k-1]    */
{
  int t;
  while (k-- > 0) {
    t = x[i];
    x[i] = x[j];
    x[j] = t;
    i++;
    j++;
  }
}

void gcdrot(int rotdist, int n)
{
  int i, j, p;

  if (rotdist==0 || rotdist==n)
    return;
  i = p = rotdist;
  j = n-p;
  while (i != j) {
    /* invariant:
     *      x[0  ..p-i  ] is in final position
     *      x[p-i..p-1  ] = a (to be swapped w/ b)
     *      x[p  ..p+j-1] = b (to be swapped w/ a)
     *      x[p+j..n-1  ] in final position
     */
    if (i > j) {
      swap(p-i, p, j);
      i -= j;
    } else {
      swap(p-i, p+j-i, i);
      j -= i;
    }
  }
  swap(p-i, p, i);
}

int isogcd(int i, int j)
{
  if (i == 0)
    return j;
  if (j == 0)
    return i;
  while (i != j) {
    if (i > j)
      i -= j;
    else
      j -= i;
  }
  return i;
}

void testgcd(void)
{
  int i, j;
  while (scanf("%d %d", &i, &j) != EOF)
    printf("%d\n", isogcd(i,j));
}

/* test all algs */
void slide(int rotdist, int n) /* benchmark: slide left rotdist
                                * (lose 0..rotdist-1) */
{
  int i;
  for (i=rotdist; i<n; ++i)
    x[i-rotdist] = x[i];
}

void initx(void)
{
  int i;
  for (i=0; i<n; ++i)
    x[i] = i;
}

void printx(void)
{
  int i;
  for (i=0; i<n; ++i)
    printf(" %d", x[i]);
  putchar('\n');
}

void roterror(void)
{
  fprintf(stderr, " rotate bug %d %d\n", n,rotdist);
  printx();
  exit(1);
}

void checkrot(void)
{
  int i;
  for (i=0; i<n-rotdist; ++i)
    if (x[i] != i+rotdist)
      roterror();
  for (i=0; i<rotdist; ++i)
    if (x[n-rotdist+i] != i)
      roterror();
}

void testrot(void)
{
  for (n=1; n<=20; ++n) {
    printf(" testing n=%d\n", n);
    for (rotdist=0; rotdist<=n; ++rotdist) {
      /* printf(" testing rotdist=%d\n", rotdist); */
      initx();
      revrot(rotdist, n);
      checkrot;

      initx();
      jugglerot(rotdist, n);
      checkrot;
      
      initx();
      jugglerot2(rotdist, n);
      checkrot;

      initx();
      gcdrot(rotdist, n);
      checkrot;
    }
  }
}

/* timing */
void timedriver(void)
{
  int i, algnum, numtests, start, clicks;

  while (scanf("%d %d %d %d", &algnum,&numtests,&n,&rotdist) != EOF) {
    initx();
    start = clock();
    for (i=0; i<numtests; ++i) {
      if (algnum == 1)
        revrot(rotdist, n);
      else if (algnum == 2)
        jugglerot(rotdist, n);
      else if (algnum == 3)
        jugglerot2(rotdist, n);
      else if (algnum == 4)
        gcdrot(rotdist, n);
    }
    clicks = clock()-start;
    printf("%d\t%d\t%d\t%d\t%d\t%g\n",
            algnum,numtests,n,rotdist,clicks,
            1e9*clicks/((float) CLOCKS_PER_SEC*n*numtests));
  }
}

/* main */

int main(void)
{
  /* testrot() */
  timedriver();
  return 0;
}

