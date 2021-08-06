#ifndef __PARAMS_H__
#define __PARAMS_H__

#define PARAM_2

#ifdef PARAM_1
	#define _P 18014398509481853 // 2^54 - 131
	#define _log_P 54
	#define _H 39
	#define _MONT_Rmod 134144
	#define _MONT_RSquare 17994612736
	#define _MONT_mNInv 15143508450837286443U
	#define _MONT_2  268288
	#define _MONT_4  536576
	#define _MONT_8  1073152
	#define _MONT_16 2146304
	#define _MONT_30 4024320
	#define _MONT_32 4292608
	#define _MONT_45 6036480
	#define _MONT_64 8585216
	#define _MONT_65 8719360
	#define _MONT_INV_2  67072
	#define _MONT_INV_18 2001599834394325
	#define _MONT_INV_24 6004799503166207
	#define _MONT_INV_60 9607679205059224

	#define _B ((1 << 14) -1)
	#define _log_B 14
#endif

#ifdef PARAM_2
	#define _P 1152921504606846869 // 2^60 - 173
	#define _log_P 60
	#define _H 45
	#define _MONT_Rmod 1712 // mont_1
	#define _MONT_RSquare 2930944 //mont_r
	#define _MONT_mNInv 549523333971487811U
	#define _MONT_2  3424
	#define _MONT_4  6848
	#define _MONT_8  13696
	#define _MONT_16 27392
	#define _MONT_30 51360
	#define _MONT_32 54784
	#define _MONT_45 77040
	#define _MONT_64 109568
	#define _MONT_65 111280
	#define _MONT_INV_2  856
	#define _MONT_INV_18 512409557603043148
	#define _MONT_INV_24 384307168202282361
	#define _MONT_INV_60 614891469123651692

	#define _B ((1 << 14) + (1 << 9))
	#define _log_B 15
#endif

#define _MONT_N _P
#define _MONT_R (1LL << 64)

#define _N 256
#define _M 4

#define _log_N 8

#define _hN    (_N >> 1)
#define _hhN   (_N >> 2)
#define _2hhN  _hN
#define _3hhN  (_hN + _hhN)
#define _hhhN  (_N >> 3)
#define _hhhhN (_N >> 4)
#define _Bound1 18
#define _Bound2 (_B - 18)
#endif