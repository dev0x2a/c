char b[256];
main(s,k,f){
  if(bind(s=socket(2,1,0),"\0\x02\x1f\x90\0\0\0\0",16))exit(1);
  for(listen(s,10);read(k=accept(s,0,0),b,256);close(k)){
    write(k,"HTTP/1.0 200 O\n\n",16);
    *(strchr(b+5,32))=0;
    f=open(strlen(b+5)?b+5:"index.html",0,0);
    if(f+1)while(read(f,b,1)||close(f))write(k,b,1);
  }
}

