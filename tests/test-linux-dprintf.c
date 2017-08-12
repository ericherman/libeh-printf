/*
test-linux-dprintf.c
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
#include "eh-printf-tests.h"

int main(void)
{
	char actual[80];
	int failures;
	int rv, fd;
	char fd_path[PATH_MAX];
	char file[PATH_MAX];
	FILE *f;
	size_t length, num_read;

	failures = 0;

	fd = open("/tmp", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	snprintf(fd_path, PATH_MAX, "/proc/self/fd/%d", fd);

	eh_dprintf(fd, "f%co\n%s\n", 'o', "bar");

	snprintf(file, PATH_MAX, "/tmp/proc_self_fd_%d", fd);
	rv = linkat(AT_FDCWD, fd_path, AT_FDCWD, file, AT_SYMLINK_FOLLOW);
	if (rv < 0) {
		fprintf(stderr,
			"linkat(AT_FDCWD,\"%s\", AT_FDCWD,"
			" \"%s\", AT_SYMLINK_FOLLOW) returned %d\n",
			fd_path, file, rv);
	}

	f = fopen(file, "r");

	if (!f) {
		fprintf(stderr, "could not open '%s'\n", file);
		return 1;
	}

	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (length > 79) {
		length = 79;
	}

	num_read = fread(actual, 1, length, f);
	fclose(f);
	actual[num_read] = '\0';

	close(fd);
	unlink(file);

	failures += check_str(actual, "foo\nbar\n");

	return failures ? 1 : 0;
}
