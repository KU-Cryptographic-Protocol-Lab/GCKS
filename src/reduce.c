#include "reduce.h"
#include "params.h"

int64_t caddp(int64_t in)
{
	in += (in >> 63) & _P;

	return in;
}

int64_t csubp(int64_t in)
{
	in -= _P;
	in += (in >> 63) & _P;
	
	return in;
}

int64_t center(int64_t in)
{
	int64_t _hP = (_P-1) >> 1;

	in -= _hP + 1;
	in += ((int64_t)in >> 63) & _P;
	in -= _hP;

	return in;
}

int64_t madd(int64_t a, int64_t b)
{
	return csubp(a + b);
}

int64_t msub(int64_t a, int64_t b)
{
	return csubp(a + (_P - b));
}

int64_t mont_cvt(int64_t in)
{
	__int128_t t = (__int128_t) in * _MONT_RSquare;

	return mont_ivt(t);
}

int64_t mont_ivt(__int128_t in)
{
	__int128_t m = (in * _MONT_mNInv) & 0xffffffffffffffff;
	__int128_t t = (in + (m * _MONT_N)) >> 64;

	return 	csubp((int64_t) t);
}

int64_t mont_mul(int64_t a, int64_t b)
{
	__int128_t t = (__int128_t)a * (__int128_t)b;

	return mont_ivt(t);
}