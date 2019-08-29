/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* test-linux-fprintf.c */
/* Copyright (C) 2017, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>

#ifndef O_TMPFILE
#ifndef __O_TMPFILE
#define __O_TMPFILE 020000000
#endif
#define O_TMPFILE (__O_TMPFILE | O_DIRECTORY)
#endif
#ifndef O_TMPFILE_MASK
#define O_TMPFILE_MASK (__O_TMPFILE | O_DIRECTORY | O_CREAT)
#endif

#include <eh-printf.h>
#include <eh-printf-sys-context.h>
#include "eh-printf-tests.h"

int main(void)
{
	char actual[80];
	int failures;
	FILE *f;
	const char *file = "/tmp/test-linux-fprintf.out";
	size_t length, num_read;

	failures = 0;

	f = fopen(file, "w+");
	if (!f) {
		fprintf(stderr, "could not open '%s'\n", file);
		return 1;
	}

	eh_fprintf(f, "%s\n%s\n", "foo", "bar");

	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (length > 79) {
		length = 79;
	}

	num_read = fread(actual, 1, length, f);
	fclose(f);
	unlink(file);
	actual[num_read] = '\0';

	failures += check_str(actual, "foo\nbar\n");

	return failures ? 1 : 0;
}
