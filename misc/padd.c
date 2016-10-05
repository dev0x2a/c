#include <stdio.h>
#include <stdlib.h>

/*
 *        *(Arr + 7)  -->   (Arr + 7)
 *        *(7 + Arr)  -->   (7 + Arr)
 *        Arr[7]      -->   & Arr[7]
 *        7[Arr]      -->   & 7[Arr]
 *        *& 7[Arr]   -->   &*& 7[Arr]
 *
 */

int
err(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "%s <num>\n", argv[0]);
    return(-1);
  }
}

int
main(int argc, char *argv[])
{
  err(argc, argv);
  
  int num;
  num = atol(argv[1]);

  char arr[30][num];
  char (*arr11)[num] = &arr[11];
  char (*arr13)[num] = arr + 13;    /*  same as &arr[13]  */

  printf("arr13 - arr11 = %d\n", arr13-arr11);
  printf("arr13 - arr11 = %d\n", (int)arr13 - (int)arr11);
  return 0;
}

