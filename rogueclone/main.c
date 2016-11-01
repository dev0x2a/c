#include<ncurses.h>
#include<stdlib.h>

typedef struct _user{
  int yo;
  int xo;
  int hp;
}user_t;

int psetscr(void);
int psetmap(void);
int pgetin(int in,user_t *user);
int pmove(int y,int x,user_t *user);
user_t *psetuser(void);

int main()
{ int ch;
  user_t *user;
  psetscr();
  psetmap();
  user=psetuser();
  while((ch=getch())!='q'){
    pgetin(ch,user);  
  }
  endwin();
  return(0);
}
int psetscr(void)
{ initscr();
  printw("... ");
  noecho();
  refresh();
  return(0);
}
int psetmap(void)
{ mvprintw(13,13,"--------");
  for(int i=14;i<=17;++i){
    mvprintw(i,13,"|......|");
  }
  mvprintw(18,13,"--------");
}
user_t *psetuser(void)
{ user_t *user;
  user=malloc(sizeof(user_t));
  user->yo=14;
  user->xo=14;
  user->hp=20;
  pmove(14,14,user);
  return(user);
}
int pgetin(int in,user_t *user)
{ switch(in){
    case 'w':
    case 'W':
      pmove(user->yo-1,user->xo,user);
      break;
    case 's':
    case 'S':
      pmove(user->yo+1,user->xo,user);
      break;
    case 'a':
    case 'A':
      pmove(user->yo,user->xo-1,user);
      break;
    case 'd':
    case 'D':
      pmove(user->yo,user->xo+1,user);
      break;
    default:break;
  }
}
int pmove(int y,int x,user_t *user)
{ mvprintw(user->yo,user->xo,".");
  user->yo=y;
  user->xo=x;
  mvprintw(user->yo,user->xo,"@");
  move(user->yo,user->xo);
}

