#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "NIST/rng.h"
#include "sign.h"
#include "reduce.h"
#include "pack.h"
#include "sample.h"

#define TEST_LOOP 10000

int64_t cpucycles(void)
{
	unsigned int hi, lo;

    __asm__ __volatile__ ("rdtsc\n\t" : "=a" (lo), "=d"(hi));

    return ((int64_t)lo) | (((int64_t)hi) << 32);
}

int test1()
{
	unsigned char pk[CRYPTO_PUBLICKEYBYTES];
	unsigned char sk[CRYPTO_SECRETKEYBYTES];

	unsigned char  m[100] = "hessllo world!";
	unsigned char sm[CRYPTO_BYTES + 200];

	unsigned char  m2[100];

	unsigned long long  mlen = 0;
	unsigned long long smlen;

	unsigned long long  m2len;

	int result;

    unsigned long long kcycles, ecycles, dcycles;
    unsigned long long cycles1, cycles2;

    mlen = strlen(m);

	printf("CRYPTO_PUBLICKEYBYTES : %d\n", CRYPTO_PUBLICKEYBYTES);
	printf("CRYPTO_SECRETKEYBYTES : %d\n", CRYPTO_SECRETKEYBYTES);
	printf("CRYPTO_BYTES : %d\n", CRYPTO_BYTES);

	printf("KeyGen\n");
	kcycles=0;
	for (int i = 0; i < TEST_LOOP; i++)
	{
		cycles1 = cpucycles();
		crypto_sign_keypair(pk, sk);
		cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
	}
    printf("  KeyGen runs in ................. %8lld cycles", kcycles/TEST_LOOP);
    printf("\n"); 


	printf("Sign\n");
	kcycles=0;
	for (int i = 0; i < TEST_LOOP; i++)
	{
		cycles1 = cpucycles();
		crypto_sign(sm, &smlen, m, mlen, sk);
		cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
	}
    printf("  Sign runs in ................. %8lld cycles", kcycles/TEST_LOOP);
    printf("\n"); 


	printf("Verify\n");
	kcycles=0;
	for (int i = 0; i < TEST_LOOP; i++)
	{
		cycles1 = cpucycles();
		result = crypto_sign_open(m2, &m2len, sm, smlen, pk);
		cycles2 = cpucycles();
        kcycles += cycles2-cycles1;
	}
    printf("  Verify runs in ................. %8lld cycles", kcycles/TEST_LOOP);
    printf("\n"); 

  	if(result == 1)
	{
		printf("Verification Success!\n");
		printf("msg : ");
		for (int i = 0; i < m2len; ++i)
		{
			printf("%c", m2[i]);
		}
		printf("\n");
	}
	else
	{
		printf("Verification Fail\n");
	}

	return 0;
}


int main(int argc, char const *argv[])
{
	test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();	
}