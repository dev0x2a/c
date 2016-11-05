#ifndef ROGUE_H
#define ROGUE_H

#include<ncurses.h>
#include<stdlib.h>
#include<time.h>
#define ES EXIT_SUCCESS
#define EF EXIT_FAILURE
#define M_ES 0
#define M_EF -1
#define P_EF NULL
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
char **__setmap(void);
rm_t *__mkrm(int ry,int rx,int rh,int rw);
usr_t *__setuser(void);
int __setscr(void);
int __drwrm(rm_t *rm);
int __cntd(lcl_t *d0,lcl_t *d1);
int __getin(int in,usr_t *user);
int __move(int y,int x,usr_t *user);
int __checkd(int ny,int nx,usr_t *user);

#endif
