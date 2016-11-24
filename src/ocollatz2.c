n;main(a,b)char**b;{n=atoi(1[b]);if(n<2)return;do{write(1,"'",1);(n&1)?(n=(n<<1)+n+1):(n>>=1);}while(n!=1);puts("");};
