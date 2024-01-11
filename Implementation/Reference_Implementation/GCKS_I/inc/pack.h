#ifndef __PACK_H__
#define __PACK_H__

#include <stdint.h>
#include "poly.h"

void pack_poly(uint8_t* out, int32_t* in);
void pack_s(uint8_t* out, int32_t in[][_N]);
void pack_z(uint8_t* out, int32_t in[][_N]);

void unpack_poly(int32_t* out, uint8_t* in);
void unpack_s(int32_t out[][_N], uint8_t* in);
void unpack_z(int32_t out[][_N], uint8_t* in);

void pack_polyvec(uint8_t* out, int32_t in[][_N]);
void unpack_polyvec(int32_t out[][_N], uint8_t* in);
void pack_polyvec_s(uint8_t* out, int32_t in[][_N]);
void unpack_polyvec_s(int32_t out[][_N], uint8_t* in);

#endif