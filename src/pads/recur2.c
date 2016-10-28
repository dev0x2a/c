/*  RECUR2.C: Second example of recursion  */

main()
{
  p(80);
  puts("");
}

p(n) int n;
{
  if (n>0){
    p(n-40);
    printf("%3d", n);
    p(n-20);
  }
}

