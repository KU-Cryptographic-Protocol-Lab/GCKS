#ifndef __POLY_H__
#define __POLY_H__

#include "params.h"
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>

#define POLY_BYTES ((_log_P * _N) >> 3)
#define POLYVEC_BYTES (POLY_BYTES * _K)

/*void comput_w();
void ntt(int64_t* in);
void invntt(int64_t* in);

int32_t mont_cvt(int32_t in);
int32_t mont_mul(int32_t a, int32_t b);
int32_t mont_ivt(int64_t in);
void poly_mul_NTT(int32_t* c, int32_t* a, int32_t* b);

void poly_mul_NTT_wocvt(int32_t* c, int32_t* a, int32_t* b);
void polyvec_mul_NTT_wocvt(int32_t* c, int32_t a[][_N], int32_t b[][_N]);*/


void poly_cadd(int32_t* in);
void polyvec_cadd(int32_t in[][_N]);

void poly_init(int32_t* in);
void poly_add(int32_t* c, int32_t* a, int32_t* b);
void poly_sub(int32_t* c, int32_t* a, int32_t* b);
void polyvec_add(int32_t c[][_N], int32_t a[][_N], int32_t b[][_N]);
void polyvec_mul(int32_t* c, int32_t a[][_N], int32_t b[][_N]);
void polyvec_sub(int32_t c[][_N], int32_t a[][_N], int32_t b[][_N]);

int poly_reject_cs(int32_t in[][_N]);
int poly_reject_z(int32_t in[][_N]);

void schoolbook_poly_mul(int32_t* c, int32_t* a, int32_t* b);
void schoolbook_polyvec_mul(int32_t* c, int32_t a[][_N], int32_t b[][_N]);
void schoolbook_polymat_mul(int32_t c[][_N], int32_t a[][_M][_N], int32_t b[_M][_N]);

void poly_basemul(int32_t* c, int32_t* a, int32_t* b);
void polyvec_mul(int32_t* c, int32_t a[][_N], int32_t b[][_N]);

void polymat_mul(int32_t c[][_N], int32_t a[][_M][_N], int32_t b[_M][_N]);

void polyvec_mul2(int32_t* c, int32_t a[][_N], int32_t b[][_N]);
void polymat_mul2(int32_t c[][_N], int32_t a[][_M][_N], int32_t b[_M][_N]);

void karatsuba_simple_8(int32_t* c, const int32_t* a, const int32_t* b);
void karatsuba_simple_16(int32_t* c, const int32_t* a, const int32_t* b);
void karatsuba_32(int32_t* c, const int32_t* a, const int32_t* b);
void toom_cook_eval_32(int32_t aw[][8], const int32_t* a);
void toom_cook_intp_32(int32_t* c, int32_t w[][16]);
void toom_cook_32(int32_t* c, const int32_t* a, const int32_t* b);
void basemul(int32_t c[32], const int32_t a[32], const int32_t b[32], int32_t zeta);
#endif