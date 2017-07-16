/*
test-floats.c
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
	Cmp_with_libc1("%f", (1.0 / 0.0));
	Cmp_with_libc1("%f", (-1.0 / 0.0));
	Cmp_with_libc1("%f", sqrt(-1.0));

	return failures ? 1 : 0;
}
