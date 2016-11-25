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

  psc_t rw1 = initpiece(ROOK, ALIVE, WH, H, 1);
  psc_t rw2 = initpiece(ROOK, ALIVE, WH, A, 1);
  psc_t nw1 = initpiece(KNIGHT, ALIVE, WH, G, 1);
  psc_t nw2 = initpiece(KNIGHT, ALIVE, WH, B, 1);
  psc_t bw1 = initpiece(BISHOP, ALIVE, WH, F, 1);
  psc_t bw2 = initpiece(BISHOP, ALIVE, WH, C, 1);
  psc_t qww = initpiece(QUEEN, ALIVE, WH, D, 1);
  psc_t kww = initpiece(KING, ALIVE, WH, E, 1);
  psc_t pw1 = initpiece(PAWN, ALIVE, WH, H, 2);
  psc_t pw2 = initpiece(PAWN, ALIVE, WH, G, 2);
  psc_t pw3 = initpiece(PAWN, ALIVE, WH, F, 2);
  psc_t pw4 = initpiece(PAWN, ALIVE, WH, E, 2);
  psc_t pw5 = initpiece(PAWN, ALIVE, WH, D, 2);
  psc_t pw6 = initpiece(PAWN, ALIVE, WH, C, 2);
  psc_t pw7 = initpiece(PAWN, ALIVE, WH, B, 2);
  psc_t pw8 = initpiece(PAWN, ALIVE, WH, A, 2);
  

  psc_t rb1 = initpiece(ROOK, ALIVE, BL, A, 8);
  psc_t rb2 = initpiece(ROOK, ALIVE, BL, H, 8);
  psc_t nb1 = initpiece(KNIGHT, ALIVE, BL, B, 8);
  psc_t nb2 = initpiece(KNIGHT, ALIVE, BL, G, 8);
  psc_t bb1 = initpiece(BISHOP, ALIVE, BL, C, 8);
  psc_t bb2 = initpiece(BISHOP, ALIVE, BL, F, 8);
  psc_t qbb = initpiece(QUEEN, ALIVE, BL, E, 8);
  psc_t kbb = initpiece(KING, ALIVE, BL, D, 8);
  psc_t pb1 = initpiece(PAWN, ALIVE, BL, A, 7);
  psc_t pb2 = initpiece(PAWN, ALIVE, BL, B, 7);
  psc_t pb3 = initpiece(PAWN, ALIVE, BL, C, 7);
  psc_t pb4 = initpiece(PAWN, ALIVE, BL, D, 7);
  psc_t pb5 = initpiece(PAWN, ALIVE, BL, E, 7);
  psc_t pb6 = initpiece(PAWN, ALIVE, BL, F, 7);
  psc_t pb7 = initpiece(PAWN, ALIVE, BL, G, 7);
  psc_t pb8 = initpiece(PAWN, ALIVE, BL, H, 7);


  printuser(white);
  printuser(black);

PRINTINFOMACRO(rw1,rw2,nw1,nw2,bw1,bw2,qww,kww);
PRINTINFOMACRO(pw1,pw2,pw3,pw4,pw5,pw6,pw7,pw8);

PRINTINFOMACRO(rb1,rb2,nb1,nb2,bb1,bb2,qbb,kbb);
PRINTINFOMACRO(pb1,pb2,pb3,pb4,pb5,pb6,pb7,pb8);

  FREE(white, black);
  FREE(rw1, rw2);
  FREE(nw1, nw2);
  FREE(bw1, bw2);
  FREE(qww, kww);
  FREE(pw1, pw2);
  FREE(pw3, pw4);
  FREE(pw5, pw6);
  FREE(pw7, pw8);

  FREE(rb1, rb2);
  FREE(nb1, nb2);
  FREE(bb1, bb2);
  FREE(qbb, kbb);
  FREE(pb1, pb2);
  FREE(pb3, pb4);
  FREE(pb5, pb6);
  FREE(pb7, pb8);

  emit(EF, "test error message", FILENM,LINENO);
  exit(ES);
}

