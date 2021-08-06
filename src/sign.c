#include <sign.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#include "rng.h"

#include "poly.h"
#include "pack.h"
#include "sample.h"
#include "reduce.h"

int crypto_sign_keypair(unsigned char *pk, unsigned char *sk)
{
	int8_t seed[32];

	int64_t a[_M][_N];
	int64_t s[_M][_N];
	int64_t b[_N];

	//generate vector a
	randombytes(pk, 32);
	sample_a(a, pk);

	//generate vector s
	randombytes(seed, 32);
	sample_s(s, seed);
	pack_s(sk, s);
	polyvec_cadd(s);
	
	//b = <a,s>
	polyvec_mul(b, a, s);

	//encode public & secret key 
	pack_poly(pk + 32, b);
	memcpy(sk + 256, pk, 32);

	return 0;
}

int crypto_sign(unsigned char *sm, unsigned long long *smlen,
            unsigned char *m, unsigned long long mlen,
            unsigned char *sk)
{
	unsigned char seed[32];
	unsigned char tmp[POLY_BYTES];

	int check = 0;

	SHA256_CTX ctx;

	int64_t a[_M][_N];
	int64_t s[_M][_N];
	int64_t r[_M][_N];
	int64_t u[_M][_N];	
	int64_t v[_N];
	int64_t c[_N];	

	//decode secret key
	unpack_s(s, sk);
	sample_a(a, sk + 256);

	while(check == 0)
	{
		randombytes(seed, 32);
		sample_r(r, seed);
		polyvec_cadd(r);

		//generate challenge
		polyvec_mul(v, a, r);
		pack_poly(tmp ,v);

		//c = H(v,m)
		SHA256_Init(&ctx);
		SHA256_Update(&ctx, tmp, POLY_BYTES);
		SHA256_Update(&ctx, m, mlen);
		SHA256_Final(seed, &ctx);

		poly_init(c);
		sample_c(c, seed);
		poly_cadd(c);

		//u = r + sc
		poly_polyvec_mul(u, c, s);
		//if(poly_reject_cs(u) == 0) continue;

		polyvec_add(u, u, r);

		//check rejection
		check = poly_reject_U(u);
	}

	pack_u(sm, u);
	memcpy(sm + U_BYTES, seed, 32);
	memcpy(sm + CRYPTO_BYTES, m, mlen);

	*smlen = CRYPTO_BYTES + mlen;

	return 0;
}

int crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                 unsigned char *sm, unsigned long long smlen,
                 unsigned char *pk)
{
	int64_t a[_M][_N];
	int64_t u[_M][_N];	
	int64_t b[_N];
	int64_t c[_N];	
	int64_t tmp1[_N];
	int64_t tmp2[_N];

	unsigned char digest[32];
	unsigned char tmp[POLY_BYTES];

	SHA256_CTX ctx;

	//unpack public key
	sample_a(a, pk);
	unpack_poly(b, pk + 32);

	//unpack signature
	unpack_u(u, sm);
	if(poly_reject_U(u) == 0) return 0;
	polyvec_cadd(u);

	sample_c(c, sm + U_BYTES);
	poly_cadd(c);

	//v = a u - c b
	polyvec_mul(tmp1, a, u);
	poly_mul(tmp2, b, c);
	poly_sub(tmp1, tmp1, tmp2);

	//c = H(v,m)
	pack_poly(tmp, tmp1);
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, tmp, POLY_BYTES);
	SHA256_Update(&ctx, sm + CRYPTO_BYTES, smlen - CRYPTO_BYTES);
	SHA256_Final(digest, &ctx);

	//compare
	if(memcmp(digest, sm + U_BYTES, 32) == 0)
	{
		memcpy(m, sm + CRYPTO_BYTES, smlen - CRYPTO_BYTES);
		*mlen = smlen - CRYPTO_BYTES;

		return 1;
	}
	else
		return 0;
}