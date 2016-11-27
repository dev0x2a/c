//main(c){write(read(0,&c,1)&&main());}
main(){unsigned char b[4],s=read(0,b,1)+read(0,b+1,*b&128?*b&32?*b&16?3:2:1:0);
*b?main(),write(1,b,s):1;}
