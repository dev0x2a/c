#include<ncurses.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//typedef struct _ent{
//}ent_t;
//typedef struct _itm{
//}itm_t;
//{{{
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
rm_t **p_setmap(void);
rm_t *p_mkrm(int ry,int rx,int rh,int rw);
usr_t *p_setuser(void);
int p_setscr(void);
int p_drwrm(rm_t *rm);
int p_cntd(lcl_t *d0,lcl_t *d1);
int p_getin(int in,usr_t *user);
int p_move(int y,int x,usr_t *user);
int p_checkd(int ny,int nx,usr_t *user);
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
  return(0);
}
rm_t **p_setmap(void)
{ rm_t **rm;
  rm=malloc(sizeof(rm_t)*6);
  rm[0]=p_mkrm(13,13,6,8);
  p_drwrm(rm[0]);
  rm[1]=p_mkrm(13,40,6,8);
  p_drwrm(rm[1]);
  p_cntd(rm[0]->d[3],rm[1]->d[1]);
  return(rm);
}
rm_t *p_mkrm(int ry,int rx,int rh,int rw)
{ rm_t *rm;
  rm=malloc(sizeof(rm_t));
  rm->p.dy=ry;
  rm->p.dx=rx;
  rm->dh=rh;
  rm->dw=rw;
  /**/
  rm->d=malloc(sizeof(lcl_t)*4);
  rm->d[0]=malloc(sizeof(lcl_t));
  rm->d[0]->dy=rm->p.dy;
  rm->d[0]->dx=rand()%(rw-2)+rm->p.dx+1;
  /**/
  rm->d[1]=malloc(sizeof(lcl_t));
  rm->d[1]->dy=rand()%(rh-2)+rm->p.dy+1;
  rm->d[1]->dx=rm->p.dx;
  /**/
  rm->d[2]=malloc(sizeof(lcl_t));
  rm->d[2]->dy=rm->p.dy+rm->dh-1;
  rm->d[2]->dx=rand()%(rw-2)+rm->p.dx+1;
  /**/
  rm->d[3]=malloc(sizeof(lcl_t));
  rm->d[3]->dy=rand()%(rh-2)+rm->p.dy+1;
  rm->d[3]->dx=rm->p.dx+rw-1;
  return(rm);
}
int p_drwrm(rm_t *rm)
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
//}}}
int p_cntd(lcl_t *d0,lcl_t *d1)
{ lcl_t tmp;
  tmp.dx=d0->dx;
  tmp.dy=d0->dy;
  while(1){
    if((abs((tmp.dx-1)-d1->dx)<abs(tmp.dx-d1->dx))&&(mvinch(tmp.dy,tmp.dx-1)==' ')){
      mvprintw(tmp.dy,tmp.dx-1,"#");
      tmp.dx=tmp.dx-1;
    }else if((abs((tmp.dx+1)-d1->dx)<abs(tmp.dx-d1->dx))&&(mvinch(tmp.dy,tmp.dx+1)==' ')){
      mvprintw(tmp.dy,tmp.dx+1,"#");
      tmp.dx=tmp.dx+1;
    }else if((abs((tmp.dy-1)-d1->dy)<abs(tmp.dy-d1->dy))&&(mvinch(tmp.dy-1,tmp.dx)==' ')){
      mvprintw(tmp.dy-1,tmp.dx,"#");
      tmp.dy=tmp.dy-1;
    }else if((abs((tmp.dy+1)-d1->dy)<abs(tmp.dy-d1->dy))&&(mvinch(tmp.dy+1,tmp.dx)==' ')){
      mvprintw(tmp.dy+1,tmp.dx,"#");
      tmp.dy=tmp.dy+1;
    }else{
      return(-1);
    }
    getch();
  }
  return(0);
}
usr_t *p_setuser(void)
{ usr_t *user;
  user=malloc(sizeof(usr_t));
  user->p.dy=14;
  user->p.dx=14;
  user->hp=20;
  p_move(14,14,user);
  return(user);
}
int p_getin(int in,usr_t *user)
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
  p_checkd(ny,nx,user);
  return(0);
}
int p_checkd(int ny,int nx,usr_t *user)
{ //int s;
  switch(mvinch(ny,nx)){
    case('.'):case('#'):case('+'):p_move(ny,nx,user);break;
    default:move(user->p.dy,user->p.dx);break;
  }
  return(0);
}
int p_move(int y,int x,usr_t *user)
{ mvprintw(user->p.dy,user->p.dx,".");
  user->p.dy=y;
  user->p.dx=x;
  mvprintw(user->p.dy,user->p.dx,"@");
  move(user->p.dy,user->p.dx);
  return(0);
}

