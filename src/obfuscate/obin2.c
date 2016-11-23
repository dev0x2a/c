#define i main(int w,char**z)
#define n putchar
i{int k,l=atoi(z[1]);for(k=31;k>=0;--k){((l>>k)&1)?n('1'):n('0');}n('\n');}
