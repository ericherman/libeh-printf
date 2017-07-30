/*
eh-printf-sys-context-arduino.cpp: Arduino specific system calls
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

/*

By using eh-printf instead of spirntf, I see this change in the
firmware size:

-rw-rw-r-- 1 eric eric  29353 May 28 06:56 example_sprintf.hex
-rw-rw-r-- 1 eric eric  24538 May 28 06:57 example_ehprintf.hex

And, I notice this difference:

Sketch uses 4,566 bytes (14%) of program storage space. Maximum is 32,256 bytes.
Sketch uses 4,182 bytes (12%) of program storage space. Maximum is 32,256 bytes.

*/

#include "eh-printf-sys-context.h"
#include "eh-printf-arduino-serialobj.h"

extern "C" {

int EH_PRINTF_SYSOUT_FILENO = 1;
int EH_PRINTF_SYSERR_FILENO = 1;

struct eh_printf_context_s start_sys_printf_context(int fileno);
{
	struct eh_printf_context_s ctx;
	ctx.fileno = fileno;
	ctx.error = 0;
	ctx.data = &SERIAL_OBJ;
	return ctx;
}

int end_sys_printf_context(struct eh_printf_context_s *ctx)
{
	return (ctx & ctx->error == 0) ? 0 : 1;
}

size_t eh_sys_output_char(struct eh_printf_context_s *ctx, char c)
{
	return eh_sys_output_str(ctx, &c, 1);
}

size_t eh_sys_output_str(struct eh_printf_context_s *ctx, const char *str,
			 size_t len)
{
	if (ctx == NULL) {
		return (size_t)(-1L);
	}
	const uint8_t *bytes = (const uint8_t *)buf;
	return (size_t)SERIAL_OBJ.write(bytes, len);
}

} /* extern "C" */
