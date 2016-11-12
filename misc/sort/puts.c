int puts(const char*s)
{
  int err;
  while(*s&&(EOF!=(err=putchar(*s++))))
    continue;
  if(err)
    err=putchar('\n');
  return(err);
}



