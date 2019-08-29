/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* test-str.c */
/* Copyright (C) 2016, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#include "../src/eh-printf.h"
#include "eh-printf-tests.h"

int main(int argc, char **argv)
{
	char expect[80];
	char actual[80];
	int failures;
	char *str;

	eh_snprintf(actual, 80, "%s", "foo");
	sprintf(expect, "%s", "foo");
	failures = check_str(actual, expect);

	eh_snprintf(actual, 80, "%12s", "bar");
	sprintf(expect, "%12s", "bar");
	failures += check_str(actual, expect);

	str = (argc > 1) ? argv[1] : NULL;

	eh_snprintf(actual, 80, "%12s", str);
	sprintf(expect, "%12s", str);
	failures += check_str(actual, expect);

	return failures ? 1 : 0;
}
