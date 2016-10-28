/*  SUM.C:  Compute the sum of a seq of ints  */

main()
{
  int i,s;
  s=0;
  while (scanf("%d", &i)>0) s+=i;
  printf("\nsum = %d\n", s);
}

