#include"rogue.h"
char **__setmap(void)
{ rm_t **rm;
  rm=malloc(sizeof(rm_t)*6);
  rm[0]=__mkrm(13,13,6,8);
  __drwrm(rm[0]);
  rm[1]=__mkrm(13,40,6,8);
  __drwrm(rm[1]);
  __cntd(rm[0]->d[3],rm[1]->d[1]);
  return(rm);
}
rm_t *__mkrm(int ry,int rx,int rh,int rw)
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
int __drwrm(rm_t *rm)
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
  return(ES);
}
