#define EEMPTY 0x0 //empty
#define EPAWN 0x1c0 //pawn
#define EROOK 0x1c100 //rook
#define EKNIGHT 0x1c101 //knight
#define EBISHOP 0x1c110 //bishop
#define EQUEEN 0x1c1110 //queen
#define EKING 0x1d1111 //king

#define EBEMPTY 0x20 //32 :empty board 32*1 bit
#define EBEPAWN 0x30 //48 :pawns 16*3 bits
#define EBELSE 0x3c //60: rooks/knights/bishops 12*5 bits
#define EBSPEC 0x18 //24 :queens/kings 4*6 bits
#define EBINIT 0xa4 //164 :total initial state

#define CAPTURE 0xfff

typedef unsigned int uint;
uint move;

void pmove(uint from, uint to, uint flag) {
  move = ((flag & 0xf)<<12) | ((from & 0x3f)<<6) | (to & 0x3f);
}

uint getto() {return move & 0x3f;}
uint getfrom() {return (move >> 6) & 0x3f;}
uint getflag() {return (move >> 12) & 0x0f;}

void setto(uint to) {
  move &= ~0x3f;
  move |= to & 0x3f;
}

void setfrom(uint from) {
  move &= ~0xfc0;
  move |= (from & 0x3f) << 6;
}

int capture() {
  return (move & CAPTURE) != 0;
}

