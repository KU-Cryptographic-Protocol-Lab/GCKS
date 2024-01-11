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
#include "ntt.h"


unsigned long long ctr_sign;



int crypto_sign_keypair(unsigned char *pk, unsigned char *sk)
{
	uint16_t nonce = 0;
	int8_t seed_s[32];
	int32_t A[_K][_M][_N];
	int32_t s[_M][_N];
	int32_t A2[_K][_M][_N];
	int32_t s2[_M][_N];
	int32_t T[_K][_N] = {0};
	
	randombytes(pk, 32);
	sample_A(A, pk, nonce++);

	randombytes(seed_s, 32);
	sample_s(s, seed_s, nonce++);

	#ifdef Raw_s // Setting secret key with original small s
	pack_s(sk, s);
	#endif

	polyvec_cadd(s);
	
	for(int j=0; j<_M; j++)
		ntt(s[j]);	

	polymat_mul(T, A, s);
	polyvec_cadd(s);
	#ifdef Raw_s
	memcpy(sk + _M * _hhN, pk, 32);
	#endif

	#ifdef NTT_s // Setting secret key with ntt(s) to reduce the number of ntt operations in sign phase
	pack_polyvec_s(sk, s);
	
	memcpy(sk + _M * POLY_BYTES, pk, 32);
	#endif

	for (int i = 0; i < _K; i++)
		poly_cadd(T[i]);
	
	pack_polyvec(pk + 32, T);
	
	return 0;

	
}

int crypto_sign(unsigned char *sm, unsigned long long *smlen,
            unsigned char *m, unsigned long long mlen,
            unsigned char *sk)
{
    uint16_t nonce = 0;
	unsigned char seed[32];
	unsigned char TMP[POLYVEC_BYTES];

	int check = 0;
	ctr_sign=0;

	SHA256_CTX ctx;

	int32_t A[_K][_M][_N];
	int32_t s[_M][_N];
	int32_t y[_M][_N];
	int32_t z[_M][_N] = {0};
	int32_t c[_N];	
	
	#ifdef Raw_s
	//unpack public key
	sample_A(A, sk + _M*_hhN, nonce++);
	
	//decode secret key
	unpack_s(s, sk);
	#endif

	#ifdef NTT_s
	//unpack public key
	sample_A(A, sk + _M*POLY_BYTES, nonce++);
	//decode secret key
	unpack_polyvec_s(s, sk);
	#endif
	
//	for(int j=0; j<_M; j++)
//		ntt(s[j]);	
	
	randombytes(seed, 32);
	
	
	while(check == 0)
	{
		ctr_sign++;
		int32_t V[_K][_N] = {0};
		sample_y(y, seed, nonce++);
		polyvec_cadd(y);

		
		//generate challenge c = H(ay, m)

		for(int j=0; j<_M; j++)
			ntt(y[j]);	
		polymat_mul(V, A, y);
		pack_polyvec(TMP, V);
	
		//c = H(v,m)
		SHA256_Init(&ctx);
		SHA256_Update(&ctx, TMP, POLYVEC_BYTES); //PROBLEM!!
		SHA256_Update(&ctx, m, mlen);
		SHA256_Final(seed, &ctx);
		sample_c(c, seed);
		ntt(c);
	
		//z = y + sc	
		for(int i = 0; i < _M; i++)
			poly_basemul(z[i], c, s[i]);
		
		polyvec_add(z, z, y); 
		
		for(int j=0; j<_M; j++)
			{
				invntt(z[j]);
			}

		//check rejection
		check = poly_reject_z(z);
	}

	pack_z(sm, z);
	memcpy(sm + Z_BYTES, seed, 32);
	memcpy(sm + CRYPTO_BYTES, m, mlen);

	*smlen = CRYPTO_BYTES + mlen;

	return 0;
}

int crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                 unsigned char *sm, unsigned long long smlen,
                 unsigned char *pk)
{
    uint16_t nonce = 0;
	int32_t A[_K][_M][_N];
	int32_t z[_M][_N];	
	int32_t T[_K][_N];
	int32_t c[_N];	
	
	int32_t TMP1[_K][_N] = {0};
	int32_t TMP2[_K][_N];
	int32_t TMP3[_K][_N] = {0};
		
	unsigned char digest[32];
	unsigned char TMP[POLYVEC_BYTES];

	SHA256_CTX ctx;

	//unpack public key
	sample_A(A, pk, nonce);
	unpack_polyvec(T, pk + 32);
	
	//unpack signature
	unpack_z(z, sm);
	
	if(poly_reject_z(z) == 0) return 0;
	sample_c(c, sm + Z_BYTES);		
	
	//v = a z - c t
	ntt(c);
	for(int j=0; j<_M; j++)
		ntt(z[j]);

	polymat_mul(TMP1, A, z);

	for(int i = 0; i < _K; i++)
		poly_basemul(TMP2[i], c, T[i]);

	polyvec_sub(TMP1, TMP1, TMP2); // tmp1 = az - tc
	for(int i = 0; i < _K; i++)
		for(int j = 0; j < _N; j++)
			TMP1[i][j]=barrett_reduce(TMP1[i][j]);
		
	pack_polyvec(TMP, TMP1);

	SHA256_Init(&ctx);
	SHA256_Update(&ctx, TMP, POLYVEC_BYTES); //PROBLEM!!
	SHA256_Update(&ctx, sm + CRYPTO_BYTES, smlen - CRYPTO_BYTES);
	SHA256_Final(digest, &ctx);

	//compare
	if(memcmp(digest, sm + Z_BYTES, 32) == 0)
	{
		memcpy(m, sm + CRYPTO_BYTES, smlen - CRYPTO_BYTES);
		*mlen = smlen - CRYPTO_BYTES;

		return 0;
	}
	else
		return 1;
}