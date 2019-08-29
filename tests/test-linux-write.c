/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* test-linux-write.c */
/* Copyright (C) 2016, 2019 Eric Herman */
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
	int rv, fd, orig_fd;
	char fd_path[PATH_MAX];
	char file[PATH_MAX];
	FILE *f;
	size_t length, num_read;
	struct eh_printf_context_s ctx;

	failures = 0;
	orig_fd = EH_PRINTF_SYSOUT_FILENO;

	fd = open("/tmp", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	snprintf(fd_path, PATH_MAX, "/proc/self/fd/%d", fd);
	EH_PRINTF_SYSOUT_FILENO = fd;

	start_sys_printf_context(&ctx, EH_PRINTF_SYSOUT_FILENO);

	eh_sys_output_char(&ctx, 'f');
	eh_sys_output_char(&ctx, 'o');
	eh_sys_output_char(&ctx, 'o');
	eh_sys_output_char(&ctx, '\n');

	eh_sys_output_str(&ctx, "bar\n", 4);

	end_sys_printf_context(&ctx);

	EH_PRINTF_SYSOUT_FILENO = orig_fd;

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
