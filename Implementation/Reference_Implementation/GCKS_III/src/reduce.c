#include "reduce.h"
#include "params.h"

int32_t caddp(int32_t in) // c sampling -> + Q
{
	in += (in >> 31) & Q;

	return in;
}

int32_t csubp(int32_t in)
{
	
	in -= Q;
	in += (in >> 31) & Q;
	
	return in;
}

int32_t center(int32_t in)
{
	int32_t _hP = (Q-1) >> 1;

	in -= _hP + 1;
	in += ((int32_t)in >> 31) & Q;
	in -= _hP;

	return in;
}

int32_t madd(int32_t a, int32_t b)
{
	return csubp(a + b);
}

int32_t msub(int32_t a, int32_t b)
{
	return csubp(a + (Q - b));
}

/*************************************************
* Name:        montgomery_reduce
*
* Description: Montgomery reduction; given a 32-bit integer a, computes
*              16-bit integer congruent to a * R^-1 mod q, where R=2^16
*
* Arguments:   - int32_t a: input integer to be reduced;
*                           has to be in {-q2^15,...,q2^15-1}
*
* Returns:     integer in {-q+1,...,q-1} congruent to a * R^-1 modulo q.
**************************************************/
int32_t montgomery_reduce(int64_t a)
{
  int32_t t;

  t = (int64_t)(int32_t)a*QINV;
  t = (a - (int64_t)t*Q) >> 32;
  return t;
}

/*************************************************
* Name:        barrett_reduce
*
* Description: Barrett reduction; given a 16-bit integer a, computes
*              centered representative congruent to a mod q in {-(q-1)/2,...,(q-1)/2}
*
* Arguments:   - int16_t a: input integer to be reduced
*
* Returns:     integer in {-(q-1)/2,...,(q-1)/2} congruent to a modulo q.
**************************************************/

/*int32_t barrett_reduce(int32_t a)
{
  return a % Q;
}*/
#ifdef PARAM_1

int32_t barrett_reduce(int32_t a)
{
  int32_t t;

  t = (a + (1 << 24)) >> 25;
  t = a - t*Q;
  return t;
}

#endif

#ifdef PARAM_2

int32_t barrett_reduce(int32_t a)
{
  int32_t t;

  t = (a + (1 << 25)) >> 26;
  t = a - t*Q;
  return t;
}

#endif

#ifdef PARAM_3

int32_t barrett_reduce(int32_t a)
{
  int32_t t;
  //t = (a + (1 << 25)) >> 26;
  t = (a + (1 << 26)) >> 27;
  t = a - t*Q;
  return t;
	//return a % Q;
}

#endif