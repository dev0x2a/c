#include<ncurses.h>
#include<stdlib.h>

typedef struct _user{
  int dy;
  int dx;
  int hp;
}user_t;

int psetscr(void);
int psetmap(void);
int pgetin(int in,user_t *user);
int pmove(int y,int x,user_t *user);
int pcheckd(int ny,int nx,user_t *user);
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
  user->dy=14;
  user->dx=14;
  user->hp=20;
  pmove(14,14,user);
  return(user);
}
int pgetin(int in,user_t *user)
{ int ny,nx;
  switch(in){
    case('w'):case('W'):
      ny=user->dy-1;
      nx=user->dx;break;
    case('s'):case('S'):
      ny=user->dy+1;
      nx=user->dx;break;
    case('a'):case('A'):
      ny=user->dy;
      nx=user->dx-1;break;
    case('d'):case('D'):
      ny=user->dy;
      nx=user->dx+1;break;
    default:break;
  }
  pcheckd(ny,nx,user);
}
int pcheckd(int ny,int nx,user_t *user)
{ int s;
  switch(mvinch(ny,nx)){
    case('.'):pmove(ny,nx,user);break;
    default:move(user->dy,user->dx);break;
  }
}
int pmove(int y,int x,user_t *user)
{ mvprintw(user->dy,user->dx,".");
  user->dy=y;
  user->dx=x;
  mvprintw(user->dy,user->dx,"@");
  move(user->dy,user->dx);
}

