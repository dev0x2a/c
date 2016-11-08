#include "plib.h"

uint32 mod10[200] = {
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9,
  0,1,2,3,4,5,6,7,8,9 ,0,1,2,3,4,5,6,7,8,9
};

uint32 div10[200] = {
  0,0,0,0,0,0,0,0,0,0 ,1,1,1,1,1,1,1,1,1,1,
  2,2,2,2,2,2,2,2,2,2 ,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4 ,5,5,5,5,5,5,5,5,5,5,
  6,6,6,6,6,6,6,6,6,6 ,7,7,7,7,7,7,7,7,7,7,
  8,8,8,8,8,8,8,8,8,8 ,9,9,9,9,9,9,9,9,9,9,
  10,10,10,10,10,10,10,10,10,10 ,11,11,11,11,11,11,11,11,11,11,
  12,12,12,12,12,12,12,12,12,12 ,13,13,13,13,13,13,13,13,13,13,
  14,14,14,14,14,14,14,14,14,14 ,15,15,15,15,15,15,15,15,15,15,
  16,16,16,16,16,16,16,16,16,16 ,17,17,17,17,17,17,17,17,17,17,
  18,18,18,18,18,18,18,18,18,18 ,19,19,19,19,19,19,19,19,19,19
};

uint64 low = 2;
uint64 high = 1000000000;
primegen pg;
uint32 digits[40];
int len;

int main(int argc, char *argv[])
{ 
  int i;
  uint64 p;
  uint32 u;
  if (argv[1]) {
    scan_uint64(argv[1], &low);
    if (argv[2])
      scan_uint64(argv[2], &high);
  }
  primegen_init(&pg);
  primegen_skipto(&pg, low);

  for (i=0; i<40; ++i)
    digits[i] = 0;
  
  p = primegen_peek(&pg);
  len = 0;
  
  do {
    digits[len++] = p%10;
    p /= 10;
  } while(p);
  
  p = primegen_peek(&pg);
  for (;;) {
    u = primegen_next(&pg)-p;
    p += u;
    if (p > high)
      break;
    for (i=0; u; ++i) {
      u += digits[i];
      if (u >= 200) {
        digits[i] = u%10;
        u /= 10;
      } else {
        digits[i] = mod10[u];
        u = div10[u];
      }
    }
    if (i>len)len=i;
    for (i=len-1; i>=0; --i)
      putchar('0'+digits[i]);
    putchar('\n');
  }
  exit(0);
}

