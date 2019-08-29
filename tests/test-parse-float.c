/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* test-parse-float.c */
/* Copyright (C) 2017, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#include <eh-printf.h>
#include "eh-printf-tests.h"
#include <stdlib.h>
#include <stdint.h>
#include <float.h>
#include "config.h"
#include <efloat.h>

#define Check_parse_float64(ul, e_sign, e_exp, e_frac) \
	pun_d.u64 = ul; \
	d = pun_d.d; \
	fmt = "%f sign: %d exponent: %d fraction: %u"; \
	sprintf(expect, fmt, d, e_sign, e_exp, e_frac); \
	if (verbose) { \
		printf("expect %s\n", expect); \
	} \
	efloat64_radix_2_to_fields(d, &fields64); \
	sprintf(actual, fmt, d, fields64.sign, fields64.exponent, \
		fields64.significand); \
	failures += check_str(actual, expect)

#define Check_parse_float32(u, e_sign, e_exp, e_frac) \
	pun_f.u32 = u; \
	f = pun_f.f; \
	fmt = "%f sign: %d exponent: %d fraction: %u"; \
	sprintf(expect, fmt, f, e_sign, e_exp, e_frac); \
	if (verbose) { \
		printf("%s\n", expect); \
	} \
	efloat32_radix_2_to_fields(f, &fields32); \
	sprintf(actual, fmt, f, fields32.sign, fields32.exponent, \
		fields32.significand); \
	failures += check_str(actual, expect)

int main(int argc, char **argv)
{
	int failures, verbose;
	union double_u64_u {
		double d;
		uint64_t u64;
	} pun_d;
	double d;
	struct efloat64_fields fields64;
	int8_t expect_sign;
	int16_t expect_exp;
	uint64_t expect_frac, u64;

/*
	union float_u32_u {
		float f;
		uint32_t u32;
	} pun_f;
	float f;
	struct efloat32_fields fields32;
	uint32_t u32;
*/

	char *fmt;
	char expect[80];
	char actual[80];

	failures = 0;
	verbose = (argc > 1) ? atoi(argv[1]) : 0;

	u64 = (1ULL << 63ULL) + (1ULL << 62ULL) + (1ULL << 51ULL);
	expect_sign = -1;
	expect_exp = 1;
	expect_frac = 1125899906842624;
	Check_parse_float64(u64, expect_sign, expect_exp, expect_frac);

/*
	u32 = (1ULL << 31) + (1ULL << 30) + (1ULL << 22);
	expect_sign = -1;
	expect_exp = 1;
	expect_frac = 4194304;
	expect_frac = 12582912;
	Check_parse_float32(u32, expect_sign, expect_exp, expect_frac);
*/

	return failures ? 1 : 0;
}
