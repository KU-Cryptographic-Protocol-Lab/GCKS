#ifndef NTT_H
#define NTT_H

#include <stdint.h>
#include "params.h"

extern const int32_t zetas[8];

int32_t fqmul(int32_t a, int32_t b);
void ntt(int32_t* in);
void invntt(int32_t* in);
void basemul(int32_t r[32], const int32_t a[32], const int32_t b[32], int32_t zeta);

#endif