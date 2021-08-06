#include "poly.h"
#include "reduce.h"
#include "params.h"
#include "string.h"
#include "NIST/rng.h"

void mul_2(int64_t* c, int64_t* a, int64_t* b)
{
	c[0] = mont_mul(a[0], b[0]);
	c[1] = madd(mont_mul(a[0], b[1]), mont_mul(a[1], b[0]));
	c[2] = mont_mul(a[1], b[1]);
	c[3] = 0;
}

void mul_4(int64_t* c, int64_t* a, int64_t* b)
{
	memset(c, 0, 64);

	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			c[i + j] = madd(c[i + j], mont_mul(a[i], b[j]));
		}
	}
}

void mul_8(int64_t* c, int64_t* a, int64_t* b)
{
	memset(c, 0, 16 * 8);

	for (int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			c[i + j] = madd(c[i + j], mont_mul(a[i], b[j]));
		}
	}
}

void mul_16(int64_t* c, int64_t* a, int64_t* b)
{
	memset(c, 0, 32 * 8);

	for (int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			c[i + j] = madd(c[i + j], mont_mul(a[i], b[j]));
		}
	}
}

void mul_32(int64_t* c, int64_t* a, int64_t* b)
{
	memset(c, 0, 64 * 8);

	for (int i = 0; i < 32; i++)
	{
		for(int j = 0; j < 32; j++)
		{
			c[i + j] = madd(c[i + j], mont_mul(a[i], b[j]));
		}
	}
}

void mul_64(int64_t* c, int64_t* a, int64_t* b)
{
	memset(c, 0, 128 * 8);

	for (int i = 0; i < 64; i++)
	{
		for(int j = 0; j < 64; j++)
		{
			c[i + j] = madd(c[i + j], mont_mul(a[i], b[j]));
		}
	}
}

void mul_128(int64_t* c, int64_t* a, int64_t* b)
{
	memset(c, 0, 256 * 8);
	
	for (int i = 0; i < 128; i++)
	{
		for(int j = 0; j < 128; j++)
		{
			c[i + j] = madd(c[i + j], mont_mul(a[i], b[j]));
		}
	}
}

void mul_256(int64_t* c, int64_t* a, int64_t* b)
{
	memset(c, 0, 512 * 8);

	for (int i = 0; i < 256; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			c[i + j] = madd(c[i + j], mont_mul(a[i], b[j]));
		}
	}
}

void poly_cadd(int64_t* in)
{
	for (int i = 0; i < _N; i++)
	{
		in[i] = caddp(in[i]);
	}
}

void polyvec_cadd(int64_t in[][_N])
{
	for (int i = 0; i < _M; i++)
	{
		poly_cadd(in[i]);
	}
}

void karatsuba_4(int64_t* c, int64_t* a, int64_t* b)
{
	int64_t t0[2] = {0};
	int64_t t1[2] = {0};
	int64_t t2[4] = {0};

	c[0] = mont_mul(a[0], b[0]);
	c[2] = mont_mul(a[1], b[1]);
	c[1] = msub(mont_mul(a[0] + a[1], b[0] + b[1]), madd(c[0], c[2]));

	c[4] = mont_mul(a[2], b[2]);
	c[6] = mont_mul(a[3], b[3]);
	c[5] = msub(mont_mul(a[2] + a[3], b[2] + b[3]), madd(c[4], c[6]));
	c[7] = 0;

	t0[0] = a[0] + a[2];
	t0[1] = a[1] + a[3];
	t1[0] = b[0] + b[2];
	t1[1] = b[1] + b[3];	

	t2[0] = mont_mul(t0[0], t1[0]);
	t2[2] = mont_mul(t0[1], t1[1]);
	t2[1] = msub(mont_mul(t0[0] + t0[1], t1[0] + t1[1]), madd(t2[0], t2[2]));

	t2[0] = msub(t2[0], madd(c[0], c[4]));
	t2[1] = msub(t2[1], madd(c[1], c[5]));
	t2[2] = msub(t2[2], madd(c[2], c[6]));

	c[2] = madd(c[2], t2[0]);
	c[3] = t2[1];
	c[4] = madd(c[4], t2[2]);
}

void karatsuba_8(int64_t* c, int64_t* a, int64_t* b)
{
	int64_t t0[4] = {0};
	int64_t t1[4] = {0};
	int64_t t2[8] = {0};

	karatsuba_4(c + 0, a + 0, b + 0);
	karatsuba_4(c + 8, a + 4, b + 4);

	for (int i = 0; i < 4; i++)
	{
		t0[i] = a[i] + a[i + 4];
		t1[i] = b[i] + b[i + 4];
	}

	karatsuba_4(t2, t0, t1);	

	for (int i = 0; i < 8; i++)
	{
		t2[i] = msub(t2[i], madd(c[i], c[i + 8]));
	}

	for (int i = 0; i < 8; i++)
	{
		c[i + 4] = madd(c[i + 4], t2[i]);
	}	
}


void karatsuba_16(int64_t* c, int64_t* a, int64_t* b)
{
	int64_t t0[8] = {0};
	int64_t t1[8] = {0};
	int64_t t2[16] = {0};

	karatsuba_8(c +  0, a + 0, b + 0);
	karatsuba_8(c + 16, a + 8, b + 8);

	for (int i = 0; i < 8; i++)
	{
#ifdef PARAM_1
		t0[i] = a[i] + a[i + 8];
		t1[i] = b[i] + b[i + 8];
#endif
#ifdef PARAM_2
		t0[i] = madd(a[i], a[i + 8]);
		t1[i] = madd(b[i], b[i + 8]);
#endif
	}

	karatsuba_8(t2, t0, t1);	

	for (int i = 0; i < 16; i++)
	{
		t2[i] = msub(t2[i], madd(c[i], c[i + 16]));
	}

	for (int i = 0; i < 16; i++)
	{
		c[i + 8] = madd(c[i + 8], t2[i]);
	}
}

void karatsuba_32(int64_t* c, int64_t* a, int64_t* b)
{
	int64_t t0[16] = {0};
	int64_t t1[16] = {0};
	int64_t t2[32] = {0};

	karatsuba_16(c +  0, a +  0, b +  0);
	karatsuba_16(c + 32, a + 16, b + 16);

	for (int i = 0; i < 16; i++)
	{
#ifdef PARAM_1
		t0[i] = a[i] + a[i + 16];
		t1[i] = b[i] + b[i + 16];
#endif
#ifdef PARAM_2
		t0[i] = madd(a[i], a[i + 16]);
		t1[i] = madd(b[i], b[i + 16]);
#endif
	}

	karatsuba_16(t2, t0, t1);	

	for (int i = 0; i < 32; i++)
	{
		t2[i] = msub(t2[i], madd(c[i], c[i + 32]));
	}

	for (int i = 0; i < 32; i++)
	{
		c[i + 16] = madd(c[i + 16], t2[i]);
	}
}

void karatsuba_64(int64_t* c, int64_t* a, int64_t* b)
{
	int64_t t0[32] = {0};
	int64_t t1[32] = {0};
	int64_t t2[64] = {0};

	karatsuba_32(c +  0, a +  0, b +  0);
	karatsuba_32(c + 64, a + 32, b + 32);

	for (int i = 0; i < 32; i++)
	{
#ifdef PARAM_1
		t0[i] = a[i] + a[i + 32];
		t1[i] = b[i] + b[i + 32];
#endif
#ifdef PARAM_2
		t0[i] = madd(a[i], a[i + 32]);
		t1[i] = madd(b[i], b[i + 32]);
#endif
	}

	karatsuba_32(t2, t0, t1);	

	for (int i = 0; i < 64; i++)
	{
		t2[i] = msub(t2[i], madd(c[i], c[i + 64]));
	}

	for (int i = 0; i < 64; i++)
	{
		c[i + 32] = madd(c[i + 32], t2[i]);
	}
}

void toom_cook_eval_256(int64_t aw[][_hhN], int64_t* a)
{
	int64_t *a0, *a1, *a2, *a3;
	int64_t r0, r1, r2, r3, r4, r5, r6, r7;
	
	a0 = a;
	a1 = a0 + _hhN;
	a2 = a1 + _hhN;
	a3 = a2 + _hhN;

	for (int i = 0; i < _hhN; i++)
	{
		r0 = a0[i];
		r1 = a1[i];
		r2 = a2[i];
		r3 = a3[i];
		r4 = madd(r0, r2);
		r5 = madd(r1, r3);
		r6 = madd(r4, r5);
		r7 = msub(r4, r5);

		aw[2][i] = r6;
		aw[3][i] = r7;

		r4 = mont_mul((r0 << 2) + r2, _MONT_2);
		r5 = madd(mont_mul(r1, _MONT_4), r3);
		r6 = madd(r4, r5);
		r7 = msub(r4, r5);
		
		aw[4][i] = r6;
		aw[5][i] = r7;
		
		r4 = madd(mont_mul((((r3 << 1) + r2) << 1) + r1, _MONT_2), r0);

		aw[1][i] = r4;
		aw[6][i] = r0;
		aw[0][i] = r3;
	}	
}

void toom_cook_intp_256(int64_t* c, int64_t w[][_hN])
{
	int64_t r0, r1, r2, r3, r4, r5, r6, r7;

	memset(c, 0, 8 * 512);

	for (int i = 0; i < _hN - 1; i++) 
	{
		r0 = w[0][i];
		r1 = w[1][i];
		r2 = w[2][i];
		r3 = w[3][i];
		r4 = w[4][i];
		r5 = w[5][i];
		r6 = w[6][i];

		r1 = madd(r1, r4);
		r5 = msub(r5, r4);
		r3 = mont_mul(r3 + (_P - r2), _MONT_INV_2);
		r4 = mont_mul(r4 + (_P - r0) + (_P - mont_mul(r6, _MONT_64)), _MONT_2);
		r4 = madd(r4, r5);
		r2 = madd(r2, r3);
		r1 = msub(r1, mont_mul(r2, _MONT_65));
		r2 = msub(r2, r6);
		r2 = msub(r2, r0);
		r1 = madd(r1, mont_mul(_MONT_45, r2));
		r4 = mont_mul(r4 + (_P - mont_mul(r2, _MONT_8)), _MONT_INV_24);
		r5 = madd(r5, r1);
		r1 = mont_mul(r1 + mont_mul(r3, _MONT_16), _MONT_INV_18);
		r3 = csubp(_P - madd(r3, r1));
#ifdef PARAM_1		
		r5 = mont_mul(r1 * 30 + (_P - r5), _MONT_INV_60);
#endif
#ifdef PARAM_2
		r5 = mont_mul(mont_mul(_MONT_30, r1) + (_P - r5), _MONT_INV_60);
#endif
		r2 = msub(r2, r4);
		r1 = msub(r1, r5);

		c[i]           = madd(c[i], r6);
		c[i+_hhN]      = madd(c[i+_hhN], r5);
		c[i+_hN]       = madd(c[i+_hN], r4);
		c[i+_hN+_hhN]  = madd(c[i+_hN+_hhN], r3);
		c[i+_N]        = madd(c[i+_N], r2);
		c[i+_N + _hhN] = madd(c[i+_N + _hhN], r1);
		c[i+_N + _hN]  = madd(c[i+_N + _hN], r0);
	}	
}

void poly_print(int64_t* in)
{
	for (int i = 0; i < _N; i++)
	{
		printf("%20ld ", in[i]);
		if(i % 6 == 5) printf("\n");
	}
	printf("\n");

}

void poly_mont_cvt(int64_t* out, int64_t* in)
{
	for (int i = 0; i < _N; i++)
	{
		out[i] = mont_cvt(in[i]);
	}
}

void poly_mont_ivt(int64_t* out, int64_t* in)
{
	for (int i = 0; i < _N; ++i)
	{
		out[i] = mont_ivt(in[i]);
	}
}

void poly_init(int64_t* in)
{
	for (int i = 0; i < _N; i++)
	{
		in[i] = 0;
	}
}

void poly_add(int64_t* c, int64_t* a, int64_t* b)
{
	for(int i=0; i< _N; i++)
	{
		c[i] = madd(a[i], b[i]);
	}
}

void poly_sub(int64_t* c, int64_t* a, int64_t* b)
{
	for(int i=0; i< _N; i++)
	{
		c[i] = madd(a[i], _P - b[i]);
	}
}

void poly_mul(int64_t* c, int64_t* a, int64_t* b)
{
	int64_t aw[7][_hhN] = {0};
	int64_t bw[7][_hhN] = {0};
	int64_t  w[7][_hN] = {0};
	int64_t tmp[_N << 1] = {0};

	int64_t m_a[_N];
	int64_t m_b[_N];
	int64_t m_c[_N];

	poly_mont_cvt(m_a, a);
	toom_cook_eval_256(aw, m_a);

	poly_mont_cvt(m_b, b);
	toom_cook_eval_256(bw, m_b);
	
	karatsuba_64(w[0], aw[0], bw[0]); //infinity
	karatsuba_64(w[1], aw[1], bw[1]); // 2
	karatsuba_64(w[2], aw[2], bw[2]); // 1
	karatsuba_64(w[3], aw[3], bw[3]); // -1
	karatsuba_64(w[4], aw[4], bw[4]); // 1/2
	karatsuba_64(w[5], aw[5], bw[5]); // -1/2
	karatsuba_64(w[6], aw[6], bw[6]); // 0

	toom_cook_intp_256(tmp, w);
	
	for (int i = 0; i < _N; ++i)
	{
		m_c[i] = tmp[i] + (_P - tmp[i + _N]);
	}

	poly_mont_ivt(c, m_c);
}

void poly_polyvec_mul(int64_t c[][_N], int64_t* a, int64_t b[][_N])
{
	int64_t aw[7][_hhN] = {0};
	int64_t bw[7][_hhN] = {0};
	int64_t  w[7][_hN] = {0};
	int64_t tmp[_N << 1] = {0};

	int64_t m_a[_N];
	int64_t m_b[_N];
	int64_t m_c[_N];

	poly_mont_cvt(m_a, a);
	toom_cook_eval_256(aw, m_a);

	for (int i = 0; i < _M; i++)
	{
		poly_mont_cvt(m_b, b[i]);
		toom_cook_eval_256(bw, m_b);

		karatsuba_64(w[0], aw[0], bw[0]); //infinity
		karatsuba_64(w[1], aw[1], bw[1]); // 2
		karatsuba_64(w[2], aw[2], bw[2]); // 1
		karatsuba_64(w[3], aw[3], bw[3]); // -1
		karatsuba_64(w[4], aw[4], bw[4]); // 1/2
		karatsuba_64(w[5], aw[5], bw[5]); // -1/2
		karatsuba_64(w[6], aw[6], bw[6]); // 0

		toom_cook_intp_256(tmp, w);

		for (int j = 0; j < _N; j++)
		{
			m_c[j] = tmp[j] + (_P - tmp[j + _N]);
		}

		poly_mont_ivt(c[i], m_c);
	}
}

void polyvec_add(int64_t c[][_N], int64_t a[][_N], int64_t b[][_N])
{
	for(int i = 0; i < _M; i++)
	{
		poly_add(c[i], a[i], b[i]);
	}	
}

void polyvec_mul(int64_t* c, int64_t a[][_N], int64_t b[][_N])
{
	int64_t aw[7][_hhN] = {0};
	int64_t bw[7][_hhN] = {0};
	int64_t  w[7][_hN] = {0};
	int64_t  t[7][_hN] = {0};	
	int64_t tmp[_N << 1] = {0};

	int64_t m_a[_N];
	int64_t m_b[_N];
	int64_t m_c[_N];

	for(int i = 0; i < _M; i++)
	{
		memset(w, 0, 7*_hN);

		poly_mont_cvt(m_a, a[i]);
		toom_cook_eval_256(aw, m_a);

		poly_mont_cvt(m_b, b[i]);
		toom_cook_eval_256(bw, m_b);

		karatsuba_64(w[0], aw[0], bw[0]); //infinity	
		karatsuba_64(w[1], aw[1], bw[1]); // 2
		karatsuba_64(w[2], aw[2], bw[2]); // 1
		karatsuba_64(w[3], aw[3], bw[3]); // -1
		karatsuba_64(w[4], aw[4], bw[4]); // 1/2
		karatsuba_64(w[5], aw[5], bw[5]); // -1/2
		karatsuba_64(w[6], aw[6], bw[6]); // 0

		for (int j = 0; j < 7; j++)
		{
			for (int k = 0; k < _hN; k++)
			{
				t[j][k] = madd(t[j][k], w[j][k]);
			}
		}
	}

	toom_cook_intp_256(tmp, t);

	for (int i = 0; i < _N; i++)
	{
		m_c[i] = tmp[i] + (_P - tmp[i + _N]);
	}

	poly_mont_ivt(c, m_c);
}

int poly_reject_cs(int64_t in[][_N])
{
	int tmp1;
	int tmp2;

	int result = 1;

	for (int i = 0; i < _M; i++)
	{
		for (int j = 0; j < _N; j++)
		{
			 if(((_Bound1 - in[i][j]) & (in[i][j] - (_P - _Bound1))) >> 63) return 0;
		}
	}

	return 1;
}

int poly_reject_U(int64_t in[][_N])
{
	int tmp1;
	int tmp2;

	int result = 1;

	for (int i = 0; i < _M; i++)
	{
		for (int j = 0; j < _N; j++)
		{
			 if(((_Bound2 - in[i][j]) & (in[i][j] - (_P - _Bound2))) >> 63) return 0;
		}
	}

	for (int i = 0; i < _M; i++)
	{
		for (int j = 0; j < _N; j++)
		{
			 in[i][j] = center(in[i][j]);
		}
	}

	return 1;
}


