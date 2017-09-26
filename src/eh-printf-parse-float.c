/*
eh-parse-float.c - extract fields from a floating point variable
Copyright (C) 2017 Eric Herman

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later
version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License (COPYING) along with this library; if not, see:

        https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
*/
#include "eh-printf-parse-float.h"
#include <string.h>		/* memcpy */

#if (!defined EH_PRINTF_SKIP_FLOAT64)
#if (EH_LONG_IS_AT_LEAST_64_BIT)
#define eh_sign_mask 0x8000000000000000UL
#define eh_rexp_mask 0x7FF0000000000000UL
#define eh_frac_mask 0x000FFFFFFFFFFFFFUL
#else /* we need LONG LONG */
#define eh_sign_mask 0x8000000000000000ULL
#define eh_rexp_mask 0x7FF0000000000000ULL
#define eh_frac_mask 0x000FFFFFFFFFFFFFULL
#endif
static uint64_t eh_float64_to_uint64(Eh_float64 d)
{
	uint64_t u64;
	memcpy(&u64, &d, sizeof(Eh_float64));
	return u64;
}

int eh_float64_radix_2_to_fields(Eh_float64 d, uint8_t *sign,
				 int16_t *exponent, uint64_t *fraction)
{
	int16_t raw_exp;
	uint64_t d_u64;

	d_u64 = eh_float64_to_uint64(d);

	*sign = (d_u64 & eh_sign_mask) ? 1U : 0U;
	raw_exp = ((d_u64 & eh_rexp_mask) >> 52UL);
	*exponent = raw_exp - Eh_float64_exp_max;
	*fraction = d_u64 & eh_frac_mask;

	return eh_float64_classify_f(*exponent, *fraction);
}

#undef eh_sign_mask
#undef eh_rexp_mask
#undef eh_frac_mask
#endif

#if (!defined EH_PRINTF_SKIP_FLOAT32)
static uint32_t eh_float32_to_uint32(Eh_float32 d)
{
	uint32_t u32;
	memcpy(&u32, &d, sizeof(Eh_float32));
	return u32;
}

int eh_float32_radix_2_to_fields(Eh_float32 d, uint8_t *sign,
				 int16_t *exponent, uint64_t *fraction)
{
	uint32_t sign_mask, rexp_mask, frac_mask;
	uint16_t raw_exp;
	uint32_t d_u32;

	sign_mask = 0x80000000UL;
	rexp_mask = 0x7F800000UL;
	frac_mask = 0x007FFFFFUL;

	d_u32 = eh_float32_to_uint32(d);

	*sign = (d_u32 & sign_mask) ? 1U : 0U;
	raw_exp = ((d_u32 & rexp_mask) >> 23U);
	*exponent = raw_exp - Eh_float32_exp_max;
	*fraction = d_u32 & frac_mask;

	return eh_float32_classify_f(*exponent, *fraction);
}
#endif

int eh_float32_classify_f(int16_t exponent, uint64_t fraction)
{
	if ((exponent == 0) && (fraction == 0)) {
		return EH_FP_ZERO;
	}

	if (exponent == Eh_float32_exp_inf_nan) {
		return (fraction) ? EH_FP_NAN : EH_FP_INFINITE;
	}

	/* TODO: EH_FP_SUBNORMAL */

	return EH_FP_NORMAL;
}

int eh_float64_classify_f(int16_t exponent, uint64_t fraction)
{
	if ((exponent == 0) && (fraction == 0)) {
		return EH_FP_ZERO;
	}

	if (exponent == Eh_float64_exp_inf_nan) {
		return (fraction) ? EH_FP_NAN : EH_FP_INFINITE;
	}

	/* TODO: EH_FP_SUBNORMAL */

	return EH_FP_NORMAL;
}

int eh_float32_classify(Eh_float32 f)
{
	uint8_t sign;
	int16_t exponent;
	uint64_t fraction;

	eh_float32_radix_2_to_fields(f, &sign, &exponent, &fraction);
	return eh_float32_classify_f(exponent, fraction);
}

int eh_float64_classify(Eh_float64 d)
{
	uint8_t sign;
	int16_t exponent;
	uint64_t fraction;

	eh_float64_radix_2_to_fields(d, &sign, &exponent, &fraction);
	return eh_float64_classify_f(exponent, fraction);
}
