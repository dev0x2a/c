#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
#include<time.h>

#define USE_BITS

#ifdef USE_BITS
#define alloc_prime char *prime=calloc(i/8,sizeof(*prime));
#define set_not_prime(x) prime[x/8]|=(1<<(x%8))
#define is_prime(x) (!(prime[x/8]&(1<<(x%8))))
#endif

#ifdef USE_CHAR
#define alloc_prime char *prime=calloc(i,sizeof(*prime));
#define set_not_prime(x) prime[x]=1
#define is_prime(x) (prime[x]==0)
#endif

#ifdef USE_SIZE_TYPE
#define alloc_prime size_t *prime=calloc(i,sizeof(*prime));
#define set_not_prime(x) prime[x]=1
#define is_prime(x) (prime[x]==0)
#endif

void
main(int argc, char *argv[])
{
  if(argc!=2){
  printf("%s <lim>\n", argv[0]);
  exit(1);
  }
  int i;
  clock_t start,end;
  double cpu;

  i=atoi(argv[1]);
  cpu=0.0;
  assert((start=clock())!=-1);

  alloc_prime;
  int c1,c2,c3;
  if(!prime){
    printf("%s: cannot allocate %zu bytes\n", argv[0],i*sizeof(*prime));
    exit(1);
  }
  set_not_prime(0);
  set_not_prime(1);

  for(c2=2; c2<=(int)sqrt(i)+1; c2++){
    if(is_prime(c2)){
      c1=c2;
      for(c3=2*c1; c3<=i+1; c3+=c1){
        set_not_prime(c3);
      }
    }
  }
  end=clock();
  cpu=((double)(end-start))/CLOCKS_PER_SEC;
  for(c1=0; c1<=i+1; c1++){
    if(is_prime(c1)) printf("%i\n", c1);
    //if(prime[c1]==0)
  }
  printf("\ncpu usage: %f\n", cpu);
  exit(0);
}

