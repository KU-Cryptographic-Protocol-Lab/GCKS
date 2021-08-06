#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include "poly.h"

int sample_a(int64_t out[][_N], uint8_t* seed);
int sample_s(int64_t out[][_N], uint8_t* seed);
int sample_r(int64_t out[][_N], uint8_t* seed);
int sample_c(int64_t* out, uint8_t* in);

#endif