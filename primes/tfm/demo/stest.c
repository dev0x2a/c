/* A simple static test program. */
#include <tfm.h>

#ifdef GBA_MODE
#include <gba.h>
#define DISPLAY(x) modetxt_puts(vfb, x, 1)
#endif

#ifndef DISPLAY
#define DISPLAY(x) printf(x)
#define DISPLAY_P(...) printf(__VA_ARGS__)
#else
#define DISPLAY_P(...) (void)0
#define fp_dump(n, p)                                                          \
  do {                                                                         \
  } while (0)
#endif

#ifndef fp_dump
void fp_dump(const char *n, fp_int *p) {
  int sz;
  if (fp_radix_size(p, 2, &sz) != FP_OKAY)
    return;
  char *str = malloc(sz);
  if (!str)
    return;
#ifdef STEST_VERBOSE
  fp_toradix(p, str, 2);
  DISPLAY_P("%s = 0b%s\n", n, str);
  fp_toradix(p, str, 16);
  DISPLAY_P("%s = 0x%s\n", n, str);
#endif
  fp_toradix(p, str, 10);
  DISPLAY_P("%s = %s\n", n, str);
  free(str);
}
#endif

#ifdef GBA_MODE
int c_main(void)
#else
int main(void)
#endif
{
  fp_int a, b, c, d, e, f;
  fp_digit dp;

  fp_init(&a);
  fp_init(&b);
  fp_init(&c);
  fp_init(&d);
  fp_init(&e);
  fp_init(&f);

#ifdef GBA_MODE
  install_common();
  modetxt_init();
  modetxt_gotoxy(0, 0);
#endif

  DISPLAY_P("TFM Ident string:\n%s\n\n", fp_ident());

  /* test multiplication */
  fp_read_radix(&a, "3453534534535345345341230891273", 10);
  fp_read_radix(&b, "2394873294871238934718923", 10);
  fp_read_radix(&c, "8270777629674273015508507050766235312931312159028658979",
                10);
  fp_mul(&a, &b, &d);
  if (fp_cmp(&c, &d)) {
    DISPLAY("mul failed\n");
    return -1;
  } else {
    DISPLAY("mul passed\n");
  }

  /* test multiplication */
  fp_read_radix(&a, "3048129032049823598734971230852365237864391256347823290778"
                    "2361237864278207235782364578264891274789264278634289739",
                10);
  fp_read_radix(&b, "4876147812638726378263827632783628763283627836283762783873"
                    "6278362923698724823749238732",
                10);
  fp_read_radix(&c, "1486312771227034563307950634490737985563993459700941115664"
                    "2572757953666237955901361205791001182335803571150740688155"
                    "0725771590629510553610792175417781097686367930028393218800"
                    "6885811950341132768970948",
                10);
  fp_mul(&a, &b, &d);
  if (fp_cmp(&c, &d)) {
    DISPLAY("mul failed\n");
    return -1;
  } else {
    DISPLAY("mul passed\n");
  }

  /* test multiplication */
  fp_read_radix(&a, "1157920892373161954235709850086879078532699846656405640394"
                    "57584007913129639935",
                10);
  fp_read_radix(&b, "174224571863520493293247799005065324265471", 10);
  fp_read_radix(&c, "2017382717255397335668686853127353026820071071438907137779"
                    "4102651988800859098544338487575161443744102709980552583184"
                    "385",
                10);
  fp_mul(&a, &b, &d);
  if (fp_cmp(&c, &d)) {
    DISPLAY("mul failed\n");
    return -1;
  } else {
    DISPLAY("mul passed\n");
  }

  /* test squaring */
  fp_read_radix(
      &a, "298723982748923478923473927489237289347238947238947238947238972893",
      10);
  fp_read_radix(&b, "8923601786937913223551278706836754652130968941226262443496"
                    "4313994127411682542855190667724226920696163962644836740110"
                    "835385588789449",
                10);
  fp_sqr(&a, &c);
  if (fp_cmp(&c, &b)) {
    DISPLAY("sqr failed\n");
    return -1;
  } else {
    DISPLAY("sqr passed\n");
  }

  fp_read_radix(&a, "3978238942389731289428951238943271239417249278489273492748"
                    "97238978927593487012378490184789429812734982738972389",
                10);
  fp_read_radix(&b, "1582638508274616774919614399992649010676362829383525319328"
                    "9929829327094599793008735347190316660150732129882708700833"
                    "6951419604640736464667188494668962822678461626245753696845"
                    "719301945679092882499787869509090904187704367321",
                10);
  fp_sqr(&a, &c);
  if (fp_cmp(&c, &b)) {
    DISPLAY("sqr failed\n");
    return -1;
  } else {
    DISPLAY("sqr passed\n");
  }

  fp_read_radix(&a, "1340780792994259709957402499820584612747936582059239337772"
                    "3561443721764030073546976801874298166903427690031858186486"
                    "050853753882811946569946433649006084095",
                10);
  fp_read_radix(&b, "1797693134862315907729305190789024733617976978942306572734"
                    "3008115773267580550096313270847732240753602112011387987139"
                    "3357658789768814416622492847430639474097562152033539671286"
                    "1282522231895538391607214417672982503217152632388144027343"
                    "7995950679223090335649513062086992526784553843071409241169"
                    "5463462326211969025",
                10);
  fp_sqr(&a, &c);
  if (fp_cmp(&c, &b)) {
    DISPLAY("sqr failed\n");
    return -1;
  } else {
    DISPLAY("sqr passed\n");
  }

  /* montgomery reductions */
  fp_read_radix(&a, "2348923748923748934891234289378927812378632786378263273676"
                    "37836278362783627836783678363",
                10);
  fp_read_radix(&b, "4447823492749823749234123489273987393983289319382762756425"
                    "425425642727352327452374521",
                10);
#ifdef FP_64BIT
  fp_read_radix(&c, "9429744965608635036572267414223015988072354879416741476609"
                    "89764036913926327577165648",
                10);
#else
  fp_read_radix(&c, "2396271882990732698083317035605836523697277786556053771759"
                    "862552557086442129695099100",
                10);
#endif
  if (fp_montgomery_setup(&b, &dp) != FP_OKAY)
    DISPLAY("mont setup failed\n");
  fp_montgomery_reduce(&a, &b, dp);
  if (fp_cmp(&a, &c)) {
    DISPLAY("mont failed\n");
    fp_dump("a (is    )", &a);
    fp_dump("c (should)", &c);
    return -1;
  } else {
    DISPLAY("mont passed\n");
  }

  fp_read_radix(&a, "2348923748923748934891234456645654645645684576353428937892"
                    "781237863278637826327367637836278362783627836783678363",
                10);
  fp_read_radix(&b, "4447823492749823749234123489273987393983289319382762756425"
                    "42542564272735232745237452123424324324444121111119",
                10);
  fp_read_radix(&c, "4564261384455458290865260308618026740382331239099008232851"
                    "5008314514368668691233331246183943400359349283420",
                10);
  if (fp_montgomery_setup(&b, &dp) != FP_OKAY)
    DISPLAY("mont setup failed\n");
  fp_montgomery_reduce(&a, &b, dp);
  if (fp_cmp(&a, &c)) {
    DISPLAY("mont failed\n");
    fp_dump("a (is    )", &a);
    fp_dump("c (should)", &c);
    return -1;
  } else {
    DISPLAY("mont passed\n");
  }

  fp_read_radix(&a, "2348234242423429237489237489348912344566456546456456845763"
                    "5342497237823476237862389123683413235237523537846237848937"
                    "8927812378632786378263273676378362783627555555555539568389"
                    "0524781246184618347638376857236458275290348534905801345689"
                    "47341278498542893481762349723907847892983627836783678363",
                10);
  fp_read_radix(&b, "4447823492745656345598237492341234892739873939832893193827"
                    "6275642485623481638279025465891276312903262837562349056234"
                    "783648712314678120389173890128905425242424239784256427",
                10);
  fp_read_radix(&c, "3316086526545336165056403146451904212618563233346275408448"
                    "9985719613480783282357410514898819797738034600484519472656"
                    "152351777186694609218202276509271061460265488348645081",
                10);
  if (fp_montgomery_setup(&b, &dp) != FP_OKAY)
    DISPLAY("mont setup failed\n");
  fp_montgomery_reduce(&a, &b, dp);
  if (fp_cmp(&a, &c)) {
    DISPLAY("mont failed\n");
    fp_dump("a (is    )", &a);
    fp_dump("c (should)", &c);
    return -1;
  } else {
    DISPLAY("mont passed\n");
  }

  return 0;
}

/* $Source$ */
/* $Revision$ */
/* $Date$ */
