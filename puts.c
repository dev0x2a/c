int puts(char*s){
  int err;
  while(*s&&(EOF!=(err=putchar(*s++))))continue;
  if(err 0)err=putchar('\n');
  return(err);
}

