/*
        PRIME.H - header file for PRIME.C

    Copyright (c) J.S.A.Kapp 1994 - 1996.

        RSAEURO - RSA Library compatible with RSAREF 2.0.

        Prime Number routines header file.
*/
int GeneratePrime PROTO_LIST
((
      NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, NN_DIGIT *,
      unsigned int, R_RANDOM_STRUCT *
));
