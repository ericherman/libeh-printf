/*
eh-sys-context-arduino.cpp: Arduino specific system calls
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
#include <Arduino.h>
#include "eh-sys-context.h"

void *start_sys_printf_context()
{
	return NULL;
}

int end_sys_printf_context(void *ctx)
{
	return 0;
}

size_t eh_sys_output_char(void *ctx, char c)
{
	return Serial.print(c);
}

size_t eh_sys_output_str(void *ctx, char *buf, size_t len)
{
	return Serial.print(buf);
}
