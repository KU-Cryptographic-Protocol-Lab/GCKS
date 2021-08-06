#include "sample.h"
#include "NIST/rng.h"

int sample_a(int64_t out[][_N], uint8_t* seed)
{
	int j = 0;
	uint64_t tmp;

	AES_XOF_struct ctx;
	uint8_t domain[8] = {'G','e','n','A',0,0,0,0};

	seedexpander_init(&ctx, seed, domain, 1000000);
	
	for(int i = 0; i < _M; i++)
	{
		j = 0;

		while(j < _N)
		{
			seedexpander(&ctx, (unsigned char*)&tmp, 8);

			tmp = tmp & ((1L << _log_P) - 1);

			if(tmp < _P)
			{
				out[i][j] = tmp;
				j++;
			}					
		}
	}

	return 0;
}

int sample_s(int64_t out[][_N], uint8_t* seed)
{
	int j = 0;
	uint8_t tmp;

	AES_XOF_struct ctx;
	uint8_t domain[8] = {'G','e','n','A',0,0,0,0};

	seedexpander_init(&ctx, seed, domain, 1000000);
	
	for(int i=0; i < _M; i++)
	{
		j = 0;

		while(j < _N)
		{
			seedexpander(&ctx, &tmp, 1);
			
			if(tmp != 255)
			{
				out[i][j] = (tmp % 3) - 1;
				j++;
			}
		}
	}

	return 0;
}

int sample_r(int64_t out[][_N], uint8_t* seed)
{
	int j = 0;
	uint8_t tmp[2];

	AES_XOF_struct ctx;
	uint8_t domain[8] = {'G','e','n','A',0,0,0,0};

	seedexpander_init(&ctx, seed, domain, 1000000);
	
	for(int i=0; i < _M; i++)
	{
		j = 0;

		while(j < _N)
		{
			int tmp2;

			seedexpander(&ctx, tmp, 2);
			
			tmp2 = (int) tmp[0] << 8 | tmp[1];
#ifdef PARAM_1			
			tmp2 = tmp2 & ((1L << (_log_B + 1)) - 1);
#endif
		
			if(tmp2 < _B * 2 + 1)
			{
				out[i][j] = tmp2 - _B;
				j++;
			}
		}
	}

	return 0;
}

int sample_c(int64_t* out, uint8_t* in)
{
	AES_XOF_struct ctx;
	uint8_t domain[8] = {'G','e','n','A',0,0,0,0};
	uint8_t tmp;
	uint8_t sign[(_H >> 3) + 1];

	int count = 0;

	poly_init(out);

	seedexpander_init(&ctx, in, domain, 1000000);
	seedexpander(&ctx, sign, (_H >> 3) + 1);

	while(count < _H)
	{
		seedexpander(&ctx, &tmp, 1);

		if(out[tmp] == 0)
		{
			out[tmp] = ((sign[count >> 3] >> (7 - count % 8)) & 0x1) * 2 - 1;
			count++;
		}
	}

	return 0;
}

