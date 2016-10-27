S=1e4,i,j,s,c,g,a[2801]={[0 ... 2800]=2e3};main(){for(i=2800;i;i-=14){s=0;for(j=i;j;--j)s=s*j+S*a[j],g=j*2-1,a[j]=s%g,s/=g;printf("%04d",c+s/S);c=s%S;}}
