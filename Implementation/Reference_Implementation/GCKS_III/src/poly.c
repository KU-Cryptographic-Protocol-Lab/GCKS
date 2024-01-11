#include "poly.h"
#include "reduce.h"
#include "params.h"
#include "string.h"
#include "NIST/rng.h"
#include "ntt.h"
#include <stdio.h>
#include <stdint.h>



void poly_cadd(int32_t* in)
{
	for (int i = 0; i < _N; i++)
	{
		in[i] = caddp(in[i]);
	}
}

void polyvec_cadd(int32_t in[][_N])
{
	for (int i = 0; i < _M; i++)
	{
		poly_cadd(in[i]);
	}
}

void poly_init(int32_t* in)
{
	for (int i = 0; i < _N; i++)
	{
		in[i] = 0;
	}
}

void poly_add(int32_t* c, int32_t* a, int32_t* b)
{
	for(int i=0; i< _N; i++)
	{
		c[i] = madd(a[i], b[i]);
	}
}

void poly_sub(int32_t* c, int32_t* a, int32_t* b)
{
	for(int i=0; i< _N; i++)
	{
		c[i] = madd(a[i], Q - b[i]);
	}
}

void polyvec_add(int32_t c[][_N], int32_t a[][_N], int32_t b[][_N])
{
	for(int i = 0; i < _M; i++)
	{
		poly_add(c[i], a[i], b[i]);
	}	
}

void polyvec_sub(int32_t c[][_N], int32_t a[][_N], int32_t b[][_N])
{
	for(int i = 0; i < _K; i++)
	{
		poly_sub(c[i], a[i], b[i]);
	}	
}


int poly_reject_cs(int32_t in[][_N])
{
	int tmp1;
	int tmp2;

	int result = 1;

	for (int i = 0; i < _M; i++)
	{
		for (int j = 0; j < _N; j++)
		{
			 if(((_Bound1 - in[i][j]) & (in[i][j] - (Q - _Bound1))) >> 31) return 0;
		}
	}

	return 1;
}

int poly_reject_z(int32_t in[][_N])
{
	int tmp1;
	int tmp2;

	int result = 1;

	for (int i = 0; i < _M; i++)
	{
		for (int j = 0; j < _N; j++)
		{
			 if(((_Bound2 - in[i][j]) & (in[i][j] - (Q - _Bound2))) >> 31) return 0;
			 	
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

/*************************************************
* Name:        poly_basemul
*
* Description: Multiplication of two polynomials in NTT domain
*
* Arguments:   - poly *r:       pointer to output polynomial
*              - const poly *a: pointer to first input polynomial
*              - const poly *b: pointer to second input polynomial
**************************************************/
void poly_basemul(int32_t* c, int32_t* a, int32_t* b)
{
	for(int i = 0; i < 4; i++)
	{
		basemul(c + 64*i,      a + 64*i,      b + 64*i,       zetas[4 + i]);
		basemul(c + 64*i + 32, a + 64*i + 32, b + 64*i + 32, -zetas[4 + i]);
	}
}

void polymat_mul(int32_t c[][_N], int32_t a[][_M][_N], int32_t b[_M][_N])
{
	for(int i = 0; i < _K; i++)
		polyvec_mul(c[i],a[i],b);
}


#ifdef PARAM_1
void polyvec_mul(int32_t* c, int32_t a[][_N], int32_t b[][_N])
{
   int32_t t[64];
   int32_t aw[7][8] = {0};
   int32_t bw[7][8] = {0};
   int32_t  w[7][16] = {0};
   int32_t  w2[7][16] = {0};

   for (int i = 0; i < 4; i++)
   {
      memset(w2,0,112<<2);

      for (int j = 0; j < _M; j++)
      {
         memset(w,0,112<<2);

         toom_cook_eval_32(aw, a[j] + 64*i);
         toom_cook_eval_32(bw, b[j] + 64*i);
         
         karatsuba_simple_8(w[0], aw[0], bw[0]); //infinity
         karatsuba_simple_8(w[1], aw[1], bw[1]); // 2
         karatsuba_simple_8(w[2], aw[2], bw[2]); // 1
         karatsuba_simple_8(w[3], aw[3], bw[3]); // -1
         karatsuba_simple_8(w[4], aw[4], bw[4]); // 1/2
         karatsuba_simple_8(w[5], aw[5], bw[5]); // -1/2
         karatsuba_simple_8(w[6], aw[6], bw[6]); // 0

         for (int k = 0; k < 112; k++)
         {
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k] + Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] % Q;
            ((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k];
         }
      }

      memset(t,0,64<<2);
      toom_cook_intp_32(t, w2);

      for (int k = 0; k < 32; k++)
      {
         c[64*i + k] = barrett_reduce(t[k] + fqmul(t[k+32],zetas[4 + i]));      
         //c[64*i + k] = (c[64*i + k] + Q) % Q;
      }

      memset(w2,0,112<<2);

      for (int j = 0; j < _M; j++)
      {
         memset(w,0,112<<2);

         toom_cook_eval_32(aw, a[j] + 64*i + 32);
         toom_cook_eval_32(bw, b[j] + 64*i + 32);
         
         karatsuba_simple_8(w[0], aw[0], bw[0]); //infinity
         karatsuba_simple_8(w[1], aw[1], bw[1]); // 2
         karatsuba_simple_8(w[2], aw[2], bw[2]); // 1
         karatsuba_simple_8(w[3], aw[3], bw[3]); // -1
         karatsuba_simple_8(w[4], aw[4], bw[4]); // 1/2
         karatsuba_simple_8(w[5], aw[5], bw[5]); // -1/2
         karatsuba_simple_8(w[6], aw[6], bw[6]); // 0

         for (int k = 0; k < 112; k++)
         {
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k] + Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] % Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k];            
            ((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k];            
         }
      }
   
      memset(t,0,64<<2);
      toom_cook_intp_32(t, w2);

      for (int k = 0; k < 32; k++)
      {
         t[k] = barrett_reduce(t[k] + fqmul(t[k+32],-zetas[4 + i]));      
         //c[64*i + k + 32] = (c[64*i + k + 32] + t[k]) % Q;
         c[64*i + k + 32] = (c[64*i + k + 32] + t[k]);
      }
   }
}
#endif

#ifdef PARAM_2
void polyvec_mul(int32_t* c, int32_t a[][_N], int32_t b[][_N])
{
   int32_t t[64];
   int32_t aw[7][8] = {0};
   int32_t bw[7][8] = {0};
   int32_t  w[7][16] = {0};
   int32_t  w2[7][16] = {0};

   for (int i = 0; i < 4; i++)
   {
      memset(w2,0,112<<2);

      for (int j = 0; j < _M; j++)
      {
         memset(w,0,112<<2);

         toom_cook_eval_32(aw, a[j] + 64*i);
         toom_cook_eval_32(bw, b[j] + 64*i);
         
         karatsuba_simple_8(w[0], aw[0], bw[0]); //infinity
         karatsuba_simple_8(w[1], aw[1], bw[1]); // 2
         karatsuba_simple_8(w[2], aw[2], bw[2]); // 1
         karatsuba_simple_8(w[3], aw[3], bw[3]); // -1
         karatsuba_simple_8(w[4], aw[4], bw[4]); // 1/2
         karatsuba_simple_8(w[5], aw[5], bw[5]); // -1/2
         karatsuba_simple_8(w[6], aw[6], bw[6]); // 0

         for (int k = 0; k < 112; k++)
         {
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k] + Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] % Q;
            ((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k];
         }
      }

      memset(t,0,64<<2);
      toom_cook_intp_32(t, w2);

      for (int k = 0; k < 32; k++)
      {
         c[64*i + k] = barrett_reduce(t[k] + fqmul(t[k+32],zetas[4 + i]));      
         //c[64*i + k] = (c[64*i + k] + Q) % Q;
      }

      memset(w2,0,112<<2);

      for (int j = 0; j < _M; j++)
      {
         memset(w,0,112<<2);

         toom_cook_eval_32(aw, a[j] + 64*i + 32);
         toom_cook_eval_32(bw, b[j] + 64*i + 32);
         
         karatsuba_simple_8(w[0], aw[0], bw[0]); //infinity
         karatsuba_simple_8(w[1], aw[1], bw[1]); // 2
         karatsuba_simple_8(w[2], aw[2], bw[2]); // 1
         karatsuba_simple_8(w[3], aw[3], bw[3]); // -1
         karatsuba_simple_8(w[4], aw[4], bw[4]); // 1/2
         karatsuba_simple_8(w[5], aw[5], bw[5]); // -1/2
         karatsuba_simple_8(w[6], aw[6], bw[6]); // 0

         for (int k = 0; k < 112; k++)
         {
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k] + Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] % Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k];            
            ((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k];            
         }
      }
   
      memset(t,0,64<<2);
      toom_cook_intp_32(t, w2);

      for (int k = 0; k < 32; k++)
      {
         t[k] = barrett_reduce(t[k] + fqmul(t[k+32],-zetas[4 + i]));      
         //c[64*i + k + 32] = (c[64*i + k + 32] + t[k]) % Q;
         c[64*i + k + 32] = (c[64*i + k + 32] + t[k]);
      }
   }
}
#endif

#ifdef PARAM_3
void polyvec_mul(int32_t* c, int32_t a[][_N], int32_t b[][_N])
{
   int32_t t[64];
   int32_t aw[7][8] = {0};
   int32_t bw[7][8] = {0};
   int32_t  w[7][16] = {0};
   int32_t  w2[7][16] = {0};

   for (int i = 0; i < 4; i++)
   {
      memset(w2,0,112<<2);

      for (int j = 0; j < _M; j++)
      {
         memset(w,0,112<<2);

         toom_cook_eval_32(aw, a[j] + 64*i);
         toom_cook_eval_32(bw, b[j] + 64*i);
         
         karatsuba_simple_8(w[0], aw[0], bw[0]); //infinity
         karatsuba_simple_8(w[1], aw[1], bw[1]); // 2
         karatsuba_simple_8(w[2], aw[2], bw[2]); // 1
         karatsuba_simple_8(w[3], aw[3], bw[3]); // -1
         karatsuba_simple_8(w[4], aw[4], bw[4]); // 1/2
         karatsuba_simple_8(w[5], aw[5], bw[5]); // -1/2
         karatsuba_simple_8(w[6], aw[6], bw[6]); // 0

         for (int k = 0; k < 112; k++)
         {
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k] + Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] % Q;
            ((int32_t*)w2)[k] = barrett_reduce(((int32_t*)w2)[k] + ((int32_t*)w)[k]);
         }
      }

      memset(t,0,64<<2);
      toom_cook_intp_32(t, w2);

      for (int k = 0; k < 32; k++)
      {
         c[64*i + k] = barrett_reduce(t[k] + fqmul(t[k+32],zetas[4 + i]));      
         //c[64*i + k] = (c[64*i + k] + Q) % Q;
      }

      memset(w2,0,112<<2);

      for (int j = 0; j < _M; j++)
      {
         memset(w,0,112<<2);

         toom_cook_eval_32(aw, a[j] + 64*i + 32);
         toom_cook_eval_32(bw, b[j] + 64*i + 32);
         
         karatsuba_simple_8(w[0], aw[0], bw[0]); //infinity
         karatsuba_simple_8(w[1], aw[1], bw[1]); // 2
         karatsuba_simple_8(w[2], aw[2], bw[2]); // 1
         karatsuba_simple_8(w[3], aw[3], bw[3]); // -1
         karatsuba_simple_8(w[4], aw[4], bw[4]); // 1/2
         karatsuba_simple_8(w[5], aw[5], bw[5]); // -1/2
         karatsuba_simple_8(w[6], aw[6], bw[6]); // 0

         for (int k = 0; k < 112; k++)
         {
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k] + Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] % Q;
            //((int32_t*)w2)[k] = ((int32_t*)w2)[k] + ((int32_t*)w)[k];            
            ((int32_t*)w2)[k] = barrett_reduce(((int32_t*)w2)[k] + ((int32_t*)w)[k]);            
         }
      }
   
      memset(t,0,64<<2);
      toom_cook_intp_32(t, w2);

      for (int k = 0; k < 32; k++)
      {
         t[k] = barrett_reduce(t[k] + fqmul(t[k+32],-zetas[4 + i]));      
         //c[64*i + k + 32] = (c[64*i + k + 32] + t[k]) % Q;
         c[64*i + k + 32] = barrett_reduce((c[64*i + k + 32] + t[k]));
      }
   }
}
#endif

void karatsuba_simple_8(int32_t* c, const int32_t* a, const int32_t* b)
{
    int32_t t0[3] = {0};
    int32_t t1[3] = {0};
    int32_t t2[3] = {0};
    int32_t s[7] = {0};

    int32_t i, j;
	
    int32_t acc1, acc2, acc3, acc4, acc5, acc6, acc7, acc8, acc9, acc10;

    for (i = 0; i < 2; i++) 
	{
        acc1 = a[i]; //a0
        acc2 = a[i + 2]; //a1
        acc3 = a[i + 4]; //a2
        acc4 = a[i + 6]; //a3

        for (j = 0; j < 2; j++) 
		{
            acc5 = b[j    ]; //b0
            acc6 = b[j + 2]; //b1

            c[i + j     ] += fqmul(acc1, acc5);
            c[i + j + 4] += fqmul(acc2, acc6);

            acc7 = acc5 + acc6; //b01
            acc8 = acc1 + acc2; //a01
            t0[i + j] += fqmul(acc7, acc8);

            acc7 = b[j + 4]; //b2
            acc8 = b[j + 6]; //b3
            c[i + j + 8] += fqmul(acc7, acc3);
            c[i + j + 12] += fqmul(acc8, acc4);

            acc9  = acc3 + acc4;
            acc10 = acc7 + acc8;
            t2[i + j] += fqmul(acc9, acc10);

            acc5 = acc5 + acc7; //b02
            acc7 = acc1 + acc3; //a02
            s[i + j] += fqmul(acc5, acc7);

            acc6 = acc6 + acc8; //b13
            acc8 = acc2 + acc4;
            s[i + j + 4] += fqmul(acc6, acc8);

            acc5 = acc5 + acc6;
            acc7 = acc7 + acc8;
            t1[i + j] += fqmul(acc5, acc7);
        }
    }

    // 2nd last stage
    for (i = 0; i < 3; i++) {
        t1[i] -= s[i] + s[i + 4];
        t0[i] -= c[i] + c[i + 4];
        t2[i] -= c[i + 8] + c[i + 12];
    }

    for (i = 0; i < 3; i++)
	{
        s[i + 2] += t1[i];
        c[i + 2] += t0[i];
        c[i + 10] += t2[i];
    }

    // Last stage
    for (i = 0; i < 7; i++) {
        s[i] = barrett_reduce(s[i] - c[i] - c[i + 8]);
    }

    for (i = 0; i < 7; i++) {
        c[i + 4] = barrett_reduce(c[i + 4] + s[i]);
    }
}


void karatsuba_simple_16(int32_t* c, const int32_t* a, const int32_t* b)
{
    int32_t t0[7] = {0};
    int32_t t1[7] = {0};
    int32_t t2[7] = {0};
    int32_t s[15] = {0};

    int32_t i, j;
	
    int32_t acc1, acc2, acc3, acc4, acc5, acc6, acc7, acc8, acc9, acc10;

    for (i = 0; i < 4; i++) 
	{
        acc1 = a[i]; //a0
        acc2 = a[i + 4]; //a1
        acc3 = a[i + 8]; //a2
        acc4 = a[i + 12]; //a3

        for (j = 0; j < 4; j++) 
		{
            acc5 = b[j    ]; //b0
            acc6 = b[j + 4]; //b1

            c[i + j     ] += fqmul(acc1, acc5);
            c[i + j + 8] += fqmul(acc2, acc6);

            acc7 = acc5 + acc6; //b01
            acc8 = acc1 + acc2; //a01
            t0[i + j] += fqmul(acc7, acc8);

            acc7 = b[j + 8]; //b2
            acc8 = b[j + 12]; //b3
            c[i + j + 16] += fqmul(acc7, acc3);
            c[i + j + 24] += fqmul(acc8, acc4);

            acc9  = acc3 + acc4;
            acc10 = acc7 + acc8;
            t2[i + j] += fqmul(acc9, acc10);

            acc5 = acc5 + acc7; //b02
            acc7 = acc1 + acc3; //a02
            s[i + j] += fqmul(acc5, acc7);

            acc6 = acc6 + acc8; //b13
            acc8 = acc2 + acc4;
            s[i + j + 8] += fqmul(acc6, acc8);

            acc5 = acc5 + acc6;
            acc7 = acc7 + acc8;
            t1[i + j] += fqmul(acc5, acc7);
        }
    }

    // 2nd last stage
    for (i = 0; i < 7; i++) {
        t1[i] -= s[i] + s[i + 8];
        t0[i] -= c[i] + c[i + 8];
        t2[i] -= c[i + 16] + c[i + 24];
    }

    for (i = 0; i < 7; i++)
	{
        s[i + 4] += t1[i];
        c[i + 4] += t0[i];
        c[i + 20] += t2[i];
    }

    // Last stage
    for (i = 0; i < 15; i++) {
        s[i] = barrett_reduce(s[i] - c[i] - c[i + 16]);
    }

    for (i = 0; i < 15; i++) {
        c[i + 8] = barrett_reduce(c[i + 8] + s[i]);
    }
}

void karatsuba_32(int32_t* c, const int32_t* a, const int32_t* b)
{
	int32_t t0[16] = {0};
	int32_t t1[16] = {0};
	int32_t t2[32] = {0};

	karatsuba_simple_16(c +  0, a +  0, b +  0);
	karatsuba_simple_16(c + 32, a + 16, b + 16);

	for (int i = 0; i < 16; i++)
	{
		t0[i] = a[i] + a[i + 16];
		t1[i] = b[i] + b[i + 16];
	}

	karatsuba_simple_16(t2, t0, t1);	

	for (int i = 0; i < 32; i++)
	{
		t2[i] = barrett_reduce(t2[i] - (c[i] + c[i + 32]));
	}

	for (int i = 0; i < 32; i++)
	{
		c[i + 16] = barrett_reduce(c[i + 16] + t2[i]);
	}
}




void toom_cook_eval_32(int32_t aw[][8], const int32_t* a)
{
   const int32_t *a0, *a1, *a2, *a3;
   int32_t r0, r1, r2, r3, r4, r5, r6, r7;
   
   a0 = a;
   a1 = a0 + 8;
   a2 = a1 + 8;
   a3 = a2 + 8;

   for (int i = 0; i < 8; i++)
   {
      r0 = a0[i];
      r1 = a1[i];
      r2 = a2[i];
      r3 = a3[i];
      r4 = r0 + r2;
      r5 = r1 + r3;
      r6 = r4 + r5;
      r7 = r4 - r5;

      aw[2][i] = r6;
      aw[3][i] = r7;

      r4 = fqmul((r0 << 2) + r2, _MONT_2);
      r5 = fqmul(r1, _MONT_4) + r3;
      r6 = r4 + r5;
      r7 = r4 - r5;
      
      aw[4][i] = r6;
      aw[5][i] = r7;
      
      r4 = fqmul((((r3 << 1) + r2) << 1) + r1, _MONT_2) + r0;

      aw[1][i] = r4;
      aw[6][i] = r0;
      aw[0][i] = r3;
   }   
}


void toom_cook_intp_32(int32_t* c, int32_t w[][16])
{
   int32_t r0, r1, r2, r3, r4, r5, r6;

   for (int i = 0; i < 16 - 1; i++) 
   {
      r0 = w[0][i];
      r1 = w[1][i];
      r2 = w[2][i];
      r3 = w[3][i];
      r4 = w[4][i];
      r5 = w[5][i];
      r6 = w[6][i];

      r1 = r1 + r4;
      r5 = r5 - r4;
      r3 = fqmul(r3 + (Q - r2), _MONT_INV_2);
      r4 = fqmul(r4 + (Q - r0) + (Q - fqmul(r6, _MONT_64)), _MONT_2);
      r4 = r4 + r5;
      r2 = r2 + r3;
      r1 = r1 - fqmul(r2, _MONT_65);
      r2 = r2 - r6;
      r2 = r2 - r0;
      r1 = r1 + fqmul(_MONT_45, r2);
      r4 = fqmul(r4 + (Q - fqmul(r2, _MONT_8)), _MONT_INV_24);
      r5 = r5 + r1;
      r1 = fqmul(r1 + fqmul(r3, _MONT_16), _MONT_INV_18);
      r3 = -(r3 + r1);
      r5 = fqmul(fqmul(_MONT_30, r1) + (Q - r5), _MONT_INV_60);

      r2 = r2 - r4;
      r1 = r1 - r5;

      c[i     ] = c[i    ] + r6;
      c[i +  8] = c[i + 8] + r5;
      c[i + 16] = c[i + 16] + r4;
      c[i + 24] = c[i + 24] + r3;
      c[i + 32] = c[i + 32] + r2;
      c[i + 40] = c[i + 40] + r1;
      c[i + 48] = c[i + 48] + r0;
   }   
}

void toom_cook_32(int32_t* c, const int32_t* a, const int32_t* b)
{
	int32_t aw[7][8] = {0};
	int32_t bw[7][8] = {0};
	int32_t  w[7][16] = {0};

	toom_cook_eval_32(aw, a);
	toom_cook_eval_32(bw, b);
	
	karatsuba_simple_8(w[0], aw[0], bw[0]); //infinity
	karatsuba_simple_8(w[1], aw[1], bw[1]); // 2
	karatsuba_simple_8(w[2], aw[2], bw[2]); // 1
	karatsuba_simple_8(w[3], aw[3], bw[3]); // -1
	karatsuba_simple_8(w[4], aw[4], bw[4]); // 1/2
	karatsuba_simple_8(w[5], aw[5], bw[5]); // -1/2
	karatsuba_simple_8(w[6], aw[6], bw[6]); // 0

	toom_cook_intp_32(c, w);
}