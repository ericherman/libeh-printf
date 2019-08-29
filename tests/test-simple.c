/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* test-simple.c */
/* Copyright (C) 2016, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#include "../src/eh-printf.h"
#include "eh-printf-tests.h"

int main(void)
{
	char buf[80];
	int failures;

	eh_snprintf(buf, 80, "foo:%d%ld%%dbar", 5, 23L);

	failures = check_str(buf, "foo:523%dbar");

	eh_snprintf(buf, 80, "foo:%d %u %lu %ld\n", 0, 0, 0, 0);

	failures += check_str(buf, "foo:0 0 0 0\n");

	return failures ? 1 : 0;
}
