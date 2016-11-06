#include"rogue.h"

int main(void)
{ 
  int ch;
  char **lvl;
  usr_t *user;
  
  lvl=__setmsp();
  __setscr();
  __setmap();
  user=__setuser();
  
  while((ch=getch())!='q'){
    __getin(ch,user);
  }
  
  endwin();
  return(0);
}

int __setscr(void)
{ 
  initscr();
  printw("... ");
  noecho();
  refresh();
  srand(time(NULL));
  return(ES);
}

