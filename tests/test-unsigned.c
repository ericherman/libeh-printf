/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* test-unsigned.c */
/* Copyright (C) 2016, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#include "../src/eh-printf.h"
#include "eh-printf-tests.h"

int main(void)
{
	char expect[80];
	char actual[80];
	int failures;

	eh_snprintf(actual, 80, "%u", 23);
	sprintf(expect, "%u", 23);
	failures = check_str(actual, expect);

	eh_snprintf(actual, 80, "%lu", 23L);
	sprintf(expect, "%lu", 23L);
	failures += check_str(actual, expect);

	eh_snprintf(actual, 80, "%u", -5);
	sprintf(expect, "%u", -5);
	failures += check_str(actual, expect);

	eh_snprintf(actual, 80, "%lu", -83L);
	sprintf(expect, "%lu", -83L);
	failures += check_str(actual, expect);

	return failures ? 1 : 0;
}
