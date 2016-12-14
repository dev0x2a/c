#if defined(RN_PRESCOTT) && defined(RN_SSE2)
#undef RN_SSE2
#define RN_X86
#endif

#define COMBA_START
#define CLR_CARRY c0=c1=c2=0;
#define COMBA_STO(x) x=c0;
#define COMBA_STO2(x) x=c1;
#define CARRY_FOW do { c0=c1; c1=c2; c2=0; } while (0);
#define COMBA_FIN

#if defined(RN_X86) /* x86-32 optimized */
#define SQRADD(i,j) \
  asm("movl  %6,%%eax     \n\t" \
      "mull  %%eax        \n\t" \
      "addl  %%eax,%0     \n\t" \
      "adcl  %%edx,%1     \n\t" \
      "adcl  $0,%2        \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"m"(i) \
      : "%eax","%edx","cc");

#define SQRADD2(i,j) \
  asm("movl  %6,%%eax     \n\t" \
      "mull  %7           \n\t" \
      "addl  %%eax,%0     \n\t" \
      "adcl  %%edx,%1     \n\t" \
      "adcl  $0,%2        \n\t" \
      "addl  %%eax,%0     \n\t" \
      "adcl  %%edx,%1     \n\t" \
      "adcl  $0,%2        \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"m"(i),"m"(j) \
      : "%eax","%edx","cc");

#define SQRADDSC(i,j) \
  asm("movl  %3,%%eax     \n\t" \
      "mull  %4           \n\t" \
      "movl  %%eax,%0     \n\t" \
      "movl  %%edx,%1     \n\t" \
      "xorl  %2,%2        \n\t" \
      : "=r"(sc0),"=r"(sc1),"=r"(sc2) \
      : "g"(i),"g"(j) \
      : "%eax","%edx","cc");

#define SQRADDAC(i,j) \
  asm("movl  %6,%%eax     \n\t" \
      "mull  %7           \n\t" \
      "addl  %%eax,%0     \n\t" \
      "adcl  %%edx,%1     \n\t" \
      "adcl  $0,%2        \n\t" \
      : "=r"(sc0),"=r"(sc1),"=r"(sc2) \
      : "0"(sc0),"1"(sc1),"2"(sc2),"g"(i),"g"(j) \
      : "%eax","%edx","cc");

#define SQRADDDB \
  asm("addl %6,%0         \n\t" \
      "adcl %7,%1         \n\t" \
      "adcl %8,%2         \n\t" \
      "addl %6,%0         \n\t" \
      "adcl %7,%1         \n\t" \
      "adcl %8,%2         \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"r"(sc0),"r"(sc1),"r"(sc2) \
      : "cc");

#elif defined(RN_X86_64) /* x86-64 optimized */
#define SQRADD(i,j) \
  asm("movq  %6,%%rax     \n\t" \
      "mulq  %%rax        \n\t" \
      "addq  %%rax,%0     \n\t" \
      "adcq  %%rdx,%1     \n\t" \
      "adcq  $0,%2        \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"x"(i) \
      : "%rax","%rdx","cc");

#define SQRADD2(i,j) \
  asm("movq  %6,%%rax     \n\t" \
      "mulq  %7           \n\t" \
      "addq  %%rax,%0     \n\t" \
      "adcq  %%rdx,%1     \n\t" \
      "adcq  $0,%2        \n\t" \
      "addq  %%rax,%0     \n\t" \
      "adcq  %%rdx,%1     \n\t" \
      "adcq  $0,%2        \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"g"(i),"g"(j) \
      : "%rax","%rdx","cc");

#define SQRADDSC(i,j) \
  asm("movq  %3,%%rax     \n\t" \
      "mulq  %4           \n\t" \
      "movq  %%rax,%0     \n\t" \
      "movq  %%rdx,%1     \n\t" \
      "xorq  %2,%2        \n\t" \
      : "=r"(sc0),"=r"(sc1),"=r"(sc2) \
      : "g"(i),"g"(j) \
      : "%rax","%rdx","cc");

#define SQRADDAC(i,j) \
  asm("movq  %6,%%rax     \n\t" \
      "mulq  %7           \n\t" \
      "addq  %%rax,%0     \n\t" \
      "adcq  %%rdx,%1     \n\t" \
      "adcq  $0,%2        \n\t" \
      : "=r"(sc0),"=r"(sc1),"=r"(sc2) \
      : "0"(sc0),"1"(sc1),"2"(sc2),"g"(i),"g"(j) \
      : "%rax","%rdx","cc");

#define SQRADDDB \
  asm("addq %6,%0         \n\t" \
      "adcq %7,%1         \n\t" \
      "adcq %8,%2         \n\t" \
      "addq %6,%0         \n\t" \
      "adcq %7,%1         \n\t" \
      "adcq %8,%2         \n\t" \
      : "=r"(c0),"=r"(c1),"=r"(c2) \
      : "0"(c0),"1"(c1),"2"(c2),"r"(sc0),"r"(sc1),"r"(sc2) \
      : "cc");
#else

#define RN_ISO /* ISO C portable code */
/* multiplies point i and j, updates carry "c1" and digit c2 */
#define SQRADD(i,j) \
  do { rnw t = c0+((rnw)i)*((rnw)j); \
    c0 = t; t = c1+(t>>DGT_BIT); \
    c1 = t; c2 += t>>DGT_BIT; } while (0);

/* for squaring some of the terms are doubled... */
#define SQRADD2(i,j) \
  do { rnw t = ((rnw)i)*((rnw)j); tt = (rnw)c0+t; c0 = tt; \
    tt = (rnw)c1+(tt>>DGT_BIT); c1 = tt; c2 += tt>>DGT_BIT; \
    tt = (rnw)c0+t; c0 = tt; tt = (rnw)c1+(tt>>DGT_BIT); \
    c1 = tt; c2 += tt>>DGT_BIT; } while (0);

#define SQRADDSC(i,j) \
  do { rnw t = ((rnw)i)*((rnw)j); sc0 = (rnd)t; \
    sc1 = (t>>DGT_BIT); sc2 = 0; } while (0);

#define SQRADDAC(i,j) \
  do { rnw t = sc0+((rnw)i)*((rnw)j); sc0 = t; t = sc1+(t>>DGT_BIT); \
    sc1 = t;  sc2 += t>>DGT_BIT; } while (0);

#define SQRADDDB \
  do { rnw t = ((rnw)sc0)+((rnw)sc0)+c0; c0 = t; \
    t = ((rnw)sc1)+((rnw)sc1)+c1+(t>>DGT_BIT); c1 = t; \
    c2 = c2+((rnw)sc2)+((rnw)sc2)+(t>>DGT_BIT); } while (0);
#endif

