/* Copyright 2004-2016 The OpenSSL Project Authors. All Rights Reserved.
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

int main(int argc, char *argv[])
{
  BIGNUM *bn = NULL;
  int hex=0, checks=20, generate=0, bits=0, safe=0, ret=1;

  if (argc == 1 && !generate) {
    fprintf(stderr, "%s: No prime specified\n", argv[0]);
    goto end;
  }


  if (generate) {
    char *s;

    if (!bits) {
      fprintf(stderr, "Specify the number of bits.\n");
      goto end;
    }
    bn = BN_new();
    if (bn == NULL) {
      fprintf(stderr, "Out of memory.\n");
      goto end;
    }
    if (!BN_generate_prime_ex(bn, bits, safe, NULL, NULL, NULL)) {
      fprintf(stderr, "Failed to generate prime.\n");
      goto end;
    }
    s = hex ? BN_bn2hex(bn) : BN_bn2dec(bn);
    if (s == NULL) {
      fprintf(stderr, "Out of memory.\n");
      goto end;
    }
    fprintf(stdout, "%s\n", s);
    free(s);
  } else {
    for (; *argv; ++argv) {
      int r;

      if (hex)
        r = BN_hex2bn(&bn, argv[1]);
      else
        r = BN_dec2bn(&bn, argv[1]);

      if (!r) {
        fprintf(stderr, "Failed to process value (%s)\n", argv[1]);
        goto end;
      }

      BN_print(stdout, bn);
      fprintf(stdout, " (%s) %s prime\n", argv[1],
                 BN_is_prime_ex(bn, checks, NULL, NULL) ? "is" : "is not");
    }
  }
  ret = 0;
end:
  BN_free(bn);
  return ret;
}

