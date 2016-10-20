/*
eh-string.c - A version of strlen for embedded applications
Copyright (C) 2016 Eric Herman

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later
version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License (COPYING) along with this library; if not, see:

        https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
*/
#include "eh-string.h"

size_t eh_strlen(const char *str)
{
	size_t i;

	if (str == NULL) {
		return 0;
	}

	i = 0;
	while (*(str + i) != '\0') {
		++i;
	}
	return i;
}

char *eh_strncpyl(char *dest, const char *src, size_t dest_size,
		  size_t *dest_written)
{
	size_t i;

	/* huh? */
	if (dest == NULL || !dest_size) {
		return NULL;
	}

	/* char-by-char copy */
	for (i = 0; i < dest_size && src[i] != '\0'; i++) {
		dest[i] = src[i];
	}

	/* NULL-terminate the string if room */
	if (i < dest_size) {
		dest[i] = '\0';
	}

	if (dest_written != NULL) {
		*dest_written += i;
	}

	return dest;
}
