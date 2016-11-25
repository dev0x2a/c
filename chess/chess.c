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
  

  psc_t rb1 = initpiece(ROOK, ALIVE, BL, A, 1);
  psc_t rb2 = initpiece(ROOK, ALIVE, BL, H, 1);
  psc_t nb1 = initpiece(KNIGHT, ALIVE, BL, B, 1);
  psc_t nb2 = initpiece(KNIGHT, ALIVE, BL, G, 1);
  psc_t bb1 = initpiece(BISHOP, ALIVE, BL, C, 1);
  psc_t bb2 = initpiece(BISHOP, ALIVE, BL, F, 1);
  psc_t qbb = initpiece(QUEEN, ALIVE, BL, E, 1);
  psc_t kbb = initpiece(KING, ALIVE, BL, D, 1);
  psc_t pb1 = initpiece(PAWN, ALIVE, BL, A, 2);
  psc_t pb2 = initpiece(PAWN, ALIVE, BL, B, 2);
  psc_t pb3 = initpiece(PAWN, ALIVE, BL, C, 2);
  psc_t pb4 = initpiece(PAWN, ALIVE, BL, D, 2);
  psc_t pb5 = initpiece(PAWN, ALIVE, BL, E, 2);
  psc_t pb6 = initpiece(PAWN, ALIVE, BL, F, 2);
  psc_t pb7 = initpiece(PAWN, ALIVE, BL, G, 2);
  psc_t pb8 = initpiece(PAWN, ALIVE, BL, H, 2);



  printuser(white);
  printuser(black);
  
  printinfo(rw1);
  printinfo(rw2);

  FREE(white, black);
  FREE(rw1, rw2);

  emit(EF, "test error message", FILENM,LINENO);
  exit(ES);
}

