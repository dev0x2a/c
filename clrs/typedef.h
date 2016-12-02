#ifndef CLRS_H
#define CLRS_H

/*
 * "Introduction to Algorithms, CLRS"
 * standard header by Ryan Keleti
 * 
 * @ryankeleti
 */

#include <stddef.h>

typedef unsigned char       u8;   /*              0 : 225           */
typedef signed char         s8;   /*           -128 : 127           */
typedef unsigned short      u16;  /*              0 : 65535         */
typedef signed short        s16;  /*         -32768 : 32767         */
typedef unsigned long       u32;  /*              0 : 4.294967295e9 */
typedef signed long         s32;  /* -2.147483648e9 : 2.147483647e9 */
typedef signed long long    s64;
typedef unsigned long long  u64;
typedef unsigned char       byte;

typedef enum bool {FALSE, TRUE} bool;
typedef size_t elem_t;
typedef unsigned char bit;
typedef char* string;

typedef struct dynarr_st {
  int *data;
  size_t cap, size;
} vector;

typedef struct voidvec_st {
  byte *data;
  /* cap >= size; elemsize = size in bytes of sizeof(TYPE) */
  size_t cap, size, elemsize;
  void (*elemfree)(void*);
  void (*eleminit)(void*,void*);
} vvector;


