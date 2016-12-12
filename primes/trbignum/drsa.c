//[LISTING ONE]
/* Copyright (C) 1991-2 RSA Laboratories, a division of RSA Data
   Security, Inc. All rights reserved  */
/* PROTOTYPES should be set to one if and only if the compiler supports
function argument prototyping. The following makes PROTOTYPES default to 0
if it has not already been defined with C compiler flags  */
#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above. If using
  PROTOTYPES, PROTO_LIST returns the list, otherwise it returns empty list */
#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif

/* RSA key lengths */
#define MAX_RSA_MODULUS_BITS 1024
#define MAX_RSA_MODULUS_LEN ((MAX_RSA_MODULUS_BITS+7)/8)

typedef UINT4 NN_DIGIT;
typedef UINT2 NN_HALF_DIGIT;

/* Length of digit in bits */
#define NN_DIGIT_BITS 32
#define NN_HALF_DIGIT_BITS 16
/* Length of digit in bytes */
#define NN_DIGIT_LEN (NN_DIGIT_BITS/8)
/* Maximum length in digits */
#define MAX_NN_DIGITS \
  ((MAX_RSA_MODULUS_LEN+NN_DIGIT_LEN-1)/NN_DIGIT_LEN+1)
/* Maximum digits */
#define MAX_NN_DIGIT 0xffffffff
#define MAX_NN_HALF_DIGIT 0xffff

/* Macros */
#define LOW_HALF(x) (NN_HALF_DIGIT)((x)&MAX_NN_HALF_DIGIT)
#define HIGH_HALF(x) \
  (NN_HALF_DIGIT)(((x) >> NN_HALF_DIGIT_BITS) & MAX_NN_HALF_DIGIT)
#define TO_HIGH_HALF(x) (((NN_DIGIT)(x)) << NN_HALF_DIGIT_BITS)
#define DIGIT_MSB(x) (unsigned int)(((x) >> (NN_DIGIT_BITS-1)) & 1)
#define DIGIT_2MSB(x) (unsigned int)(((x) >> (NN_DIGIT_BITS-2)) & 3)

/* NOTE: A bug in the MPW 3.2 C compiler
causes an incorrect sign extension in the routine NN_DigitDiv
To overcome this bug, change the definition of the macro HIGH_HALF to:
#define HIGH_HALF(x) (((x) >> NN_HALF_DIGIT_BITS) & MAX_NN_HALF_DIGIT) */

void NN_Assign PROTO_LIST((NN_DIGIT *, NN_DIGIT *, unsigned int));
void NN_AssignZero PROTO_LIST((NN_DIGIT *, unsigned int));

NN_DIGIT NN_Add PROTO_LIST((NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int));
NN_DIGIT NN_Sub PROTO_LIST((NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int));
void NN_Mult PROTO_LIST((NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int));
int NN_Cmp PROTO_LIST((NN_DIGIT *, NN_DIGIT *, unsigned int));
unsigned int NN_Bits PROTO_LIST((NN_DIGIT *, unsigned int));
unsigned int NN_Digits PROTO_LIST((NN_DIGIT *, unsigned int));

NN_DIGIT NN_LShift PROTO_LIST((NN_DIGIT *, NN_DIGIT *, unsigned int,
                               unsigned int));
NN_DIGIT NN_RShift PROTO_LIST((NN_DIGIT *, NN_DIGIT *, unsigned int,
                               unsigned int));
void NN_Div PROTO_LIST((NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int,
                        NN_DIGIT *, unsigned int));
NN_DIGIT NN_AddDigitMult PROTO_LIST((NN_DIGIT *, NN_DIGIT *, NN_DIGIT,
                                     NN_DIGIT *, unsigned int));
NN_DIGIT NN_SubDigitMult PROTO_LIST((NN_DIGIT *, NN_DIGIT *, NN_DIGIT,
                                     NN_DIGIT *, unsigned int));
unsigned int NN_DigitBits PROTO_LIST((NN_DIGIT));
void NN_DigitMult PROTO_LIST((NN_DIGIT[2], NN_DIGIT, NN_DIGIT));
void NN_DigitDiv PROTO_LIST((NN_DIGIT *, NN_DIGIT[2], NN_DIGIT));

//[LISTING TWO]
/* Computes a=b+c. Returns carry. Lengths: a[digits], b[digits], c[digits] */
NN_DIGIT NN_Add(a, b, c, digits) NN_DIGIT *a, *b, *c;
unsigned int digits;
{
  NN_DIGIT ai, carry;
  unsigned int i;

  carry = 0;

  for (i=0; i<digits; ++i) {
    if ((ai = b[i]+carry) < carry)
      ai = c[i];
    else if ((ai += c[i]) < c[i])
      carry = 1;
    else
      carry = 0;
    a[i] = ai;
  }
  return (carry);
}

//[LISTING THREE]
/* Computes a=b-c. Returns borrow. Lengths: a[digits], b[digits], c[digits] */
NN_DIGIT NN_Sub(a, b, c, digits) NN_DIGIT *a, *b, *c;
unsigned int digits;
{
  NN_DIGIT ai, borrow;
  unsigned int i;

  borrow = 0;
  for (i=0; i<digits; ++i) {
    if ((ai = b[i]-borrow) > (MAX_NN_DIGIT-borrow))
      ai = MAX_NN_DIGIT-c[i];
    else if ((ai -= c[i]) > (MAX_NN_DIGIT-c[i]))
      borrow = 1;
    else
      borrow = 0;
    a[i] = ai;
  }
  return (borrow);
}

//[LISTING FOUR]
/* Computes a=b*c, where b and c are digits. Lengths: a[2] */
void NN_DigitMult(a, b, c) NN_DIGIT a[2], b, c;
{
  NN_DIGIT t, u;
  NN_HALF_DIGIT bHigh, bLow, cHigh, cLow;

  bHigh = HIGH_HALF(b);
  bLow = LOW_HALF(b);
  cHigh = HIGH_HALF(c);
  cLow = LOW_HALF(c);

  a[0] = (NN_DIGIT)bLow * (NN_DIGIT)cLow;
  t = (NN_DIGIT)bLow * (NN_DIGIT)cHigh;
  u = (NN_DIGIT)bHigh * (NN_DIGIT)cLow;
  a[1] = (NN_DIGIT)bHigh * (NN_DIGIT)cHigh;

  if ((t += u) < u)
    a[1] += TO_HIGH_HALF(1);
  u = TO_HIGH_HALF(t);

  if ((a[0] += u) < u)
    a[1]++;
  a[1] += HIGH_HALF(t);
}

//[LISTING FIVE]
/* Sets a=b/c, where a and c are digits. Lengths: b[2]. Assumes b[1] < c
   and HIGH_HALF (c) > 0. For efficiency, c should be normalized */
void NN_DigitDiv(a, b, c) NN_DIGIT *a, b[2], c;
{
  NN_DIGIT t[2], u, v;
  NN_HALF_DIGIT aHigh, aLow, cHigh, cLow;

  cHigh = HIGH_HALF(c);
  cLow = LOW_HALF(c);

  t[0] = b[0];
  t[1] = b[1];

  /* Underestimate high half of quotient and subtract product
     of estimate and divisor from dividend */
  if (cHigh == MAX_NN_HALF_DIGIT)
    aHigh = HIGH_HALF(t[1]);
  else
    aHigh = (NN_HALF_DIGIT)(t[1] / (cHigh+1));
  u = (NN_DIGIT)aHigh * (NN_DIGIT)cLow;
  v = (NN_DIGIT)aHigh * (NN_DIGIT)cHigh;
  if ((t[0] -= TO_HIGH_HALF(u)) > (MAX_NN_DIGIT-TO_HIGH_HALF(u)))
    t[1]--;
  t[1] -= HIGH_HALF(u);
  t[1] -= v;

  /* Correct estimate. */
  while ((t[1]>cHigh) || ((t[1]==cHigh) && (t[0]>=TO_HIGH_HALF(cLow)))) {
    if ((t[0] -= TO_HIGH_HALF(cLow)) > MAX_NN_DIGIT-TO_HIGH_HALF(cLow))
      t[1]--;
    t[1] -= cHigh;
    aHigh++;
  }
  /* Underestimate low half of quotient and subtract product of
     estimate and divisor from what remains of dividend */
  if (cHigh == MAX_NN_HALF_DIGIT)
    aLow = LOW_HALF(t[1]);
  else
    aLow = (NN_HALF_DIGIT)((NN_DIGIT)(TO_HIGH_HALF(t[1])+HIGH_HALF(t[0]))/
        (cHigh+1));
  u = (NN_DIGIT)aLow * (NN_DIGIT)cLow;
  v = (NN_DIGIT)aLow * (NN_DIGIT)cHigh;
  if ((t[0] -= u) > (MAX_NN_DIGIT-u))
    t[1]--;
  if ((t[0] -= TO_HIGH_HALF(v)) > (MAX_NN_DIGIT-TO_HIGH_HALF(v)))
    t[1]--;
  t[1] -= HIGH_HALF(v);

  /* Correct estimate */
  while ((t[1]>0) || ((t[1]==0) && t[0]>=c)) {
    if ((t[0] -= c) > (MAX_NN_DIGIT-c))
      t[1]--;
    aLow++;
  }
  *a = TO_HIGH_HALF(aHigh)+aLow;
}

//[LISTING SIX]
/* Computes a=b+c*d, where c is a digit. Returns carry
   Lengths: a[digits], b[digits], d[digits] */
NN_DIGIT NN_AddDigitMult(a, b, c, d, digits) NN_DIGIT *a, *b, c, *d;
unsigned int digits;
{
  NN_DIGIT carry, t[2];
  unsigned int i;

  carry = 0;
  for (i=0; i<digits; ++i) {
    NN_DigitMult(t, c, d[i]);
    if ((a[i] = b[i]+carry) < carry)
      carry = 1;
    else
      carry = 0;
    if ((a[i] += t[0]) < t[0])
      carry++;
    carry += t[1];
  }
  return (carry);
}

//[LISTING SEVEN]
/* Computes a=b*c. Lengths: a[2*digits], b[digits], c[digits]
   Assumes digits < MAX_NN_DIGITS */
void NN_Mult(a, b, c, digits) NN_DIGIT *a, *b, *c;
unsigned int digits;
{
  NN_DIGIT t[2*MAX_NN_DIGITS];
  unsigned int bDigits, cDigits, i;

  NN_AssignZero(t, 2*digits);

  bDigits = NN_Digits(b, digits);
  cDigits = NN_Digits(c, digits);

  for (i=0; i<bDigits; ++i)
    t[i+cDigits] += NN_AddDigitMult(&t[i], &t[i], b[i], c, cDigits);
  NN_Assign(a, t, 2*digits);
}

//[LISTING EIGHT]
/* Computes a=b-c*d, where c is a digit. Returns borrow
   Lengths: a[digits], b[digits], d[digits] */
NN_DIGIT NN_SubDigitMult(a, b, c, d, digits) NN_DIGIT *a, *b, c, *d;
unsigned int digits;
{
  NN_DIGIT borrow, t[2];
  unsigned int i;

  borrow = 0;
  for (i=0; i<digits; ++i) {
    NN_DigitMult(t, c, d[i]);
    if ((a[i] = b[i]-borrow) > (MAX_NN_DIGIT-borrow))
      borrow = 1;
    else
      borrow = 0;
    if ((a[i] -= t[0]) > (MAX_NN_DIGIT-t[0]))
      borrow++;
    borrow += t[1];
  }
  return (borrow);
}

//[LISTING NINE]
/* Computes a=c div d and b=c mod d. Lengths: a[cDigits], b[dDigits],
   c[cDigits], d[dDigits]. Assumes d > 0, cDigits < 2 * MAX_NN_DIGITS,
   dDigits < MAX_NN_DIGITS */
void NN_Div(a, b, c, cDigits, d, dDigits) NN_DIGIT *a, *b, *c, *d;
unsigned int cDigits, dDigits;
{
  NN_DIGIT ai, cc[2*MAX_NN_DIGITS+1], dd[MAX_NN_DIGITS], t;
  int i;
  unsigned int ddDigits, shift;

  ddDigits = NN_Digits(d, dDigits);
  if (ddDigits == 0)
    return;

  //[LISTING TEN]
  /* Normalize operands */
  shift = NN_DIGIT_BITS-NN_DigitBits(d[ddDigits-1]);
  NN_AssignZero(cc, ddDigits);
  cc[cDigits] = NN_LShift(cc, c, shift, cDigits);
  NN_LShift(dd, d, shift, ddDigits);
  t = dd[ddDigits-1];

  NN_AssignZero(a, cDigits);

  for (i=cDigits-ddDigits; i>=0; --i) {
    /* Underestimate quotient digit and subtract */
    if (t == MAX_NN_DIGIT)
      ai = cc[i+ddDigits];
    else
      NN_DigitDiv(&ai, &cc[i+ddDigits-1], t+1);
    cc[i+ddDigits] -= NN_SubDigitMult(&cc[i], &cc[i], ai, dd, ddDigits);
    /* Correct estimate */
    while (cc[i+ddDigits] || (NN_Cmp(&cc[i], dd, ddDigits)>=0)) {
      ai++;
      cc[i+ddDigits] -= NN_Sub(&cc[i], &cc[i], dd, ddDigits);
    }
    a[i] = ai;
  }
  /* Restore result */
  NN_AssignZero(b, dDigits);
  NN_RShift(b, cc, shift, ddDigits);
}

