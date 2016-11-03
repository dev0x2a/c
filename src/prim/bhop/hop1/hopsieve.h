#include<stdio.h>

typedef struct hopsieve{
  int n;  /*'current num'         */
  int n0; /*start val for n       */
  int S;  /*num of entries in pbuf*/
  int *pbuf;
}hopsieve_t;

/* given hopsieve_t *sv, convert m to 'prime @ m' */
#define P(sv,m) sv->pbuf[((m)-(sv->n0))%(sv->S)]

