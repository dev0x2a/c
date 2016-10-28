#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#define x(s,d,...)if(s){o=errno;fputs(*v,stderr);fprintf(stderr,": "__VA_ARGS__\
);errno=o;perror(0);d;}
#define l while
#define s(r,s,d,...)l((r=s)<0&&errno==EINTR);x(r<0,d,__VA_ARGS__)
#define z " %s ",(c>1?v[i]:"stdin")
#define w(c)s(w,write(1,c,1),,"write: ")
int main(int c,char**v){int o,r,f,i=1,w,n;f=n=0;char*b,*e,*p,*q;b=e=p=0;do{if(c>
1){s(f,open(v[i],O_RDONLY),n=1;continue,"cannot open %s: ",v[i])}do{do{if(p==e){
q=p=b;b=realloc(b,(e-p)*2+1);x(!b,{free(q);close(f);return 1;},"realloc: ")p=e-p
+b;e=b+(p-b)*2+1;}s(r,read(f,p,1),n=1,"read"z)}l(r>0&&*p++-10);if(r+1&&p-b){l(p-
b)if(*--p-10){w(p)}w("\n")}}l(r>0);close(f);}l(++i<c);free(b);return n;}

