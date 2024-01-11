#ifndef __REDUCE_H_
#define __REDUCE_H_

#include "params.h"
#include <stdint.h>
#include "poly.h"

int32_t caddp(int32_t in);
int32_t csubp(int32_t in);
int32_t center(int32_t in);
int32_t madd(int32_t a, int32_t b);
int32_t msub(int32_t a, int32_t b);
/*
int64_t mont_cvt(int64_t a);
int64_t mont_ivt(__int128_t t);
int64_t mont_mul(int64_t a, int64_t b);
*/
int32_t csubp2(int32_t in);
int32_t mont_cvt2(int32_t a);
int32_t mont_ivt2(__int128_t t);
int32_t mont_mul2(int32_t a, int32_t b);

int32_t montgomery_reduce(int64_t a);
int32_t barrett_reduce(int32_t a);

#endif