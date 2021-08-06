#include "pack.h"
#include "params.h"

#include <stdint.h>

#ifdef PARAM_1
void pack_poly(uint8_t* out, int64_t* in)
{
	uint64_t tmp1, tmp2, tmp3, tmp4;

	for (int i = 0; i < _hhN; i++)
	{
		tmp1 = in[4*i];
		tmp2 = in[4*i + 1];
		tmp3 = in[4*i + 2];
		tmp4 = in[4*i + 3];

		out[27*i +  0] = tmp1 >> 46;
		out[27*i +  1] = tmp1 >> 38;
		out[27*i +  2] = tmp1 >> 30;
		out[27*i +  3] = tmp1 >> 22;
		out[27*i +  4] = tmp1 >> 14;
		out[27*i +  5] = tmp1 >>  6;
		out[27*i +  6] = (tmp1 << 2) | ((tmp2 >> 52) & 0x03);
		out[27*i +  7] = tmp2 >> 44;
		out[27*i +  8] = tmp2 >> 36;
		out[27*i +  9] = tmp2 >> 28;		
		out[27*i + 10] = tmp2 >> 20;
		out[27*i + 11] = tmp2 >> 12;
		out[27*i + 12] = tmp2 >> 4;
		out[27*i + 13] = (tmp2 << 4) | ((tmp3 >> 50) & 0x0f);
		out[27*i + 14] = tmp3 >> 42;
		out[27*i + 15] = tmp3 >> 34;
		out[27*i + 16] = tmp3 >> 26;		
		out[27*i + 17] = tmp3 >> 18;
		out[27*i + 18] = tmp3 >> 10;
		out[27*i + 19] = tmp3 >>  2;
		out[27*i + 20] = (tmp3 << 6) | ((tmp4 >> 48) & 0x3f);
		out[27*i + 21] = tmp4 >> 40;
		out[27*i + 22] = tmp4 >> 32;
		out[27*i + 23] = tmp4 >> 24;		
		out[27*i + 24] = tmp4 >> 16;
		out[27*i + 25] = tmp4 >>  8;
		out[27*i + 26] = tmp4;
	}
}
#endif

#ifdef PARAM_2
void pack_poly(uint8_t* out, int64_t* in)
{
	uint64_t tmp1;
	uint64_t tmp2;

	for (int i = 0; i < _hN; i++)
	{
		tmp1 = in[2*i];
		tmp2 = in[2*i + 1];

		out[15*i +  0] = tmp1 >> 52;
		out[15*i +  1] = tmp1 >> 44;
		out[15*i +  2] = tmp1 >> 36;
		out[15*i +  3] = tmp1 >> 28;
		out[15*i +  4] = tmp1 >> 20;
		out[15*i +  5] = tmp1 >> 12;
		out[15*i +  6] = tmp1 >>  4;
		out[15*i +  7] = (tmp1 <<  4) | ((tmp2 >> 56) & 0x0f);
		out[15*i +  8] = tmp2 >> 48;
		out[15*i +  9] = tmp2 >> 40;
		out[15*i + 10] = tmp2 >> 32;
		out[15*i + 11] = tmp2 >> 24;
		out[15*i + 12] = tmp2 >> 16;
		out[15*i + 13] = tmp2 >> 8;
		out[15*i + 14] = tmp2;
	}
}
#endif

#ifdef PARAM_3
void pack_poly(uint8_t* out, int64_t* in)
{
	uint64_t tmp1, tmp2, tmp3, tmp4;

	for (int i = 0; i < _hhN; i++)
	{
		tmp1 = in[4*i];
		tmp2 = in[4*i + 1];
		tmp3 = in[4*i + 2];
		tmp4 = in[4*i + 3];

		//58 8 * 7 + 2
		out[29*i +  0] = tmp1 >> 50;
		out[29*i +  1] = tmp1 >> 42;
		out[29*i +  2] = tmp1 >> 34;
		out[29*i +  3] = tmp1 >> 26;
		out[29*i +  4] = tmp1 >> 18;
		out[29*i +  5] = tmp1 >> 10;
		out[29*i +  6] = tmp1 >>  2;
		out[29*i +  7] = (tmp1 << 6) | ((tmp2 >> 52) & 0x03f);
		out[29*i +  8] = tmp2 >> 44;
		out[29*i +  9] = tmp2 >> 36;
		out[29*i + 10] = tmp2 >> 28;		
		out[29*i + 11] = tmp2 >> 20;
		out[29*i + 12] = tmp2 >> 12;
		out[29*i + 13] = tmp2 >>  4;
		out[29*i + 14] = (tmp2 << 4) | ((tmp3 >> 54) & 0x0f);
		out[29*i + 15] = tmp3 >> 46;
		out[29*i + 16] = tmp3 >> 38;
		out[29*i + 17] = tmp3 >> 30;		
		out[29*i + 18] = tmp3 >> 22;
		out[29*i + 19] = tmp3 >> 14;
		out[29*i + 20] = tmp3 >>  6;
		out[29*i + 21] = (tmp3 << 2) | ((tmp4 >> 56) & 0x03);
		out[29*i + 22] = tmp4 >> 48;
		out[29*i + 23] = tmp4 >> 40;
		out[29*i + 24] = tmp4 >> 32;		
		out[29*i + 25] = tmp4 >> 24;
		out[29*i + 26] = tmp4 >> 16;
		out[29*i + 27] = tmp4 >>  8;		
		out[29*i + 28] = tmp4;
	}
}
#endif

void pack_s(uint8_t* out, int64_t in[][_N])
{
	uint8_t* tmpout;

	for (int i = 0; i < _M; i++)
	{
		tmpout = out + 64 * i;

		for (int j = 0; j < 64; j++)
		{
			tmpout[j] = ((in[i][4*j + 0] & 0x3) << 6) | ((in[i][4*j + 1] & 0x3) << 4) | ((in[i][4*j + 2] & 0x3) << 2) | (in[i][4*j + 3] & 0x3);
		}
	}
}

void pack_u(uint8_t* out, int64_t in[][_N])
{
	uint8_t* tmpout;

#ifdef PARAM_1
	for (int i = 0; i < _M; i++)
	{
		tmpout = out + i * 15 * 32;

		for (int j = 0; j < 32; j++)
		{
			tmpout[15*j +  0] = (in[i][8*j + 0] >> 7);
			tmpout[15*j +  1] = (in[i][8*j + 0] << 1) | ((in[i][8*j + 1] >> 14) & 0x01);
			tmpout[15*j +  2] = (in[i][8*j + 1] >> 6);
			tmpout[15*j +  3] = (in[i][8*j + 1] << 2) | ((in[i][8*j + 2] >> 13) & 0x03);
			tmpout[15*j +  4] = (in[i][8*j + 2] >> 5);		
			tmpout[15*j +  5] = (in[i][8*j + 2] << 3) | ((in[i][8*j + 3] >> 12) & 0x07);
			tmpout[15*j +  6] = (in[i][8*j + 3] >> 4);
			tmpout[15*j +  7] = (in[i][8*j + 3] << 4) | ((in[i][8*j + 4] >> 11) & 0x0f);
			tmpout[15*j +  8] = (in[i][8*j + 4] >> 3);
			tmpout[15*j +  9] = (in[i][8*j + 4] << 5) | ((in[i][8*j + 5] >> 10) & 0x1f);		
			tmpout[15*j + 10] = (in[i][8*j + 5] >> 2);
			tmpout[15*j + 11] = (in[i][8*j + 5] << 6) | ((in[i][8*j + 6] >>  9) & 0x3f);
			tmpout[15*j + 12] = (in[i][8*j + 6] >> 1);
			tmpout[15*j + 13] = (in[i][8*j + 6] << 7) | ((in[i][8*j + 7] >>  8) & 0x7f);						
			tmpout[15*j + 14] = (in[i][8*j + 7]);
		}
	}
#endif

#ifdef PARAM_2
	for (int i = 0; i < _M; i++)
	{
		tmpout = out + i * 512;

		for (int j = 0; j < 256; j++)
		{
			tmpout[2*j+0]  = in[i][j] >> 8;
			tmpout[2*j+1]  = in[i][j];
		}
	}
#endif
}

#ifdef PARAM_1
void unpack_poly(int64_t* out, uint8_t* in)
{
	int64_t tmp1;
	int64_t tmp2;

	for (int i = 0; i < _hhN; i++)
	{
		tmp1 = ((uint64_t) in[27*i + 0] << 46) | ((uint64_t) in[27*i + 1] << 38) | ((uint64_t) in[27*i + 2] << 30) | ((uint64_t) in[27*i + 3] << 22);
		tmp2 = ((uint64_t) in[27*i + 4] << 14) | ((uint64_t) in[27*i + 5] <<  6) | ((uint64_t) in[27*i + 6] >>  2);

		out[4*i] = tmp1 | tmp2;

		tmp1 = ((uint64_t) (in[27*i +  6] & 0x03) << 52) | ((uint64_t) in[27*i +  7] << 44) | ((uint64_t) in[27*i +  8] << 36) | ((uint64_t) in[27*i +  9] << 28);
		tmp2 = ((uint64_t)  in[27*i + 10]         << 20) | ((uint64_t) in[27*i + 11] << 12) | ((uint64_t) in[27*i + 12] <<  4) | ((uint64_t) in[27*i + 13] >>  4);

		out[4*i + 1] = tmp1 | tmp2;

		tmp1 = ((uint64_t) (in[27*i + 13] & 0x0f) << 50) | ((uint64_t) in[27*i + 14] << 42) | ((uint64_t) in[27*i + 15] << 34) | ((uint64_t) in[27*i + 16] << 26);
		tmp2 = ((uint64_t)  in[27*i + 17]         << 18) | ((uint64_t) in[27*i + 18] << 10) | ((uint64_t) in[27*i + 19] <<  2) | ((uint64_t) in[27*i + 20] >>  6);

		out[4*i + 2] = tmp1 | tmp2;

		tmp1 = ((uint64_t) (in[27*i +  20] & 0x3f) << 48) | ((uint64_t) in[27*i + 21] << 40) | ((uint64_t) in[27*i + 22] << 32) | ((uint64_t) in[27*i + 23] << 24);
		tmp2 = ((uint64_t)  in[27*i +  24]         << 16) | ((uint64_t) in[27*i + 25] <<  8) |  (uint64_t) in[27*i + 26];

		out[4*i + 3] = tmp1 | tmp2;
	}
}
#endif

#ifdef PARAM_2
void unpack_poly(int64_t* out, uint8_t* in)
{
	int64_t tmp1;
	int64_t tmp2;

	for (int i = 0; i < _hN; i++)
	{
		tmp1 = ((uint64_t) in[15*i + 0] << 52) | ((uint64_t) in[15*i + 1] << 44) | ((uint64_t) in[15*i + 2] << 36) | ((uint64_t) in[15*i + 3] << 28);
		tmp2 = ((uint64_t) in[15*i + 4] << 20) | ((uint64_t) in[15*i + 5] << 12) | ((uint64_t) in[15*i + 6] <<  4) | ((uint64_t) in[15*i + 7] >> 4);

		out[2*i] = tmp1 | tmp2;

		tmp1 = ((uint64_t) (in[15*i +  7] & 0xf) << 56) | ((uint64_t) in[15*i +  8] << 48) | ((uint64_t) in[15*i +  9] << 40) | ((uint64_t) in[15*i + 10] << 32);
		tmp2 = ((uint64_t)  in[15*i + 11] << 24       ) | ((uint64_t) in[15*i + 12] << 16) | ((uint64_t) in[15*i + 13] <<  8) | ((uint64_t) in[15*i + 14]);

		out[2*i + 1] = tmp1 | tmp2;
	}
}
#endif

#ifdef PARAM_3
void unpack_poly(int64_t* out, uint8_t* in)
{
	int64_t tmp1;
	int64_t tmp2;

	for (int i = 0; i < _hhN; i++)
	{
		tmp1 = ((uint64_t) in[29*i + 0] << 50) | ((uint64_t) in[29*i + 1] << 42) | ((uint64_t) in[29*i + 2] << 34) | ((uint64_t) in[29*i + 3] << 26);
		tmp2 = ((uint64_t) in[29*i + 4] << 18) | ((uint64_t) in[29*i + 5] << 10) | ((uint64_t) in[29*i + 6] <<  2) | ((uint64_t) in[29*i + 7] >>  6);

		out[4*i] = tmp1 | tmp2;

		tmp1 = ((uint64_t) (in[29*i +  7] & 0x3f) << 52) | ((uint64_t) in[29*i +  8] << 44) | ((uint64_t) in[29*i +  9] << 36) | ((uint64_t) in[29*i + 10] << 28);
		tmp2 = ((uint64_t)  in[29*i + 11]         << 20) | ((uint64_t) in[29*i + 12] << 12) | ((uint64_t) in[29*i + 13] <<  4) | ((uint64_t) in[29*i + 14] >>  4);

		out[4*i + 1] = tmp1 | tmp2;

		tmp1 = ((uint64_t) (in[29*i + 14] & 0x0f) << 54) | ((uint64_t) in[29*i + 15] << 46) | ((uint64_t) in[29*i + 16] << 38) | ((uint64_t) in[29*i + 17] << 30);
		tmp2 = ((uint64_t)  in[29*i + 18]         << 22) | ((uint64_t) in[29*i + 19] << 14) | ((uint64_t) in[29*i + 20] <<  6) | ((uint64_t) in[29*i + 21] >>  2);

		out[4*i + 2] = tmp1 | tmp2;

		tmp1 = ((uint64_t) (in[29*i +  21] & 0x03) << 56) | ((uint64_t) in[29*i + 22] << 48) | ((uint64_t) in[29*i + 23] << 40) | ((uint64_t) in[29*i + 24] << 32);
		tmp2 = ((uint64_t)  in[29*i +  25]         << 24) | ((uint64_t) in[29*i + 26] << 16) | ((uint64_t) in[29*i + 27] <<  8) | ((uint64_t) in[29*i + 28]);

		out[4*i + 3] = tmp1 | tmp2;
	}
}
#endif

void unpack_s(int64_t out[][_N], uint8_t* in)
{
	uint8_t* tmpin;

	for (int i = 0; i < _M; i++)
	{
		tmpin = in + 64 * i;

		for (int j = 0; j < 64; j++)
		{
			out[i][4*j + 0] = ((((int64_t)tmpin[j]) << 56) >> 62);
			out[i][4*j + 1] = ((((int64_t)tmpin[j]) << 58) >> 62);
			out[i][4*j + 2] = ((((int64_t)tmpin[j]) << 60) >> 62);				
			out[i][4*j + 3] = ((((int64_t)tmpin[j]) << 62) >> 62);
		}
	}
}

void unpack_u(int64_t out[][_N], uint8_t* in)
{
	uint8_t* tmpin;

#ifdef PARAM_1
	for (int i = 0; i < _M; i++)
	{
		tmpin = in + i * 32 * 15;

		for (int j = 0; j < 32; j++)
		{
			out[i][8*j + 0] =                                         (((uint64_t) tmpin[15*j +  0]) << 7) | (tmpin[15*j +  1] >> 1); 
			out[i][8*j + 1] = (((uint64_t) tmpin[15*j +  1]) << 14) | (((uint64_t) tmpin[15*j +  2]) << 6) | (tmpin[15*j +  3] >> 2);
			out[i][8*j + 2] = (((uint64_t) tmpin[15*j +  3]) << 13) | (((uint64_t) tmpin[15*j +  4]) << 5) | (tmpin[15*j +  5] >> 3);
			out[i][8*j + 3] = (((uint64_t) tmpin[15*j +  5]) << 12) | (((uint64_t) tmpin[15*j +  6]) << 4) | (tmpin[15*j +  7] >> 4);
			out[i][8*j + 4] = (((uint64_t) tmpin[15*j +  7]) << 11) | (((uint64_t) tmpin[15*j +  8]) << 3) | (tmpin[15*j +  9] >> 5);
			out[i][8*j + 5] = (((uint64_t) tmpin[15*j +  9]) << 10) | (((uint64_t) tmpin[15*j + 10]) << 2) | (tmpin[15*j + 11] >> 6);
			out[i][8*j + 6] = (((uint64_t) tmpin[15*j + 11]) <<  9) | (((uint64_t) tmpin[15*j + 12]) << 1) | (tmpin[15*j + 13] >> 7);
			out[i][8*j + 7] = (((uint64_t) tmpin[15*j + 13]) << 8) | (tmpin[15*j + 14]);
		}

		for (int j = 0; j < _N; j++)
		{
			out[i][j] = (out[i][j] << 49) >> 49; 
		}
	}
#endif

#ifdef PARAM_2
	for (int i = 0; i < _M; i++)
	{
		tmpin = in + i * 512;

		for (int j = 0; j < 256; j++)
		{
			out[i][j]  = ((((int64_t) tmpin[2*j] << 8) | tmpin[2*j+1]) << 48) >> 48;
		}
	}
#endif
}