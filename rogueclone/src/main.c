#include"rogue.h"
int main(void)
{ int ch;
  usr_t *user;
  p_setscr();
  p_setmap();
  user=p_setuser();
  while((ch=getch())!='q'){p_getin(ch,user);}
  endwin();
  return(0);
}
int p_setscr(void)
{ initscr();
  printw("... ");
  noecho();
  refresh();
  srand(time(NULL));
  return(ES);
}
