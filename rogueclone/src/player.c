#include"rogue.h"
int __cntd(lcl_t *d0,lcl_t *d1)
{ lcl_t tmp;
  lcl_t prv;
  int c=0;
  tmp.dx=d0->dx;
  tmp.dy=d0->dy;
  prv=tmp;
  while(1){
    if((abs((tmp.dx-1)-d1->dx)<abs(tmp.dx-d1->dx))&&(mvinch(tmp.dy,tmp.dx-1)==' ')){
      prv.dx=tmp.dx;
      tmp.dx=tmp.dx-1;
    }else if((abs((tmp.dx+1)-d1->dx)<abs(tmp.dx-d1->dx))&&(mvinch(tmp.dy,tmp.dx+1)==' ')){
      prv.dx=tmp.dx;
      tmp.dx=tmp.dx+1;
    }else if((abs((tmp.dy-1)-d1->dy)<abs(tmp.dy-d1->dy))&&(mvinch(tmp.dy-1,tmp.dx)==' ')){
      prv.dy=tmp.dy;
      tmp.dy=tmp.dy-1;
    }else if((abs((tmp.dy+1)-d1->dy)<abs(tmp.dy-d1->dy))&&(mvinch(tmp.dy+1,tmp.dx)==' ')){
      prv.dy=tmp.dy;
      tmp.dy=tmp.dy+1;
    }else{
      if(c==0){
        tmp=prv;
        ++c;
        continue;
      }else{
        return(EF);
      }
    }
    mvprintw(tmp.dy,tmp.dx,"#");
    getch();
  }
  return(ES);
}
usr_t *__setuser(void)
{ usr_t *user;
  user=malloc(sizeof(usr_t));
  user->p.dy=14;
  user->p.dx=14;
  user->hp=20;
  __move(14,14,user);
  return(user);
}
int __getin(int in,usr_t *user)
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
  __checkd(ny,nx,user);
  return(ES);
}
int __checkd(int ny,int nx,usr_t *user)
{ //int s;
  switch(mvinch(ny,nx)){
    case('.'):case('#'):case('+'):__move(ny,nx,user);break;
    default:move(user->p.dy,user->p.dx);break;
  }
  return(ES);
}
int __move(int y,int x,usr_t *user)
{ mvprintw(user->p.dy,user->p.dx,".");
  user->p.dy=y;
  user->p.dx=x;
  mvprintw(user->p.dy,user->p.dx,"@");
  move(user->p.dy,user->p.dx);
  return(ES);
}

