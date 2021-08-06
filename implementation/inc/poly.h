#ifndef __POLY_H__
#define __POLY_H__

#include "params.h"
#include <stdint.h>

#define POLY_BYTES ((_log_P * _N) >> 3)
#define POLYVEC_BYTES (POLY_BYTES * _M)

void poly_cadd(int64_t* in);
void polyvec_cadd(int64_t in[][_N]);

void poly_print(int64_t* in);
void poly_init(int64_t* in);
void poly_add(int64_t* c, int64_t* a, int64_t* b);
void poly_sub(int64_t* c, int64_t* a, int64_t* b);
void poly_mul(int64_t* c, int64_t* a, int64_t* b);
void poly_polyvec_mul(int64_t c[][_N], int64_t* a, int64_t b[][_N]);
void polyvec_add(int64_t c[][_N], int64_t a[][_N], int64_t b[][_N]);
void polyvec_mul(int64_t* c, int64_t a[][_N], int64_t b[][_N]);

int poly_reject_cs(int64_t in[][_N]);
int poly_reject_U(int64_t in[][_N]);
#endif