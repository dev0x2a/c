#include<stdio.h>

typedef struct hopsieve{
  int n;      /*'current num'                     */
  int nindex; /*corresponding index into pbuf,dbuf*/
  int S;      /*num of entries in pbuf,dbuf       */
  int *pbuf;
  int *dbuf;
}hopsieve_t;

