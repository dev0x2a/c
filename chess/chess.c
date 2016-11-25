#include "chess.h"

int main(void)
{
  disp_t disp;
  initboard(&disp);
  pboard(&disp);

  usr_t white = inituser(WH);
  usr_t black = inituser(BL);

  white->turn = 1;
  white->status = 1;

  black->turn = 0;
  black->status = 1;


#if 0
  psc_t rw1, rw2, kw1, kw2, bw1, bw2, qw,  kw;
  psc_t pw1, pw2, pw3, pw4, pw5, pw6, pw7, pw8;
  psc_t rb1, rb2, kb1, kb2, bb1, bb2, qb,  kb;
  psc_t pb1, pb2, pb3, pb4, pb5, pb6, pb7, pb8;
#endif
  psc_t rw1 = initpiece(ROOK, ALIVE, WH, H, 1);
  psc_t rw2 = initpiece(ROOK, ALIVE, WH, A, 1);
  

  printuser(white);
  printuser(black);
  
  printinfo(rw1);
  printinfo(rw2);

  FREE(white, black);
  FREE(rw1, rw2);

  emit(EF, "test error message", FILENM,LINENO);
  exit(ES);
}

