#include <stdio.h>

int
main(void)
{
  double n1, n2, n3;

  printf(":\t");
  scanf("%lf %lf %lf", &n1, &n2, &n3);

  if (n1 >= n2) {
    if (n1 >= n3)
      printf("\n%.2lf ismax\n", n1);
    else
      printf("\n%.2lf ismax\n", n3);
  } else {
    if (n2 >= n3)
      printf("\n%.2lf ismax\n", n2);
    else
      printf("\n%.2lf ismax\n", n3);
  }
  return 0;
}

