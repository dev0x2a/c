#ifndef RBN_PRIV_H
#define RBN_PRIV_H

#include "rbn.h"

void s_rn_add(rni *a, rni *b, rni *c);
void s_rn_sub(rni *a, rni *b, rni *c);
void rn_rev(unsigned char *s, int len);

void rn_mul_comba(rni *A, rni *B, rni *C);

#ifdef RN_SMALL_SET
void rn_mul_comba_small(rni *A, rni *B, rni *C);
#endif

#ifdef RN_MUL3
void rn_mul_comba3(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL4
void rn_mul_comba4(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL6
void rn_mul_comba6(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL7
void rn_mul_comba7(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL8
void rn_mul_comba8(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL9
void rn_mul_comba9(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL12
void rn_mul_comba12(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL17
void rn_mul_comba17(rni *A, rni *B, rni *C);
#endif

#ifdef RN_MUL20
void rn_mul_comba20(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL24
void rn_mul_comba24(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL28
void rn_mul_comba28(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL32
void rn_mul_comba32(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL48
void rn_mul_comba48(rni *A, rni *B, rni *C);
#endif
#ifdef RN_MUL64
void rn_mul_comba64(rni *A, rni *B, rni *C);
#endif

void rn_sqr_comba(rni *A, rni *B);

#ifdef RN_SMALL_SET
void rn_sqr_comba_small(rni *A, rni *B);
#endif

#ifdef RN_SQR3
void rn_sqr_comba3(rni *A, rni *B);
#endif
#ifdef RN_SQR4
void rn_sqr_comba4(rni *A, rni *B);
#endif
#ifdef RN_SQR6
void rn_sqr_comba6(rni *A, rni *B);
#endif
#ifdef RN_SQR7
void rn_sqr_comba7(rni *A, rni *B);
#endif
#ifdef RN_SQR8
void rn_sqr_comba8(rni *A, rni *B);
#endif
#ifdef RN_SQR9
void rn_sqr_comba9(rni *A, rni *B);
#endif
#ifdef RN_SQR12
void rn_sqr_comba12(rni *A, rni *B);
#endif
#ifdef RN_SQR17
void rn_sqr_comba17(rni *A, rni *B);
#endif

#ifdef RN_SQR20
void rn_sqr_comba20(rni *A, rni *B);
#endif
#ifdef RN_SQR24
void rn_sqr_comba24(rni *A, rni *B);
#endif
#ifdef RN_SQR28
void rn_sqr_comba28(rni *A, rni *B);
#endif
#ifdef RN_SQR32
void rn_sqr_comba32(rni *A, rni *B);
#endif
#ifdef RN_SQR48
void rn_sqr_comba48(rni *A, rni *B);
#endif
#ifdef RN_SQR64
void rn_sqr_comba64(rni *A, rni *B);
#endif
extern const char *rn_s_rmap;

#endif /* RBN_PRIV_H */

