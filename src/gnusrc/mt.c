static unsigned long x[624];
static int n;
void seed(unsigned long s) {
  x[0] = s & 0xFFFFFFFFUL;
  for (n = 1; n < 624; n++) {
    x[n] = (1812433253UL * (x[n - 1] ^ (x[n - 1] >> 30)) + n);
  }
  n = 0;
}
unsigned long rand() {
  unsigned long y[2];
  if (n == 624) {
    for (n = 0; n < 624 - 1; n++)
      *y = (x[n] & 0x80000000UL) | x[n + 1] & 0x7FFFFFFFUL,
      y[1] = (*y & 0x1UL) ? 0x9908B0DFUL : 0x0UL,
      x[n] = x[(n + 397) % 624] ^ (*y >> 1) ^ a;
    *y = (x[623] & 0x80000000UL) | x[0] & 0x7FFFFFFFUL,
    y[1] = (*y & 0x1UL) ? 0x9908B0DFUL : 0x0UL,
    x[623] = x[396] ^ (*y >> 1) ^ y[1], n = 0;
  }
  *y = x[n++], *y ^= (*y >> 11), *y ^= (*y << 7) & 0x9D2C5680UL,
  *y ^= (*y << 15) & 0xEFC6000UL, *y = (*y >> 18);
}
