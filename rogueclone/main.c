#include<ncurses.h>
#include<stdlib.h>
#include<time.h>
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
  lcl_t **d;
  //ent_t **monst;
  //itm_t **items;
}rm_t;
typedef struct _user{
  lcl_t p;
  int hp;
  //room_t *rm;
}usr_t;
int psetscr(void);
rm_t **psetmap(void);
rm_t *pmkrm(int ry,int rx,int rh,int rw);
int drwrm(rm_t *rm);
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
  printw("... ");
  noecho();
  refresh();
  srand(time(NULL));
  return(0);
}
rm_t **psetmap(void)
{ rm_t **rm;
  rm=malloc(sizeof(rm_t)*6);
  rm[0]=pmkrm(13,13,6,8);
  drwrm(rm[0]);
  return(rm);
}
rm_t *pmkrm(int ry,int rx,int rh,int rw)
{ rm_t *rm;
  rm=malloc(sizeof(rm_t));
  rm->p.dy=ry;
  rm->p.dx=rx;
  rm->dh=rh;
  rm->dw=rw;

  rm->d=malloc(sizeof(lcl_t)*4);

  rm->d[0]=malloc(sizeof(lcl_t));
  rm->d[0]->dy=rm->p.dy;
  rm->d[0]->dx=rand()%rw+rm->p.dx;

  rm->d[1]=malloc(sizeof(lcl_t));
  rm->d[1]->dy=rm->p.dy+rm->dh-1;
  rm->d[1]->dx=rand()%rw+rm->p.dx;

  rm->d[2]=malloc(sizeof(lcl_t));
  rm->d[2]->dy=rand()%rw+rm->p.dy;
  rm->d[2]->dx=rm->p.dx;

  rm->d[3]=malloc(sizeof(lcl_t));
  rm->d[3]->dy=rand()%rw+rm->p.dy;
  rm->d[3]->dx=rm->p.dx+rw-1;
  return(rm);
}
int drwrm(rm_t *rm)
{ int y,x;
  for(x=rm->p.dx;x<rm->p.dx+rm->dw;++x){
    mvprintw(rm->p.dy,x,"-");
    mvprintw(rm->p.dy+rm->dh-1,x,"-");
  }
  for(y=rm->p.dy+1;y<rm->p.dy+rm->dh-1;++y){
    mvprintw(y,rm->p.dx,"|");
    mvprintw(y,rm->p.dx+rm->dw-1,"|");
    for(x=rm->p.dx+1;x<rm->p.dx+rm->dw-1;++x){
      mvprintw(y,x,".");
    }
  }
  mvprintw(rm->d[0]->dy,rm->d[0]->dx,"+");
  mvprintw(rm->d[1]->dy,rm->d[1]->dx,"+");
  mvprintw(rm->d[2]->dy,rm->d[2]->dx,"+");
  mvprintw(rm->d[3]->dy,rm->d[3]->dx,"+");
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

