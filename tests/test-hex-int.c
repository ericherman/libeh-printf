/*
test-hex-int.c
Copyright (C) 2016 Eric Herman

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

#define Cmp_with_libc1(fmt, x) \
	eh_snprintf(actual, 80, fmt, x); \
	sprintf(expect, fmt, x); \
	failures += check_str_m(actual, expect, fmt); \
	if (verbose) { \
		printf(" format: '%s'\n actual: '%s'\n expect: '%s'\n", \
			fmt, actual, expect); \
	}

int main(int argc, char **argv)
{
	char expect[80];
	char actual[80];
	int failures, verbose;

	failures = 0;
	verbose = (argc > 1) ? atoi(argv[1]) : 0;

	Cmp_with_libc1("%X", 23);
	Cmp_with_libc1("%#010x", 23);
	Cmp_with_libc1("%#010x", 1);
	Cmp_with_libc1("0x%08x", 2);
	Cmp_with_libc1("%#08x", 5);
	Cmp_with_libc1("%04x", 1234);
	Cmp_with_libc1("%04X", 1234);

	return failures ? 1 : 0;
}
