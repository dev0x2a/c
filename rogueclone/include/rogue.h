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
rm_t **p_setmap(void);
rm_t *p_mkrm(int ry,int rx,int rh,int rw);
usr_t *p_setuser(void);
int p_setscr(void);
int p_drwrm(rm_t *rm);
int p_cntd(lcl_t *d0,lcl_t *d1);
int p_getin(int in,usr_t *user);
int p_move(int y,int x,usr_t *user);
int p_checkd(int ny,int nx,usr_t *user);

#endif
