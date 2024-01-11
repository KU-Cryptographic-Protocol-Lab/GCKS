#include "params.h"
#include "reduce.h"
#include "ntt.h"

#ifdef PARAM_1
const int32_t zetas[8] = {
       59264,  1014600,  2502850,  5952122,
    3962317, -6936790, -5441109,  1127519};

#endif

#ifdef PARAM_2
const int32_t zetas[8] = {
	     7104,  -5531502,  14477659,  32074643,
	 27030963, -15818498, -12691170,    959850};
#endif

#ifdef PARAM_3
const int32_t zetas[8] = {
         2528,  31537333, -34170946, -36058205,
    16705881,  42593276,  38686637, -17668812};
#endif


/*************************************************
* Name:        fqmul
*
* Description: Multiplication followed by Montgomery reduction
*
* Arguments:   - int32_t a: first factor
*              - int32_t b: second factor
*
* Returns 16-bit integer congruent to a*b*R^{-1} mod q
**************************************************/
//static int32_t fqmul(int32_t a, int32_t b)
int32_t fqmul(int32_t a, int32_t b)
{
  return montgomery_reduce((int64_t)a*b);
}


/*void ntt(int32_t* in)
{
	int32_t t;
	int32_t zeta;
	int k = 1;

	for(int i = 0; i < _N; i++)
	{
		in[i] = fqmul(in[i],-16641937);
	}

	for(int step = _N/2; step >= 32; step >>= 1)
	{
		for(int start = 0; start < _N; start += (step << 1))
		{
			zeta = zetas[k++];

			for(int i = start; i < start + step; i++)
			{
				t = fqmul(zeta, in[i + step]);
				
				in[i + step] = barrett_reduce(in[i] - t);
				in[i       ] = barrett_reduce(in[i] + t);
			}
		}
	}
}*/

/*************************************************
* Name:        ntt
*
* Description: Inplace number-theoretic transform (NTT) in Rq.
*              input is in standard order, output is in bitreversed order
*
* Arguments:   - int32_t r[512]: pointer to input/output vector of elements of Zq
**************************************************/
void ntt(int32_t* in)
{
   int32_t t;
   int32_t zeta;
   int k = 1;

   for(int i = 0; i < _N; i++)
   {
      in[i] = fqmul(in[i],_MONT_2_32);
   }

   for(int step = _N/2; step >= 32; step >>= 1)
   {
      for(int start = 0; start < _N; start += (step << 1))
      {
         zeta = zetas[k++];

         for(int i = start; i < start + step; i++)
         {
            t = fqmul(zeta, in[i + step]);
            
            in[i + step] = barrett_reduce(in[i] - t);
            in[i       ] = barrett_reduce(in[i] + t);
         }
      }
   }
}


/*void invntt(int32_t* in)
{
	int32_t t;
	int32_t zeta;
	int k = 7;

	for(int step = 32; step <= _N/2; step <<= 1)	
	{
		for(int start = 0; start < _N; start += (step << 1))
		{
			zeta = zetas[k--];

			for(int i = start; i < start + step; i++)
			{
				t = in[i + step];

				in[i + step] = fqmul(zeta,  t - in[i]);
				in[i       ] = barrett_reduce(in[i] + t);
			}
		}
	}

	for(int i = 0; i < _N; i++)
	{
		//r[i] = fqmul(888, r[i]);
		//r[i] = fqmul(1, r[i]);
		in[i] = fqmul(-8388594, in[i]);	
	}
}*/

/*************************************************
* Name:        invntt
*
* Description: inverse number-theoretic transform in Rq and
*              multiplication by Montgomery factor R = 2^16.
*
* Arguments:   - int32_t b[GCKS_N]: pointer to output vector of elements of Zq
*              - int32_t a[GCKS_N]: pointer to input vector of elements of Zq
**************************************************/
void invntt(int32_t* in)
{
   int32_t t;
   int32_t zeta;
   int k = 7;

   for(int step = 32; step <= _N/2; step <<= 1)   
   {
      for(int start = 0; start < _N; start += (step << 1))
      {
         zeta = zetas[k--];

         for(int i = start; i < start + step; i++)
         {
            t = in[i + step];

            in[i + step] = fqmul(zeta,  t - in[i]);
            in[i       ] = barrett_reduce(in[i] + t);
         }
      }
   }

   for(int i = 0; i < _N; i++)
   {
      //r[i] = fqmul(7408, r[i]);
      //r[i] = fqmul(1, r[i]);
      in[i] = fqmul(_INV_2_3, in[i]);   
   }
}

/*
static void karatsuba_simple_16(int32_t* c, const int32_t* a, const int32_t* b)
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

static void karatsuba_32(int32_t* c, const int32_t* a, const int32_t* b)
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
}*/

/*************************************************
* Name:        basemul
*
* Description: Multiplication of polynomials in Zq[X]/(X^2-zeta)
*              used for multiplication of elements in Rq in NTT domain
*
* Arguments:   - int32_t c[2]: pointer to the output polynomial
*              - const int32_t a[2]: pointer to the first factor
*              - const int32_t b[2]: pointer to the second factor
*              - int32_t zeta: integer defining the reduction polynomial
**************************************************/
void basemul(int32_t c[32], const int32_t a[32], const int32_t b[32], int32_t zeta)
{
	int32_t tmp[64] = {0};

	karatsuba_32(tmp, a, b);
	//toom_cook_32(tmp, a, b);

	for (int i = 0; i < 32; i++)
	{
		c[i] = barrett_reduce(tmp[i] + fqmul(tmp[i+32],zeta));		
	}
}


