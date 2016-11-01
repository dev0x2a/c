#include<ncurses.h>
#include<stdlib.h>

//typedef struct _ent{
//}ent_t;
//typedef struct _itm{
//}itm_t;
typedef struct _locale{
  int dy;
  int dx;
}lcl_t;
typedef struct _room{
  lcl_t p;
  int dh;
  int dw;
  //ent_t **monst;
  //itm_t **items;
}rm_t;
typedef struct _user{
  lcl_t p;
  int hp;
  //room_t *room;
}usr_t;
int psetscr(void);
rm_t **psetmap(void);
rm_t *pmkroom(int ry,int rx,int rh,int rw);
int drwroom(rm_t *room);
int pgetin(int in,usr_t *user);
int pmove(int y,int x,usr_t *user);
int pcheckd(int ny,int nx,usr_t *user);
usr_t *psetuser(void);
int main()
{ int ch;
  usr_t *user;
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
rm_t **psetmap(void)
{ rm_t **room;
  room=malloc(sizeof(rm_t)*6);
  room[0]=pmkroom(13,13,6,8);
  drwroom(room[0]);
  return(room);
}
rm_t *pmkroom(int ry,int rx,int rh,int rw)
{ rm_t *nroom;
  nroom=malloc(sizeof(rm_t));
  nroom->p.dy=ry;
  nroom->p.dx=rx;
  nroom->dh=rh;
  nroom->dw=rw;
  return(nroom);
}
int drwroom(rm_t *room)
{ int y,x;
  for(x=room->p.dx;x<room->p.dx+room->dw;++x){
    mvprintw(room->p.dy,x,"-");
    mvprintw(room->p.dy+room->dh-1,x,"-");
  }
  for(y=room->p.dy+1;y<room->p.dy+room->dh-1;++y){
    mvprintw(y,room->p.dx,"|");
    mvprintw(y,room->p.dx+room->dw-1,"|");
    for(x=room->p.dx+1;x<room->p.dx+room->dw-1;++x){
      mvprintw(y,x,".");
    }
  }
  return(0);
}
usr_t *psetuser(void)
{ usr_t *user;
  user=malloc(sizeof(usr_t));
  user->p.dy=14;
  user->p.dx=14;
  user->hp=20;
  pmove(14,14,user);
  return(user);
}
int pgetin(int in,usr_t *user)
{ int ny,nx;
  switch(in){
    case('w'):case('W'):
      ny=user->p.dy-1;
      nx=user->p.dx;break;
    case('s'):case('S'):
      ny=user->p.dy+1;
      nx=user->p.dx;break;
    case('a'):case('A'):
      ny=user->p.dy;
      nx=user->p.dx-1;break;
    case('d'):case('D'):
      ny=user->p.dy;
      nx=user->p.dx+1;break;
    default:break;
  }
  pcheckd(ny,nx,user);
}
int pcheckd(int ny,int nx,usr_t *user)
{ int s;
  switch(mvinch(ny,nx)){
    case('.'):pmove(ny,nx,user);break;
    default:move(user->p.dy,user->p.dx);break;
  }
}
int pmove(int y,int x,usr_t *user)
{ mvprintw(user->p.dy,user->p.dx,".");
  user->p.dy=y;
  user->p.dx=x;
  mvprintw(user->p.dy,user->p.dx,"@");
  move(user->p.dy,user->p.dx);
}

