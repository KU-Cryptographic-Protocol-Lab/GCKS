#ifndef __SIGN_H__
#define __SIGN_H__

#include "params.h"
#include "poly.h"

#define U_BYTES ((_log_B + 1) * 32 * _M)
#define S_BYTES ((_N * _M) >> 2)

#define CRYPTO_PUBLICKEYBYTES (32 + POLY_BYTES)
#define CRYPTO_SECRETKEYBYTES (256 + 32)
#define CRYPTO_BYTES (U_BYTES + 32)



int 
crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

int
crypto_sign(unsigned char *sm, unsigned long long *smlen,
            unsigned char *m, unsigned long long mlen,
            unsigned char *sk);

int
crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                 unsigned char *sm, unsigned long long smlen,
                 unsigned char *pk);

#endif
