/*
eh-printf-linux.c - linux specific system calls
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

#include <unistd.h>

int EH_SYSOUT_FILENO = STDOUT_FILENO;
int EH_SYSERR_FILENO = STDERR_FILENO;

int eh_sys_putc(char c)
{
	return write(EH_SYSOUT_FILENO, &c, 1);
}

int eh_sys_write_out(char *buf, size_t len)
{
	return write(EH_SYSOUT_FILENO, buf, len);
}

int eh_sys_write_err(char *buf, size_t len)
{
	return write(EH_SYSERR_FILENO, buf, len);
}
