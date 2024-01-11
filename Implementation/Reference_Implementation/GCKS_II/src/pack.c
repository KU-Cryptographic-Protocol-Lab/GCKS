#include "pack.h"
#include "params.h"

#include <stdint.h>

#ifdef PARAM_1
void pack_poly(uint8_t* out, int32_t* in)
{
	uint32_t tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;

	for (int i = 0; i < _hhhN; i++)
	{
		tmp1 = in[8*i];
		tmp2 = in[8*i + 1];
		tmp3 = in[8*i + 2];
		tmp4 = in[8*i + 3];
		tmp5 = in[8*i + 4];
		tmp6 = in[8*i + 5];
		tmp7 = in[8*i + 6];
		tmp8 = in[8*i + 7];

		out[25*i +  0] = tmp1 >> 17;
		out[25*i +  1] = tmp1 >>  9;
		out[25*i +  2] = tmp1 >>  1;
		out[25*i +  3] = (tmp1 << 7) | ((tmp2 >> 18) & 0x7f);
		out[25*i +  4] = tmp2 >> 10;
		out[25*i +  5] = tmp2 >>  2;
		out[25*i +  6] = (tmp2 << 6) | ((tmp3 >> 19) & 0x3f);
		out[25*i +  7] = tmp3 >> 11;
		out[25*i +  8] = tmp3 >>  3;
		out[25*i +  9] = (tmp3 << 5) | ((tmp4 >> 20) & 0x1f);
		out[25*i + 10] = tmp4 >> 12;
		out[25*i + 11] = tmp4 >>  4;
		out[25*i + 12] = (tmp4 << 4) | ((tmp5 >> 21) & 0x0f);
		out[25*i + 13] = tmp5 >> 13;
		out[25*i + 14] = tmp5 >>  5;
		out[25*i + 15] = (tmp5 << 3) | ((tmp6 >> 22) & 0x07);
		out[25*i + 16] = tmp6 >> 14;	
		out[25*i + 17] = tmp6 >>  6;		
		out[25*i + 18] = (tmp6 << 2) | ((tmp7 >> 23) & 0x03);
		out[25*i + 19] = tmp7 >> 15;
		out[25*i + 20] = tmp7 >>  7;
		out[25*i + 21] = (tmp7 << 1) | ((tmp8 >> 24) & 0x01);
		out[25*i + 22] = tmp8 >> 16;
		out[25*i + 23] = tmp8 >>  8;
		out[25*i + 24] = tmp8;		
		
	}
}
#endif

#ifdef PARAM_2
void pack_poly(uint8_t* out, int32_t* in)
{
	uint32_t tmp1, tmp2, tmp3, tmp4;

	for (int i = 0; i < _hhN; i++)
	{
		tmp1 = in[4*i];
		tmp2 = in[4*i + 1];
		tmp3 = in[4*i + 2];
		tmp4 = in[4*i + 3];


		out[13*i +  0] = tmp1 >> 18;
		out[13*i +  1] = tmp1 >> 10;
		out[13*i +  2] = tmp1 >>  2;
		out[13*i +  3] = (tmp1 <<  6) | ((tmp2 >>20) & 0x3f);
		out[13*i +  4] = tmp2 >> 12;
		out[13*i +  5] = tmp2 >>  4;
		out[13*i +  6] = (tmp2 <<  4) | ((tmp3 >> 22) & 0x0f);
		out[13*i +  7] = tmp3 >> 14;
		out[13*i +  8] = tmp3 >>  6;
		out[13*i +  9] = (tmp3 <<  2) | ((tmp4 >> 24) & 0x03);
		out[13*i + 10] = tmp4 >> 16;
		out[13*i + 11] = tmp4 >>  8;
		out[13*i + 12] = tmp4;
		
	}
}
#endif

#ifdef PARAM_3
void pack_poly(uint8_t* out, int32_t* in)
{
	uint32_t tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;

	for (int i = 0; i < _hhhN; i++)
	{
		tmp1 = in[8*i];
		tmp2 = in[8*i + 1];
		tmp3 = in[8*i + 2];
		tmp4 = in[8*i + 3];
		tmp5 = in[8*i + 4];
		tmp6 = in[8*i + 5];
		tmp7 = in[8*i + 6];
		tmp8 = in[8*i + 7];

		out[27*i +  0] = tmp1 >> 19;
		out[27*i +  1] = tmp1 >> 11;
		out[27*i +  2] = tmp1 >>  3;
		out[27*i +  3] = (tmp1 << 5) | ((tmp2 >> 22) & 0x1f);
		out[27*i +  4] = tmp2 >> 14;
		out[27*i +  5] = tmp2 >>  6;
		out[27*i +  6] = (tmp2 << 2) | ((tmp3 >> 25) & 0x03);
		out[27*i +  7] = tmp3 >> 17;
		out[27*i +  8] = tmp3 >>  9;
		out[27*i +  9] = tmp3 >>  1;		
		out[27*i + 10] = (tmp3 << 7) | ((tmp4 >> 20) & 0x7f);
		out[27*i + 11] = tmp4 >> 12;
		out[27*i + 12] = tmp4 >>  4;
		out[27*i + 13] = (tmp4 << 4) | ((tmp5 >> 23) & 0x0f);
		out[27*i + 14] = tmp5 >> 15;
		out[27*i + 15] = tmp5 >>  7;
		out[27*i + 16] = (tmp5 << 1) | ((tmp6 >> 26) & 0x01);
		out[27*i + 17] = tmp6 >> 18;		
		out[27*i + 18] = tmp6 >> 10;
		out[27*i + 19] = tmp6 >>  2;
		out[27*i + 20] = (tmp6 << 6) | ((tmp7 >> 21) & 0x3f);
		out[27*i + 21] = tmp7 >> 13;
		out[27*i + 22] = tmp7 >>  5;
		out[27*i + 23] = (tmp7 << 3) | ((tmp8 >> 24) & 0x07);
		out[27*i + 24] = tmp8 >> 16;		
		out[27*i + 25] = tmp8 >>  8;
		out[27*i + 26] = tmp8;
	}
}
#endif


void pack_s(uint8_t* out, int32_t in[][_N])
{
	uint8_t* tmpout;

	for (int i = 0; i < _M; i++)
	{
		tmpout = out + _hhN * i;

		for (int j = 0; j < _hhN; j++)
		{
			tmpout[j] = ((in[i][4*j + 0] & 0x3) << 6) | ((in[i][4*j + 1] & 0x3) << 4) | ((in[i][4*j + 2] & 0x3) << 2) | (in[i][4*j + 3] & 0x3);
		}
	}
}

void pack_z(uint8_t* out, int32_t in[][_N])
{
	uint8_t* tmpout;

#ifdef PARAM_1
	for (int i = 0; i < _M; i++)
	{
		tmpout = out + i * 2 * _N;

		for (int j = 0; j < _N; j++)
		{
			tmpout[2*j + 0] = (in[i][j] >> 8);
			tmpout[2*j + 1] = (in[i][j]     );
		}
	}
#endif

#ifdef PARAM_2
	for (int i = 0; i < _M; i++)
	{
		tmpout = out + i * 17 * _hhhN;

		for (int j = 0; j < _hhhN; j++)
		{
			tmpout[17*j +  0] = (in[i][8*j + 0] >> 9);
			tmpout[17*j +  1] = (in[i][8*j + 0] >> 1);
			tmpout[17*j +  2] = (in[i][8*j + 0] << 7) | ((in[i][8*j + 1] >> 10) & 0x7f);
			tmpout[17*j +  3] = (in[i][8*j + 1] >> 2);
			tmpout[17*j +  4] = (in[i][8*j + 1] << 6) | ((in[i][8*j + 2] >> 11) & 0x3f);
			tmpout[17*j +  5] = (in[i][8*j + 2] >> 3);
			tmpout[17*j +  6] = (in[i][8*j + 2] << 5) | ((in[i][8*j + 3] >> 12) & 0x1f);
			tmpout[17*j +  7] = (in[i][8*j + 3] >> 4);
			tmpout[17*j +  8] = (in[i][8*j + 3] << 4) | ((in[i][8*j + 4] >> 13) & 0x0f);
			tmpout[17*j +  9] = (in[i][8*j + 4] >> 5);
			tmpout[17*j + 10] = (in[i][8*j + 4] << 3) | ((in[i][8*j + 5] >> 14) & 0x07);
			tmpout[17*j + 11] = (in[i][8*j + 5] >> 6);
			tmpout[17*j + 12] = (in[i][8*j + 5] << 2) | ((in[i][8*j + 6] >> 15) & 0x03);
			tmpout[17*j + 13] = (in[i][8*j + 6] >> 7);					
			tmpout[17*j + 14] = (in[i][8*j + 6] << 1) | ((in[i][8*j + 7] >> 16) & 0x01);					
			tmpout[17*j + 15] = (in[i][8*j + 7] >> 8);					
			tmpout[17*j + 16] = (in[i][8*j + 7]);						

		}
	}
#endif


#ifdef PARAM_3
	for (int i = 0; i < _M; i++)
	{
		tmpout = out + i * 19 * _hhhN;

		for (int j = 0; j < _hhhN; j++)
		{
			tmpout[19*j +  0] = (in[i][8*j + 0] >>11);
			tmpout[19*j +  1] = (in[i][8*j + 0] >> 3);
			tmpout[19*j +  2] = (in[i][8*j + 0] << 5) | ((in[i][8*j + 1] >> 14) & 0x1f);
			tmpout[19*j +  3] = (in[i][8*j + 1] >> 6);
			tmpout[19*j +  4] = (in[i][8*j + 1] << 2) | ((in[i][8*j + 2] >> 17) & 0x03);
			tmpout[19*j +  5] = (in[i][8*j + 2] >> 9);
			tmpout[19*j +  6] = (in[i][8*j + 2] >> 1);
			tmpout[19*j +  7] = (in[i][8*j + 2] << 7) | ((in[i][8*j + 3] >> 12) & 0x7f);
			tmpout[19*j +  8] = (in[i][8*j + 3] >> 4);
			tmpout[19*j +  9] = (in[i][8*j + 3] << 4) | ((in[i][8*j + 4] >> 15) & 0x0f);
			tmpout[19*j + 10] = (in[i][8*j + 4] >> 7);
			tmpout[19*j + 11] = (in[i][8*j + 4] << 1) | ((in[i][8*j + 5] >> 18) & 0x01);
			tmpout[19*j + 12] = (in[i][8*j + 5] >>10);
			tmpout[19*j + 13] = (in[i][8*j + 5] >> 2);
			tmpout[19*j + 14] = (in[i][8*j + 5] << 6) | ((in[i][8*j + 6] >> 13) & 0x3f);
			tmpout[19*j + 15] = (in[i][8*j + 6] >> 5);					
			tmpout[19*j + 16] = (in[i][8*j + 6] << 3) | ((in[i][8*j + 7] >> 16) & 0x07);					
			tmpout[19*j + 17] = (in[i][8*j + 7] >> 8);					
			tmpout[19*j + 18] = (in[i][8*j + 7]);						

		}
	}
#endif
}


#ifdef PARAM_1
void unpack_poly(int32_t* out, uint8_t* in)
{
	int32_t tmp1;
	int32_t tmp2;

	for (int i = 0; i < _hhhN; i++)
	{
		out[8*i    ] = ((uint32_t)  in[25*i + 0] << 17)         | ((uint32_t) in[25*i + 1] <<  9) | ((uint32_t) in[25*i + 2] <<  1) | ((uint32_t) in[25*i + 3] >> 7);
		out[8*i + 1] = ((uint32_t) (in[25*i + 3] & 0x7f) << 18) | ((uint32_t) in[25*i + 4] << 10) | ((uint32_t) in[25*i + 5] <<  2) | ((uint32_t) in[25*i + 6] >> 6);
		out[8*i + 2] = ((uint32_t) (in[25*i + 6] & 0x3f) << 19) | ((uint32_t) in[25*i + 7] << 11) | ((uint32_t) in[25*i + 8] <<  3) | ((uint32_t) in[25*i + 9] >> 5);
		out[8*i + 3] = ((uint32_t) (in[25*i + 9] & 0x1f) << 20) | ((uint32_t) in[25*i +10] << 12) | ((uint32_t) in[25*i +11] <<  4) | ((uint32_t) in[25*i +12] >> 4);
		out[8*i + 4] = ((uint32_t) (in[25*i +12] & 0x0f) << 21) | ((uint32_t) in[25*i +13] << 13) | ((uint32_t) in[25*i +14] <<  5) | ((uint32_t) in[25*i +15] >> 3);
		out[8*i + 5] = ((uint32_t) (in[25*i +15] & 0x07) << 22) | ((uint32_t) in[25*i +16] << 14) | ((uint32_t) in[25*i +17] <<  6) | ((uint32_t) in[25*i +18] >> 2);
		out[8*i + 6] = ((uint32_t) (in[25*i +18] & 0x03) << 23) | ((uint32_t) in[25*i +19] << 15) | ((uint32_t) in[25*i +20] <<  7) | ((uint32_t) in[25*i +21] >> 1);
		out[8*i + 7] = ((uint32_t) (in[25*i +21] & 0x01) << 24) | ((uint32_t) in[25*i +22] << 16) | ((uint32_t) in[25*i +23] <<  8) |  (uint32_t) in[25*i +24];
	}
}
#endif

#ifdef PARAM_2
void unpack_poly(int32_t* out, uint8_t* in)
{
	int32_t tmp1;
	int32_t tmp2;
	int32_t tmp3;
	int32_t tmp4;

	for (int i = 0; i < _hhN; i++)
	{
		out[4*i    ] = ((uint32_t)  in[13*i + 0] << 18)         | ((uint32_t) in[13*i + 1] << 10) | ((uint32_t) in[13*i + 2] <<  2) | ((uint32_t) in[13*i + 3] >> 6);
		out[4*i + 1] = ((uint32_t) (in[13*i + 3] & 0x3f) << 20) | ((uint32_t) in[13*i + 4] << 12) | ((uint32_t) in[13*i + 5] <<  4) | ((uint32_t) in[13*i + 6] >> 4);
		out[4*i + 2] = ((uint32_t) (in[13*i + 6] & 0x0f) << 22) | ((uint32_t) in[13*i + 7] << 14) | ((uint32_t) in[13*i + 8] <<  6) | ((uint32_t) in[13*i + 9] >> 2);
		out[4*i + 3] = ((uint32_t) (in[13*i + 9] & 0x03) << 24) | ((uint32_t) in[13*i +10] << 16) | ((uint32_t) in[13*i +11] <<  8) |  (uint32_t) in[13*i +12];
	}
}
#endif


#ifdef PARAM_3
void unpack_poly(int32_t* out, uint8_t* in)
{
	int32_t tmp1;
	int32_t tmp2;

	for (int i = 0; i < _hhhN; i++)
	{
		out[8*i    ] = ((uint32_t)  in[27*i + 0] << 19)         | ((uint32_t) in[27*i + 1] << 11) | ((uint32_t) in[27*i + 2] <<  3) | ((uint32_t) in[27*i + 3] >> 5);
		out[8*i + 1] = ((uint32_t) (in[27*i + 3] & 0x1f) << 22) | ((uint32_t) in[27*i + 4] << 14) | ((uint32_t) in[27*i + 5] <<  6) | ((uint32_t) in[27*i + 6] >> 2);
		out[8*i + 2] = ((uint32_t) (in[27*i + 6] & 0x03) << 25) | ((uint32_t) in[27*i + 7] << 17) | ((uint32_t) in[27*i + 8] <<  9) | ((uint32_t) in[27*i + 9] << 1) | ((uint32_t) in[27*i + 10] >> 7);
		out[8*i + 3] = ((uint32_t) (in[27*i +10] & 0x7f) << 20) | ((uint32_t) in[27*i +11] << 12) | ((uint32_t) in[27*i +12] <<  4) | ((uint32_t) in[27*i +13] >> 4);
		out[8*i + 4] = ((uint32_t) (in[27*i +13] & 0x0f) << 23) | ((uint32_t) in[27*i +14] << 15) | ((uint32_t) in[27*i +15] <<  7) | ((uint32_t) in[27*i +16] >> 1);
		out[8*i + 5] = ((uint32_t) (in[27*i +16] & 0x01) << 26) | ((uint32_t) in[27*i +17] << 18) | ((uint32_t) in[27*i +18] << 10) | ((uint32_t) in[27*i +19] << 2) | ((uint32_t) in[27*i + 20] >> 6);
		out[8*i + 6] = ((uint32_t) (in[27*i +20] & 0x3f) << 21) | ((uint32_t) in[27*i +21] << 13) | ((uint32_t) in[27*i +22] <<  5) | ((uint32_t) in[27*i +23] >> 3);
		out[8*i + 7] = ((uint32_t) (in[27*i +23] & 0x07) << 24) | ((uint32_t) in[27*i +24] << 16) | ((uint32_t) in[27*i +25] <<  8) |  (uint32_t) in[27*i +26];
	}
}
#endif
		

void unpack_s(int32_t out[][_N], uint8_t* in)
{
	uint8_t* tmpin;

	for (int i = 0; i < _M; i++)
	{
		tmpin = in + _hhN * i;

		for (int j = 0; j < _hhN; j++)
		{
			out[i][4*j + 0] = ((((int64_t)tmpin[j]) << 56) >> 62);
			out[i][4*j + 1] = ((((int64_t)tmpin[j]) << 58) >> 62);
			out[i][4*j + 2] = ((((int64_t)tmpin[j]) << 60) >> 62);				
			out[i][4*j + 3] = ((((int64_t)tmpin[j]) << 62) >> 62);
		}
	}
}

void unpack_z(int32_t out[][_N], uint8_t* in)
{
	uint8_t* tmpin;

#ifdef PARAM_1
	for (int i = 0; i < _M; i++)
	{
		tmpin = in + i * _N *  2;

		for (int j = 0; j < _N; j++)
		{
			out[i][j] = (((uint32_t) tmpin[2*j +  0]) << 8) | (tmpin[2*j +  1]); 
		}

		for (int j = 0; j < _N; j++)
		{
			out[i][j] = (out[i][j] << 16) >> 16; 
		}
	}
#endif

#ifdef PARAM_2
	for (int i = 0; i < _M; i++)
	{
		tmpin = in + i * _hhhN * 17;

		for (int j = 0; j < _hhhN; j++)
		{
			out[i][8*j + 0] = (((uint32_t) tmpin[17*j +  0]) <<  9) | (((uint32_t) tmpin[17*j +  1]) << 1) | (tmpin[17*j +  2] >> 7); 
			out[i][8*j + 1] = (((uint32_t) tmpin[17*j +  2]) << 10) | (((uint32_t) tmpin[17*j +  3]) << 2) | (tmpin[17*j +  4] >> 6);
			out[i][8*j + 2] = (((uint32_t) tmpin[17*j +  4]) << 11) | (((uint32_t) tmpin[17*j +  5]) << 3) | (tmpin[17*j +  6] >> 5);
			out[i][8*j + 3] = (((uint32_t) tmpin[17*j +  6]) << 12) | (((uint32_t) tmpin[17*j +  7]) << 4) | (tmpin[17*j +  8] >> 4);
			out[i][8*j + 4] = (((uint32_t) tmpin[17*j +  8]) << 13) | (((uint32_t) tmpin[17*j +  9]) << 5) | (tmpin[17*j + 10] >> 3);
			out[i][8*j + 5] = (((uint32_t) tmpin[17*j + 10]) << 14) | (((uint32_t) tmpin[17*j + 11]) << 6) | (tmpin[17*j + 12] >> 2);
			out[i][8*j + 6] = (((uint32_t) tmpin[17*j + 12]) << 15) | (((uint32_t) tmpin[17*j + 13]) << 7) | (tmpin[17*j + 14] >> 1);
			out[i][8*j + 7] = (((uint32_t) tmpin[17*j + 14]) << 16) | (((uint32_t) tmpin[17*j + 15]) << 8) | (tmpin[17*j + 16]);
		}

		for (int j = 0; j < _N; j++)
		{
			out[i][j] = (out[i][j] << 15) >> 15; 
		}
	}
#endif

#ifdef PARAM_3
	for (int i = 0; i < _M; i++)
	{
		tmpin = in + i * _hhhN * 19;

		for (int j = 0; j < _hhhN; j++)
		{
			out[i][8*j + 0] = (((uint32_t) tmpin[19*j +  0]) << 11) | (((uint32_t) tmpin[19*j +  1]) << 3) | (tmpin[19*j +  2] >> 5); 
			out[i][8*j + 1] = (((uint32_t) tmpin[19*j +  2]) << 14) | (((uint32_t) tmpin[19*j +  3]) << 6) | (tmpin[19*j +  4] >> 2);
			out[i][8*j + 2] = (((uint32_t) tmpin[19*j +  4]) << 17) | (((uint32_t) tmpin[19*j +  5]) << 9) | (tmpin[19*j +  6] << 1) | (tmpin[19*j +  7] >> 7);
			out[i][8*j + 3] = (((uint32_t) tmpin[19*j +  7]) << 12) | (((uint32_t) tmpin[19*j +  8]) << 4) | (tmpin[19*j +  9] >> 4);
			out[i][8*j + 4] = (((uint32_t) tmpin[19*j +  9]) << 15) | (((uint32_t) tmpin[19*j + 10]) << 7) | (tmpin[19*j + 11] >> 1);
			out[i][8*j + 5] = (((uint32_t) tmpin[19*j + 11]) << 18) | (((uint32_t) tmpin[19*j + 12]) <<10) | (tmpin[19*j + 13] << 2) | (tmpin[19*j +  14] >> 6);
			out[i][8*j + 6] = (((uint32_t) tmpin[19*j + 14]) << 13) | (((uint32_t) tmpin[19*j + 15]) << 5) | (tmpin[19*j + 16] >> 3);
			out[i][8*j + 7] = (((uint32_t) tmpin[19*j + 16]) << 16) | (((uint32_t) tmpin[19*j + 17]) << 8) | (tmpin[19*j + 18]);
		}

		for (int j = 0; j < _N; j++)
		{
			out[i][j] = (out[i][j] << 13) >> 13; 
		}
	}
#endif

}


void pack_polyvec(uint8_t* out, int32_t in[][_N])
{

	for (int i = 0; i < _K; i++)
		pack_poly(out + i * _log_P * _hhhN, in[i]);
}


void unpack_polyvec(int32_t out[][_N], uint8_t* in)
{
	for (int i = 0; i < _K; i++)
		unpack_poly(out[i], in + i * _log_P * _hhhN);

}

void pack_polyvec_s(uint8_t* out, int32_t in[][_N])
{

	for (int i = 0; i < _M; i++)
		pack_poly(out + i * _log_P * _hhhN, in[i]);
}


void unpack_polyvec_s(int32_t out[][_N], uint8_t* in)
{
	for (int i = 0; i < _M; i++)
		unpack_poly(out[i], in + i * _log_P * _hhhN);

}

