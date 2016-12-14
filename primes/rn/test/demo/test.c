#include <rn.h>
#include <time.h>
#include <unistd.h>

#ifndef RN_DEMO_TEST_VS_MTEST
#define RN_DEMO_TEST_VS_MTEST 1
#endif

void draw(rni *a)
{
  int x;
  printf("%d,%d,",a->u,a->s);
  for (x=a->u-1; x>=0; --x) {
#if SIZEOF_rn_DIGIT == 4
    printf("%08lx ",a->dp[x]);
#else
    printf("%016llx ",a->dp[x]);
#endif
  }
  printf("\n");
}

int myrng(unsigned char *dst,int len,void *dat)
{
  int x;
  (void)dat;
  for (x=0; x<len; ++x)
    dst[x]=rand()&0xFF;
  return len;
}

char cmd[4096],buf[4096];

int main(void)
{
  rni a,b,c,d,e,f;
  unsigned long ix;
#if RN_DEMO_TEST_VS_MTEST
  unsigned long exp_n,add_n,sub_n,mul_n,div_n,sqr_n,mul2d_n,div2d_n,
    gcd_n,lcm_n,inv_n,div2_n,mul2_n,addd_n,subd_n,muld_n,cnt,rr;
#else
  rnd fp;
  int n,err;
#endif
  srand(time(NULL));
  printf("RN Ident string:\n%s\n\n",rn_ident());
  rn_zero(&b);
  rn_zero(&c);
  rn_zero(&d);
  rn_zero(&e);
  rn_zero(&f);
  rn_zero(&a);
#if RN_DEMO_TEST_VS_MTEST == 0
  draw(&a);
  /* test set and simple shifts */
  printf("Testing mul/div 2\n");
  rn_set(&a,1);
  draw(&a);
  for (n=0; n<=DGT_BIT; ++n) {
    rn_mul2(&a,&a);
    printf("(%d) ",rn_cntbit(&a));
    draw(&a);
  }
  for (n=0; n<=(DGT_BIT+1); ++n) {
    rn_div2(&a,&a);
    draw(&a);
  }
  rn_set(&a,1);

  /* test lshd/rshd */
  printf("testing lshd/rshd\n");
  rn_lshd(&a,3);
  draw(&a);
  rn_rshd(&a,3);
  draw(&a);

  /* test more complicated shifts */
  printf("Testing mul/div 2d\n");
  rn_mul2d(&a,DGT_BIT/2,&a);
  draw(&a);
  rn_div2d(&a,DGT_BIT/2,&a,NULL);
  draw(&a);

  rn_mul2d(&a,DGT_BIT+DGT_BIT/2,&a);
  draw(&a);
  rn_div2d(&a,DGT_BIT+DGT_BIT/2,&a,NULL);
  draw(&a);

  /* test neg/abs  */
  printf("testing neg/abs\n");
  rn_neg(&a,&a);
  draw(&a);
  rn_neg(&a,&a);
  draw(&a);
  rn_neg(&a,&a);
  draw(&a);
  rn_abs(&a,&a);
  draw(&a);

  /* test comparisons */
  rn_set(&b,3);
  rn_set(&c,4);
  rn_neg(&c,&c);
  rn_set(&d,1);
  printf("Testing compares\n%d,%d,%d,%d\n",rn_cmp(&a,&b),
         rn_cmp(&a,&c),rn_cmp(&a,&d),rn_cmp(&b,&c));

  /* test add/sub */
  printf("Testing add/sub \n");
  rn_set(&a,((rn_digit)1) << (DGT_BIT-1));
  draw(&a);
  rn_set(&b,((rn_digit)1) << (DGT_BIT-2));
  rn_add(&a,&b,&a);
  draw(&a);
  rn_add(&a,&b,&a);
  draw(&a);
  rn_add(&a,&b,&a);
  draw(&a);
  printf("sub...\n");
  printf("cmp returns: %d,",rn_cmp(&a,&b));
  rn_sub(&a,&b,&a);
  draw(&a);
  printf("cmp returns: %d,",rn_cmp(&a,&b));
  rn_sub(&a,&b,&a);
  draw(&a);
  printf("cmp returns: %d,",rn_cmp(&a,&b));
  rn_sub(&a,&b,&a);
  draw(&a);
  printf("cmp returns: %d,",rn_cmp(&a,&b));
  rn_sub(&a,&b,&a);
  draw(&a);
  printf("cmp returns: %d,",rn_cmp(&a,&b));
  rn_sub(&a,&b,&a);
  draw(&a);
  printf("cmp returns: %d,",rn_cmp(&a,&b));
  rn_sub(&a,&b,&a);
  draw(&a);
  rn_read_radix(
    &a,"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001",16);
  draw(&a);
  rn_subd(&a,3,&b);
  draw(&b);
  rn_read_radix(
    &a,"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFE",16);
  printf("cmp returns: %d,",rn_cmp(&a,&b));
  rn_sub(&a,&b,&a);
  draw(&a);

  /* test muld */
  printf("Testing muld and divd\n");
  rn_set(&a,1);
  rn_muld(&a,((rn_digit)1) << (DGT_BIT/2),&a);
  draw(&a);
  rn_muld(&a,((rn_digit)1) << (DGT_BIT/2),&a);
  draw(&a);
  rn_muld(&a,((rn_digit)1) << (DGT_BIT/2),&a);
  draw(&a);
  printf("divd\n");
  rn_divd(&a,((rn_digit)1) << (DGT_BIT/2),&a,NULL);
  draw(&a);
  rn_divd(&a,((rn_digit)1) << (DGT_BIT/2),&a,NULL);
  draw(&a);
  rn_divd(&a,((rn_digit)1) << (DGT_BIT/2),&a,NULL);
  draw(&a);
  /* testing read radix */
  printf("Testing read_radix\n");
  rn_read_radix(&a,"123456789012345678901234567890",16);
  draw(&a);
  /* test mont */
  printf("mont test #1\n");
  rn_set(&a,0x1234567ULL);
  rn_mont_setup(&a,&fp);
  rn_mont_calc_norm(&b,&a);

  rn_read_radix(&d,"123456789123",16);
  for (n=0; n<1000000; ++n) {
    rn_addd(&d,1,&d);
    rn_sqrmod(&d,&a,&d);
    rn_mul(&d,&b,&c);
    rn_mont_reduce(&c,&a,fp);
    if (rn_cmp(&c,&d) != RN_EQ) {
      printf("Failed mont %d\n",n);
      draw(&a);
      draw(&d);
      draw(&c);
      return EXIT_FAILURE;
    }
  }
  printf("Passed.\n");

  printf("mont test #2\n");
  rn_set(&a,0x1234567ULL);
  rn_lshd(&a,4);
  rn_addd(&a,1,&a);
  rn_mont_setup(&a,&fp);
  rn_mont_calc_norm(&b,&a);

  rn_read_radix(&d,"123456789123",16);
  for (n=0; n<1000000; ++n) {
    rn_addd(&d,1,&d);
    rn_sqrmod(&d,&a,&d);
    rn_mul(&d,&b,&c);
    rn_mont_reduce(&c,&a,fp);
    if (rn_cmp(&c,&d) != RN_EQ) {
      printf("Failed mont %d\n",n);
      draw(&a);
      draw(&d);
      draw(&c);
      return EXIT_FAILURE;
    }
  }
  printf("Passed.\n");
  /* test for size */
  for (ix=8*DGT_BIT; ix<10*DGT_BIT; ++ix) {
    printf("Testing (not safe-prime): %9lu bits    \r",ix);
    fflush(stdout);
    err=rn_prime_rand(&a,8,ix,(rand()&1) ? PR_2MSB_OFF : PR_2MSB_ON,
        myrng,NULL);
    if (err != rn_OKAY) {
      printf("failed with err code %d\n",err);
      return EXIT_FAILURE;
    }
    if ((unsed long)rn_cntbit(&a) != ix) {
      printf("Prime is %d not %lu bits!!!\n",rn_cntbit(&a),ix);
      return EXIT_FAILURE;
    }
  }
  printf("\n\n");
  return 0;

#else
  zero(&b);
  zero(&c);
  zero(&d);
  zero(&e);
  zero(&f);
  zero(&a);
  div2_n=mul2_n=inv_n=exp_n=lcm_n=gcd_n=add_n=sub_n=mul_n=
    div_n=sqr_n=mul2d_n=div2d_n=cnt=addd_n=subd_n=muld_n=0;
  for (;;) {
    printf("%4lu/%4lu/%4lu/%4lu/%4lu/%4lu/%4lu/%4lu/%4lu/%4lu/%4lu/%4lu/"
           "%4lu/%4lu/%4lu/%4lu ",
           add_n,sub_n,mul_n,div_n,sqr_n,mul2d_n,div2d_n,gcd_n,
           lcm_n,exp_n,inv_n,div2_n,mul2_n,addd_n,subd_n,muld_n);
    fgets(cmd,4095,stdin);
    cmd[strlen(cmd)-1]=0;
    printf("%s  ]\r",cmd);
    fflush(stdout);
    if (!strcmp(cmd,"mul2d")) {
      ++mul2d_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      sscanf(buf,"%lu",&rr);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      rn_mul2d(&a,rr,&a);
      a.s=b.s;
      if (rn_cmp(&a,&b) != RN_EQ) {
        printf("\nmul2d failed,rr == %lu\n",rr);
        draw(&a);
        draw(&b);
        return 0;
      }
    } else if (!strcmp(cmd,"div2d")) {
      ++div2d_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      sscanf(buf,"%lu",&rr);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      rn_div2d(&a,rr,&a,&e);
      a.s=b.s;
      if (a.u==b.u && a.u==0)
        a.s=b.s=rn_ZPOS;
      if (rn_cmp(&a,&b) != RN_EQ) {
        printf("\ndiv2d failed,rr == %lu\n",rr);
        draw(&a);
        draw(&b);
        return 0;
      }
    } else if (!strcmp(cmd,"add")) {
      ++add_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&c,buf,64);
      rn_cpy(&a,&d);
      rn_add(&d,&b,&d);
      if (rn_cmp(&c,&d) != RN_EQ) {
        printf("\nadd %lu failure!\n",add_n);
        draw(&a);
        draw(&b);
        draw(&c);
        draw(&d);
        return 0;
      }
      /* test the s/unsed storage functions */
      rr=rn_sed_bin_size(&c);
      rn_to_sed_bin(&c,(unsed char *)cmd);
      memset(cmd+rr,rand()&255,sizeof(cmd)-rr);
      rn_read_sed_bin(&d,(unsed char *)cmd,rr);
      if (rn_cmp(&c,&d) != RN_EQ) {
        printf("f\np_sed_bin failure!\n");
        draw(&c);
        draw(&d);
        return 0;
      }
      rr=rn_unsed_bin_size(&c);
      rn_to_unsed_bin(&c,(unsed char *)cmd);
      memset(cmd+rr,rand()&255,sizeof(cmd)-rr);
      rn_read_unsed_bin(&d,(unsed char *)cmd,rr);
      if (rn_cmp_mag(&c,&d) != RN_EQ) {
        printf("\nrn_unsed_bin failure!\n");
        draw(&c);
        draw(&d);
        return 0;
      }

    } else if (!strcmp(cmd,"sub")) {
      ++sub_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&c,buf,64);
      rn_cpy(&a,&d);
      rn_sub(&d,&b,&d);
      if (rn_cmp(&c,&d) != RN_EQ) {
        printf("\nsub %lu failure!\n",sub_n);
        draw(&a);
        draw(&b);
        draw(&c);
        draw(&d);
        return 0;
      }
    } else if (!strcmp(cmd,"mul")) {
      ++mul_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&c,buf,64);
      // continue;
      rn_cpy(&a,&d);
      rn_mul(&d,&b,&d);
      if (rn_cmp(&c,&d) != RN_EQ) {
        printf("\nmul %lu failure!\n",mul_n);
        draw(&a);
        draw(&b);
        draw(&c);
        draw(&d);
        return 0;
      }
    } else if (!strcmp(cmd,"div")) {
      ++div_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&c,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&d,buf,64);
      // continue;
      rn_div(&a,&b,&e,&f);
      if (rn_cmp(&c,&e)!=RN_EQ || rn_cmp(&d,&f)!=RN_EQ) {
        printf("\ndiv %lu failure!\n",div_n);
        draw(&a);
        draw(&b);
        draw(&c);
        draw(&d);
        draw(&e);
        draw(&f);
        return 0;
      }
    } else if (!strcmp(cmd,"sqr")) {
      ++sqr_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      // continue;
      rn_cpy(&a,&c);
      rn_sqr(&c,&c);
      if (rn_cmp(&b,&c) != RN_EQ) {
        printf("\nsqr %lu failure!\n",sqr_n);
        draw(&a);
        draw(&b);
        draw(&c);
        return 0;
      }
    } else if (!strcmp(cmd,"gcd")) {
      ++gcd_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&c,buf,64);
      // continue;
      rn_cpy(&a,&d);
      rn_gcd(&d,&b,&d);
      d.s=c.s;
      if (rn_cmp(&c,&d) != RN_EQ) {
        printf("\ngcd %lu failure!\n",gcd_n);
        draw(&a);
        draw(&b);
        draw(&c);
        draw(&d);
        return 0;
      }
    } else if (!strcmp(cmd,"lcm")) {
      ++lcm_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&c,buf,64);
      // continue;
      rn_cpy(&a,&d);
      rn_lcm(&d,&b,&d);
      d.s=c.s;
      if (rn_cmp(&c,&d) != RN_EQ) {
        printf("\nlcm %lu failure!\n",lcm_n);
        draw(&a);
        draw(&b);
        draw(&c);
        draw(&d);
        return 0;
      }
    } else if (!strcmp(cmd,"exp")) {
      ++exp_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&c,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&d,buf,64);
      // continue;
      rn_cpy(&a,&e);
      rn_expmod(&e,&b,&c,&e);
      if (rn_cmp(&d,&e) != RN_EQ) {
        printf("\nexp %lu failure!\n",exp_n);
        draw(&a);
        draw(&b);
        draw(&c);
        draw(&d);
        draw(&e);
        return 0;
      }
    } else if (!strcmp(cmd,"invmod")) {
      ++inv_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&c,buf,64);
      // continue;
      rn_invmod(&a,&b,&d);
#if 1
      rn_mulmod(&d,&a,&b,&e);
      if (rn_cmpd(&e,1) != RN_EQ) {
#else
      if (rn_cmp(&d,&c) != RN_EQ) {
#endif
        printf("\ninv [wrong value from MPI?!] failure\n");
        draw(&a);
        draw(&b);
        draw(&c);
        draw(&d);
        return 0;
      }
    } else if (!strcmp(cmd,"div2")) {
      ++div2_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      rn_div_2(&a,&c);
      if (rn_cmp(&c,&b) != RN_EQ) {
        printf("\ndiv_2 %lu failure\n",div2_n);
        draw(&a);
        draw(&b);
        draw(&c);
        return 0;
      }
    } else if (!strcmp(cmd,"mul2")) {
      ++mul2_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      rn_mul_2(&a,&c);
      if (rn_cmp(&c,&b) != RN_EQ) {
        printf("\nmul_2 %lu failure\n",mul2_n);
        draw(&a);
        draw(&b);
        draw(&c);
        return 0;
      }
    } else if (!strcmp(cmd,"addd")) {
      ++addd_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      sscanf(buf,"%lu",&ix);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      rn_addd(&a,ix,&c);
      if (rn_cmp(&b,&c) != RN_EQ) {
        printf("\naddd %lu failure\n",addd_n);
        draw(&a);
        draw(&b);
        draw(&c);
        printf("d == %lu\n",ix);
        return 0;
      }
    } else if (!strcmp(cmd,"subd")) {
      ++subd_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      sscanf(buf,"%lu",&ix);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      rn_subd(&a,ix,&c);
      if (rn_cmp(&b,&c) != RN_EQ) {
        printf("\nsubd %lu failure\n",subd_n);
        draw(&a);
        draw(&b);
        draw(&c);
        printf("d == %lu\n",ix);
        return 0;
      }
    } else if (!strcmp(cmd,"muld")) {
      ++muld_n;
      fgets(buf,4095,stdin);
      rn_read_radix(&a,buf,64);
      fgets(buf,4095,stdin);
      sscanf(buf,"%lu",&ix);
      fgets(buf,4095,stdin);
      rn_read_radix(&b,buf,64);
      rn_muld(&a,ix,&c);
      if (rn_cmp(&b,&c) != RN_EQ) {
        printf("\nmuld %lu failure\n",muld_n);
        draw(&a);
        draw(&b);
        draw(&c);
        printf("d == %lu\n",ix);
        return 0;
      }
    }
  }
#endif
}

