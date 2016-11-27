#include<stdio.h>
int main()
{
  int i,c;
  int *x,*y;
  FILE *gnuplot = popen("gnuplot","w");
  fprintf(gnuplot, "plot '-'\n");
  for(i=0,c=10;i<c;++i){
    fprintf(gnuplot,"%g %g\n",x[i],y[i]);
  }
  fprintf(gnuplot,"e\n");
  fflush(gnuplot);
  return(0);
}

