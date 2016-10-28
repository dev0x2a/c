/*  SIDE2.C:  Second prog to demonstrate side effects  */
int i=5;
main()
{
  printf("%d\n", f()+g());
}

int f()
{
  return(++i);
}
int g()
{
  return(i*=10);
}

