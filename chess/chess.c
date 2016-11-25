#include "chess.h"

int main(void)
{
  disp_t disp;
  initboard(&disp);
  pboard(&disp);

  usr_t white;
  usr_t black;

  white = inituser(WH);
  black = inituser(BL);

  white->turn = 1;
  white->status = 1;

  black->turn = 0;
  black->status = 1;

  printuser(white);
  printuser(black);

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
  psc_t rw1 = initpiece(ROOK, ALIVE, WH, H, 1);
  psc_t rw2 = initpiece(ROOK, ALIVE, WH, A, 1);

emit(EF, "line38?", FILENM,LINENO);

  printinfo(rw1);
  printinfo(rw2);

  free(white);
  free(black);
  free(rw1);
  free(rw2);
  exit(ES);
}

