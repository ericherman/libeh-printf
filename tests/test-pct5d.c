/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* test-pct5d.c */
/* Copyright (C) 2016, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#include "../src/eh-printf.h"
#include "eh-printf-tests.h"

int main(void)
{
	char expect[80];
	char actual[80];
	int failures;

	eh_snprintf(actual, 80, "%5d", 23);
	sprintf(expect, "%5d", 23);

	failures = check_str(actual, expect);

	eh_snprintf(actual, 80, "%050d", 23);
	sprintf(expect, "%050d", 23);

	failures += check_str(actual, expect);

	eh_snprintf(actual, 80, "%050d%d", 23, 17);
	sprintf(expect, "%050d%d", 23, 17);

	failures += check_str(actual, expect);

	return failures ? 1 : 0;
}
