/*
test-str.c
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
