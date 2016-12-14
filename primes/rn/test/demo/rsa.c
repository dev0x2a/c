#include "rn.h"
#include <time.h>

int main(void)
{
  rni d, e, n, c, m, e_m;
  clock_t t1;
  int x;

  /* read in the parameters */
  rn_read_radix(
    &n,
    "ce032e860a9809a5ec31e4b0fd4b546f8c40043e3d2ec3d8f49d8f2f3dd19e887094ee"
    "1af75caa1c2e6cd9ec78bf1dfd6280002ac8c30ecd72da2e4c59a28a9248048aaae2a8"
    "fa627f71bece979cebf9f8eee2bd594d4a4f2e791647573c7ec1fcbd320d3825be3fa8"
    "a17c97086fdae56f7086ce512b81cc2fe44161270ec5e9",
    16);
  rn_read_radix(&e, "10001", 16);
  rn_read_radix(
    &m,
    "39f5a911250f45b99390e2df322b33c729099ab52b5879d06b00818cce57c649a66ed7"
    "eb6d8ae214d11caf9c81e83a7368cf0edb2b71dad791f13fecf546123b40377851e678"
    "35ade1d6be57f4de18a62db4cdb1880f4ab2e6a29acfd85ca22a13dc1f6fee2621ef0f"
    "c8689cd738e6f065c033ec7c148d8d348688af83d6f6bd",
    16);
  rn_read_radix(
    &c,
    "9ff70ea6968a04530e6b06bf01aa937209cc8450e76ac19477743de996ba3fb445923c"
    "947f8d0add8c57efa51d15485309918459da6c1e5a97f215193b797dce98db51bdb463"
    "9c2ecfa90ebb051e3a2daeffd27a7d6e62043703a7b15e0ada5170427b63099cd01ef5"
    "2cd92d8723e5774bea32716aaa7f5adbae817fb12a5b50",
    16);

  /* test it */
  rn_expmod(&m, &e, &n, &e_m);
  if (rn_cmp(&e_m, &c)) {
    char buf[1024];
    printf("Encrypted text not equal\n");
    rn_toradix(&e_m, buf, 16);
    printf("e_m == %s\n", buf);
    return 0;
  }

  printf("CLOCKS_PER_SEC = %llu\n", (unsigned long long)CLOCKS_PER_SEC);
  t1 = clock();
  for (x = 0; x < 1000; ++x) {
    rn_expmod(&m, &e, &n, &e_m);
  }
  t1 = clock() - t1;
  printf("1000 RSA operations took     %10.5g seconds\n",
         (double)t1 / (double)CLOCKS_PER_SEC);
  printf("RSA encrypt/sec              %10.5g\n",
         (double)CLOCKS_PER_SEC / ((double)t1 / 1000.0));

  /* read in the parameters */
  rn_read_radix(
    &n,
    "a7f30e2e04d31acc6936916af1e404a4007adfb9e97864de28d1c7ba3034633bee2cd9"
    "d5da3ea3cdcdc9a6f3daf5702ef750f4c3aadb0e27410ac04532176795995148cdb469"
    "1bd09a8a846e3e24e073ce2f89b34dfeb2ee89b646923ca60ee3f73c4d539747838042"
    "5e7260f75dfdc54826e160395b0889b1162cf115a9773f",
    16);
  rn_read_radix(
    &d,
    "16d166f3c9a404d810d3611e6e8ed43293fe1db75c8906eb4810785a4b82529929dade"
    "1db7f11ac0335d5a59773e3167b022479eedefa514a0399db5c900750a56323cf9f5b0"
    "f21e7d60a46d75f3fcaabf30a63cbe34048b741a57ac36a13914afda798709dea5771f"
    "8d456cf72ec5f3afc1d88d023de40311143a36e7028739",
    16);
  rn_read_radix(
    &c,
    "7d216641c32543f5b8428bdd0b11d819cfbdb16f1df285247f677aa4d44de62ab064f4"
    "a0d060ec99cb94aa398113a4317f2c550d0371140b0fd2c88886cac771812e72faad4b"
    "7adf495b9b850b142ccd7f45c0a27f164c8c7731731c0015f69d0241812e769d961054"
    "618aeb9e8e8989dba95714a2cf56c9e525c5e34b5812dd",
    16);
  rn_read_radix(
    &m,
    "5f323bf0b394b98ffd78727dc9883bb4f42287def6b60fa2a964b2510bc55d61357bf5"
    "a6883d2982b268810f8fef116d3ae68ebb41fd10d65a0af4bec0530eb369f37c14b55c"
    "3be60223b582372fb6589b648d5a0c7252d1ae2dae5809785d993e9e5d0c4d9b0bcba0"
    "cde0d6671734747fba5483c735e1dab7df7b10ec6f62d8",
    16);

  /* test it */
  rn_expmod(&c, &d, &n, &e_m);
  if (rn_cmp(&e_m, &m)) {
    char buf[1024];
    printf("Decrypted text not equal\n");
    rn_toradix(&e_m, buf, 16);
    printf("e_m == %s\n", buf);
    return 0;
  }
  t1 = clock();
  for (x = 0; x < 100; ++x) {
    rn_expmod(&c, &d, &n, &e_m);
  }
  t1 = clock() - t1;
  printf("100 RSA operations took      %10.5g seconds\n",
         (double)t1 / (double)CLOCKS_PER_SEC);
  printf("RSA decrypt/sec              %10.5g\n",
         (double)CLOCKS_PER_SEC / ((double)t1 / 100.0));

  /* test half size */
  rn_rshd(&n, n.u >> 1);
  rn_rshd(&d, d.u >> 1);
  rn_rshd(&c, c.u >> 1);
  printf("n.u == %4d bits\n", n.u * DGT_BIT);

  /* ensure n is odd */
  n.dp[0] |= 1;
  t1 = clock();
  for (x = 0; x < 100; ++x) {
    rn_expmod(&c, &d, &n, &e_m);
  }
  t1 = clock() - t1;
  printf("100 RSA-half operations took %10.5g seconds\n",
         (double)t1 / (double)CLOCKS_PER_SEC);
  printf(
    "RSA decrypt/sec              %10.5g (estimate of RSA-1024-CRT) \n",
    (double)CLOCKS_PER_SEC / ((double)t1 / 50.0));
  return 0;
}
