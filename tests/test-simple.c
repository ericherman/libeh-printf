/*
test-simple.c
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
