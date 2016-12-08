main(){int a[256],i;auto f=fopen("m","r");while(i=~getc(f))a[~i]++;for(int x:a)x?printf("%c %d\n",i,x):0,++i;}
