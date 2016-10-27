/*  SIDE1.C:  First prog to demonstrate side effects  */
int n;
main()
{ int i,x;
  printf("Enter n: ");
  scanf("%d", &n);
  printf("Enter %d integers to be squared\n", n);
  for (i=0; i<n; i++){
    scanf("%d", &x);
    printf("Its square is %d\n", square(x));
  }
}

int square(x) int x;
{ n=x*x;
  return(n);
}

