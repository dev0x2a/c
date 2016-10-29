/* EUCLID.C: Euclid's algorithm */
int gcd(x,y)int x,y;
{ int r;
  if(x<0)x=-x;
  if(y<0)y=-y;
  while(y){r=x%y;x=y;y=r;}
  return(x);
}
main(){
  printf("%d\n",gcd(200,300));
}

