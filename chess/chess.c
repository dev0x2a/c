#include "chess.h"

int main(void)
{
  disp_t disp;
  initboard(&disp);
  pboard(&disp);

  psc_t rw1, rw2;
#if 0
  psc_t kw1, kw2;
  psc_t bw1, bw2;
  psc_t quw, kiw;
  psc_t pw1, pw2, pw3, pw4, pw5, pw6, pw7, pw8;
  psc_t rb1, rb2;
  psc_t kb1, kb2;
  psc_t bb1, bb2;
  psc_t qub, kib;
  psc_t pb1, pb2, pb3, pb4, pb5, pb6, pb7, pb8;
#endif
  rw1 = initpiece(ROOK, 1, WH, H, 1);
  rw2 = initpiece(ROOK, 1, WH, A, 1);
#if 0
  kw1 = initpiece(KNIGHT, 1, WH, G, 1);
  kw2 = initpiece(KNIGHT, 1, WH, B, 1);
  bw1 = initpiece(BISHOP, 1, WH, H, 1);
  bw2 = initpiece(BISHOP, 1, WH, H, 1);
  quw = initpiece(QUEEN, 1, WH, H, 1);
  kiw = initpiece(KING, 1, WH, H, 1);

  rb1 = initpiece(1, 1, BL, H, 1);
  rb2 = initpiece(1, 1, BL, H, 1);
#endif
  printinfo(rw1);
  printinfo(rw2);

  free(rw1);
  free(rw2);
  exit(0);
}

