#include<ncurses.h>
#include<stdlib.h>

typedef struct _ent{
}ent_t;
typedef struct _itm{
}itm_t;
typedef struct _room{
  int dy;
  int dx;
  int dh;
  int dw;
  //ent_t **monst;
  //itm_t **items;
}room_t;
typedef struct _user{
  int dy;
  int dx;
  int hp;
}user_t;
int psetscr(void);
room_t **psetmap(void);
room_t *pmkroom(int ry,int rx,int rh,int rw);
int drwroom(room_t *room);
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
  //printw("... ");
  noecho();
  refresh();
  return(0);
}
room_t **psetmap(void)
{ room_t **room;
  room=malloc(sizeof(room_t)*6);
  room[0]=pmkroom(13,13,6,8);
  drwroom(room[0]);
  return(room);
}
room_t *pmkroom(int ry,int rx,int rh,int rw)
{ room_t *nroom;
  nroom=malloc(sizeof(room_t));
  nroom->dy=ry;
  nroom->dx=rx;
  nroom->dh=rh;
  nroom->dw=rw;
  return(nroom);
}
int drwroom(room_t *room)
{ int wy,wx;
  for(wx=room->dx;wx<room->dx+room->dw;++wx){
    mvprintw(room->dy,wx,"-");
    mvprintw(room->dy+room->dh,wx,"-");
  }
  for(wy=room->dy+1;wy<room->dy+room->dh;++wy){
    mvprintw(wy,room->dx,"|");
    mvprintw(wy,room->dx+room->dw-1,"|");
  }
  return(0);
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

