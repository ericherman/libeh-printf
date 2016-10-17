/*
eh-printf-tests.h - a simple string compare for testing
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
#ifndef EH_PRINTF_TESTS
#define EH_PRINTF_TESTS

#include <stdio.h>
#include <string.h>

int ehpf_check_str(const char *file, int line, const char *actual,
		   const char *expected)
{
	if (actual == expected) {
		return 0;
	}
	if ((actual != NULL && expected != NULL)
	    && (strcmp(expected, actual) == 0)) {
		return 0;
	}
	fprintf(stderr, "FAIL: Expected '%s' but was '%s' [%s:%d]\n",
		expected, actual, file, line);
	return 1;
}

#define check_str(actual, expected)\
 ehpf_check_str(__FILE__, __LINE__, actual, expected)

#endif /* EH_PRINTF_TESTS */
