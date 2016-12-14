/* modified tomsfastmath code for my
   own personal project

   you probably shouldn't use this.. */
#include "rn.h"

void rn_gcd(rni *a, rni *b, rni *c)
{
  if (iszero(a)==1 && iszero(b)==0) {
    rn_abs(b, c);
    return;
  }
  if (iszero(a)==0 && iszero(b)==1) {
    rn_abs(a, c);
    return;
  }
  if (iszero(a) == 1) {
    zero(c);
    return;
  }
  rni u, v, r;
  if (rn_cmp_mag(a,b) != RN_LT) {
    initcpy(&u, a);
    initcpy(&v, b);
  } else {
    initcpy(&u, b);
    initcpy(&v, a);
  }
  zero(&r);
  while (iszero(&v) == RNN) {
    rn_mod(&u,&v,&r);
    rn_cpy(&v,&u);
    rn_cpy(&r,&v);
  }
  rn_cpy(&u,c);
}

void rn_lcm(rni *a, rni *b, rni *c)
{
  rni t1, t2;
  init(&t1);
  init(&t2);
  rn_gcd(a, b, &t1);
  if (rn_cmp_mag(a,b) == RN_GT) {
    rn_div(a, &t1, &t2, NULL);
    rn_mul(b, &t2, c);
  } else {
    rn_div(b, &t1, &t2, NULL);
    rn_mul(a, &t2, c);
  }
}

/* Miller-Rabin test of "a" to the base of "b" as described in
   HAC pp. 139 Algorithm 4.24
   Sets result to 0 if definitely composite or 1 if probably prime.
   Randomly the chance of error is no more than 1/4 and often
   very much lower */
void rn_pr_millrab(rni *a, rni *b, int *res)
{
  *res = RNN;
  if (rn_cmpd(b,1) != RN_GT)
    return;
  rni n1, y, r;
  initcpy(&n1, a);
  rn_subd(&n1, 1, &n1);

  initcpy(&r, &n1);
  int s=rn_cntlsb(&r), j;
  rn_div2d(&r, s, &r, NULL);
  init(&y);
  rn_expmod(b, &r, a, &y);

  if (rn_cmpd(&y,1)!=RN_EQ && rn_cmp(&y,&n1)!=RN_EQ) {
    j = 1;
    while ((j<=(s-1)) && rn_cmp(&y,&n1)!=RN_EQ) {
      rn_sqrmod(&y, a, &y);
      if (rn_cmpd(&y,1) == RN_EQ)
        return;
      ++j;
    }
    if (rn_cmp(&y,&n1) != RN_EQ)
      return;
  }
  *res = RNY;
}

int rn_isprime(rni *a, int t)
{
  if (t<=0 || t>PR_SIZ)
    return RNN;
  rnd d;
  int r, res;
  for (r=0; r<256; ++r) {
    rn_modd(a, primes[r], &d);
    if (d == 0)
      return RNN;
  }
  rni b;
  init(&b);
  for (r=0; r<t; ++r) {
    rn_set(&b, primes[r]);
    rn_pr_millrab(a, &b, &res);
    if (res == RNN)
      return RNN;
  }
  return RNY;
}

void rn_rand(rni *a, int dgt)
{
  zero(a);
  if (dgt <= 0)
    return;
  rnd d;
  do
    d = ((rnd)abs(rand()))&MASK;
  while (d == 0);
  rn_addd(a, d, a);
  while (--dgt > 0) {
    rn_lshd(a, 1);
    rn_addd(a, ((rnd)abs(rand())), a);
  }
  return;
}

int rn_pr_rand(rni *a, int t, int size, int flags,
               rn_prime_callback cb, void *dat)
{
  unsigned char *tmp, maskAND, maskOR_msb, maskOR_lsb;
  int res, err, bsize, maskOR_msb_offset;

  if (size<=1 || cb==NULL || t<=0 || t>PR_SIZ)
    return VAL;
  if (flags & PR_SAFE)
    flags |= PR_BBS;

  bsize = (size>>3)+(size&7 ? 1 : 0);
  tmp = malloc(bsize);
  if (tmp == NULL)
    return MEM;

  maskAND = 0xff>>((8-(size&7))&7);
  maskOR_msb = 0;
  maskOR_msb_offset = (size-2)>>3;

  if (flags & PR_2MSB_ON)
    maskOR_msb |= 1<<((size-2)&7);
  else if (flags & PR_2MSB_OFF)
    maskAND &= ~(1<<((size-2)&7));

  maskOR_lsb = 1;
  if (flags & PR_BBS)
    maskOR_lsb |= 3;
  do {
    if (cb(tmp, bsize, dat) != bsize) {
      err = VAL;
      goto error;
    }
    tmp[0] &= maskAND;
    tmp[0] |= 1<<((size-1)&7);

    tmp[maskOR_msb_offset] |= maskOR_msb;
    tmp[bsize-1] |= maskOR_lsb;

    rn_read_unsigned_bin(a, tmp, bsize);
    res = rn_isprime(a, t);
    if (res == RNN)
      continue;
    if (flags & PR_SAFE) {
      rn_subd(a, 1, a);
      rn_div2(a, a);
      res = rn_isprime(a, t);
    }
  } while (res == RNN);
  if (flags & PR_SAFE) {
    rn_mul2(a, a);
    rn_addd(a, 1, a);
  }
  err = OK;
error:
  free(tmp);
  return err;
}

