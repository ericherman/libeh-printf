/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* test-floats.c */
/* Copyright (C) 2017, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#include "../src/eh-printf.h"
#include "eh-printf-tests.h"

#include <math.h>

#define Cmp_with_libc1(fmt, x) \
	eh_snprintf(actual, 80, fmt, x); \
	sprintf(expect, fmt, x); \
	failures += check_str(actual, expect)

int main(void)
{
	char expect[80];
	char actual[80];
	int failures;

	failures = 0;

	Cmp_with_libc1("%f", 123.4);
	Cmp_with_libc1("%f", -123.4);
	Cmp_with_libc1("%f", 0.123);
	Cmp_with_libc1("%f", (1.0 / 0.0));
	Cmp_with_libc1("%f", (-1.0 / 0.0));
	Cmp_with_libc1("%f", sqrt(-1.0));
	Cmp_with_libc1("%f", -0.123456789);
	Cmp_with_libc1("%7.2f", 123.456);
	Cmp_with_libc1("%07.2f", 123.456);
	Cmp_with_libc1("%07.2f", 0.456);
	Cmp_with_libc1("%010.2f", -0.456);
	Cmp_with_libc1("%11.2f", -0.456);

	return failures ? 1 : 0;
}
