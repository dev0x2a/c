/*  TAIL.c: tail recursion  */
int s=0;
main()
{ addnumbers();
  printf("sum = %d\n",s);
}
#if 0
addnumbers()
{ int x;
  if(scanf("%d",&x)>0){s+=x;addnumbers();}
}
#endif
addnumbers()  /* nonrecursive version */
{ int x;
  while(scanf("%d",&x)>0)s+=x;
}
int depth,maxdepth;
depth=maxdepth=0;
int f(x)int x;
{ if(++depth>maxdepth)maxdepth=depth;
  /* contents of recurive function f */
  depth--;
}
double factorial(n)int n; /* recursive version */
{ return(n>1?n*factorial(n-1):1.0);
}
double factorial(n)int n; /* nonrecursive version */
{ double product=1.0;
  while(n>1)product*=n--;
  return(product);
}

