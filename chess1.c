#define F(I,S,N) for(I=S;I&lt;N;I++)
#define W(A) while(A)

int V=112,M=136,I=8e3,C=799,X,Y,Q,N,
d[]={-16,-15,-17,0,1,16,0,1,16,15,17,0,14,18,31,33,0,
     1,1,3,-1,3,5,9,
     7,-1,11,6,8,3,6},
b[128]={6,3,5,7,4,5,3,6};

char n[]=".?+pkltd?*?PKLTD";

D(k,q,l,e,x,n)
int k,q,l,e,x,n;
{
 int i=0,j,t,p,u,r,y,m=n>1|q>e?q:e,v,h,z;

 N++;
 do{
  u=b[i];
  if(u&amp;k)
  {r=p=u&amp;7;
   j=d[p+23];
   W(r=p>2&amp;r&lt;0?-r:-d[++j])
   {y=i;
    do
    {y+=r;if(y&amp;M)break;
     t=b[y];if(t&amp;k|p&lt;3&amp;!(r&amp;7)-!t)break;
     v=99*d[t&amp;7|16];
     if(v&lt;0)m=I;
     if(m>=l)return m;
    
     if(h=n-(y!=x))
     {if(p&lt;6)v+=b[i+8]-b[y+8];
      if(p==4)v+=9*(e>C?!((x^y)&amp;68):-3);

      b[i]=0;b[y]=u;
      if(p&lt;3)
      {v-=9*(((i-2)&amp;M||b[i-2]!=u)+((i+2)&amp;M||b[i+2]!=u)-1);
       if(y+r+1&amp;128){b[y]|=7;v+=C;}
      }
      v=-D(24-k,-l,-m,z=-e-v,y,h);
      v-=v>I/3;
      if(x==9){if(v+I&amp;&amp;i==X&amp;y==Y){Q=z;return l;}v=m;}
      b[i]=u;b[y]=t;
 
      if(v>m){m=v;if(x&amp;8){X=i;Y=y;}}
     }
     t+=p&lt;5;if(p&lt;3&amp;&amp;6*k+(y&amp;V)==128)t--;
    }W(!t);
   }
  }
 }W(i=i+9&amp;~M);
 return m+I?m:-D(24-k,-I,I,0,x,1)/2;
}

main()
{
 int k=8,*p,c[9],d;

 F(X,0,8)
 {b[X+V]=(b[X]+=16)-8;b[X+16]=18;b[X+96]=9;
  F(Y,0,8)b[16*Y+X+8]=(X-4)*(X-4)+(Y-3.5)*(Y-3.5);
 }

 W(1)
 {F(N,0,121)printf(" %c",N&amp;8&amp;&amp;(N+=7)?10:n[b[N]&amp;15]);
  p=c;W((*p++=getchar())>10);
  if(*c-10){X=*c-16*c[1]+C;Y=c[2]-16*c[3]+C;}else
  {d=6;N=0;W(N&lt;1e6)D(k,-I,I,Q,8,d++);}
  if(D(k,-I,I,Q,9,2)==I)k^=24;
 }
}

