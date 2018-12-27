/*
test-misc.c
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

#define Cmp_with_libc1(fmt, x) \
	eh_snprintf(actual, 80, fmt, x); \
	sprintf(expect, fmt, x); \
	failures += check_str_m(actual, expect, fmt); \
	if (verbose) { \
		printf("%s:\n actual: '%s'\n expect: '%s'\n", \
			fmt, actual, expect); \
	}

#define Cmp_with_libc2(fmt, x, y) \
	eh_snprintf(actual, 80, fmt, x, y); \
	sprintf(expect, fmt, x, y); \
	failures += check_str_m(actual, expect, fmt); \
	if (verbose) { \
		printf("%s:\n actual: '%s'\n expect: '%s'\n", \
			fmt, actual, expect); \
	}

int main(int argc, char **argv)
{
	char expect[80];
	char actual[80];
	int failures, verbose;
	void *vptr;

	failures = 0;
	verbose = (argc > 1) ? atoi(argv[1]) : 0;
	vptr = &verbose;

	Cmp_with_libc2("%f %11.2f", 123.4, -0.456);
	Cmp_with_libc2("%d %i", 3, 23);
	Cmp_with_libc2("%X %x", -3, 23);
	Cmp_with_libc2("%#X %#x", -5, 37);
	Cmp_with_libc1("%#02lx", -537L);
	Cmp_with_libc1("%#2f", 4211.0);
	Cmp_with_libc1("%p", vptr);

	return failures ? 1 : 0;
}
