/*  RECUR1.C: First example of recursion  */

main()
{
  p(4);
  puts("");
}

p(n) int n;
{
  if (n>0){
    p(n-2);
    printf("%3d", n);
    p(n-1);
  }
}

