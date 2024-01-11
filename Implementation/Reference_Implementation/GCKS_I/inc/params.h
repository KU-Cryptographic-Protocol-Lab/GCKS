#ifndef __PARAMS_H__
#define __PARAMS_H__

//PARAM options
#define PARAM_1//
#define NTT_s //either NTT_s or Raw_s

#ifdef PARAM_1

	#define _log_P 25
	#define _H 24

	#define N 256
	#define Q 33553969 //(2<<25)-463
	

	#define _B ((1 << 15) -1)
	#define _log_B 15
	#define _N 256
	#define _M 5
	#define _K 2

	#define _log_N 8

	#define _hN    (_N >> 1)
	#define _hhN   (_N >> 2)
	#define _2hhN  _hN
	#define _3hhN  (_hN + _hhN)
	#define _hhhN  (_N >> 3)
	#define _hhhhN (_N >> 4)
	#define _Bound1 24
	#define _Bound2 (_B - 24)

	#define QINV 311990993

	#define _INV_2_3 -4194246

	#define _MONT_2 118528
	#define _MONT_4 237056
	#define _MONT_8 474112
	#define _MONT_16 948224
	#define _MONT_30 1777920
	#define _MONT_45 2666880
	#define _MONT_64 3792896
	#define _MONT_65 3852160
	#define _MONT_2_32 -10945049

	#define _MONT_INV_2 29632
	#define _MONT_INV_18 7459730
	#define _MONT_INV_24 -11182187
	#define _MONT_INV_60 2237919

#endif

#ifdef PARAM_2
	#define _log_P 26
	#define _H 39

	#define N 256
	#define Q 67108753 //(2<<26)-111
	

	#define _B ((1 << 15) + (1 << 9))
	#define _log_B 16
	#define _N 256
	#define _M 8
	#define _K 3

	#define _log_N 8

	#define _hN    (_N >> 1)
	#define _hhN   (_N >> 2)
	#define _2hhN  _hN
	#define _3hhN  (_hN + _hhN)
	#define _hhhN  (_N >> 3)
	#define _hhhhN (_N >> 4)
	#define _Bound1 39
	#define _Bound2 (_B - 39)

    #define QINV 2699469169

	#define _INV_2_3 -8388594

	#define _MONT_2 14208
	#define _MONT_4 28416
	#define _MONT_8 56832
	#define _MONT_16 113664
	#define _MONT_30 213120
	#define _MONT_45 319680
	#define _MONT_64 454656
	#define _MONT_65 461760
	#define _MONT_2_32 -16641937

	#define _MONT_INV_2 3552
	#define _MONT_INV_18 22369979
	#define _MONT_INV_24 296
	#define _MONT_INV_60 13421869


#endif

#ifdef PARAM_3
	#define _log_P 27
	#define _H 74

	#define N 256
	#define Q 134217649 //(2<<27)-79
	

	#define _B ((1 << 18) -1)
	#define _log_B 18
	#define _N 256
	#define _M 17
	#define _K 7

	#define _log_N 8

	#define _hN    (_N >> 1)
	#define _hhN   (_N >> 2)
	#define _2hhN  _hN
	#define _3hhN  (_hN + _hhN)
	#define _hhhN  (_N >> 3)
	#define _hhhhN (_N >> 4)
	#define _Bound1 74
	#define _Bound2 (_B - 74)

	#define QINV 2529749329

	#define _INV_2_3 -16777206

	#define _MONT_2 5056
	#define _MONT_4 10112
	#define _MONT_8 20224
	#define _MONT_16 40448
	#define _MONT_30 75840
	#define _MONT_45 113760
	#define _MONT_64 161792
	#define _MONT_65 164320
	#define _MONT_2_32 6390784

	#define _MONT_INV_2 1264
	#define _MONT_INV_18 -59652148
	#define _MONT_INV_24 -44739111
	#define _MONT_INV_60 62634945

	

#endif


#endif