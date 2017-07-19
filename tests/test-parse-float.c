/*
test-parse-float.c
Copyright (C) 2017 Eric Herman

This work is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later
version.

This work is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License (COPYING) along with this library; if not, see:

        https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
*/
#include "../src/eh-printf.h"
#include "eh-printf-tests.h"
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include "../src/eh-parse-float.h"

#define Check_parse_float64(ul, e_sign, e_exp, e_frac) \
	pun_d.u64 = ul; \
	d = pun_d.d; \
	fmt = "%f sign: %u exponent: %d fraction: %u"; \
	sprintf(expect, fmt, d, e_sign, e_exp, e_frac); \
	if (verbose) { \
		printf("expect %s\n", expect); \
	} \
	eh_float64_radix_2_to_fields(d, &sign, &exponent, &fraction); \
	sprintf(actual, fmt, d, sign, exponent, fraction); \
	failures += check_str(actual, expect)

#define Check_parse_float32(u, e_sign, e_exp, e_frac) \
	pun_f.u32 = u; \
	f = pun_f.f; \
	fmt = "%f sign: %u exponent: %d fraction: %u"; \
	sprintf(expect, fmt, f, e_sign, e_exp, e_frac); \
	if (verbose) { \
		printf("%s\n", expect); \
	} \
	eh_float32_radix_2_to_fields(f, &sign, &exponent, &fraction); \
	sprintf(actual, fmt, f, sign, exponent, fraction); \
	failures += check_str(actual, expect)

int main(int argc, char **argv)
{
	int failures, verbose;
	union double_u64_u {
		double d;
		uint64_t u64;
	} pun_d;
	union float_u32_u {
		float f;
		uint32_t u32;
	} pun_f;
	double d;
	float f;
	uint8_t sign, expect_sign;
	int16_t exponent, expect_exp;
	uint32_t u32;
	uint64_t fraction, expect_frac, u64;
	char *fmt;
	char expect[80];
	char actual[80];

	failures = 0;
	verbose = (argc > 1) ? atoi(argv[1]) : 0;

	u64 = (1ULL << 63ULL) + (1ULL << 62ULL) + (1ULL << 51ULL);
	expect_sign = 1;
	expect_exp = 1;
	expect_frac = 1125899906842624;
	Check_parse_float64(u64, expect_sign, expect_exp, expect_frac);

	u32 = (1ULL << 31) + (1ULL << 30) + (1ULL << 22);
	expect_sign = 1;
	expect_exp = 1;
	expect_frac = 4194304;
	Check_parse_float32(u32, expect_sign, expect_exp, expect_frac);

	return failures ? 1 : 0;
}
