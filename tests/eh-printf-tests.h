/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* eh-printf-tests.h - a simple string compare for testing */
/* Copyright (C) 2016, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#ifndef EH_PRINTF_TESTS
#define EH_PRINTF_TESTS

#include <stdio.h>
#include <string.h>

static int ehpf_check_str_m(const char *file, int line, const char *actual,
			    const char *expected, const char *msg)
{
	if (actual == expected) {
		return 0;
	}
	if ((actual != NULL && expected != NULL)
	    && (strcmp(expected, actual) == 0)) {
		return 0;
	}
	fprintf(stderr, "FAIL: %s%sExpected '%s' but was '%s' [%s:%d]\n",
		msg == NULL ? "" : msg, msg == NULL ? "" : " ", expected,
		actual, file, line);
	return 1;
}

#define check_str_m(actual, expected, msg)\
 ehpf_check_str_m(__FILE__, __LINE__, actual, expected, msg)

#define check_str(actual, expected) check_str_m(actual, expected, NULL)

#endif /* EH_PRINTF_TESTS */
