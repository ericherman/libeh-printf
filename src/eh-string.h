/*
eh-string - A version of strlen for embedded applications
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
#ifndef EH_STRING
#define EH_STRING

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/*
Returns the number of bytes in the string, excluding the terminating
null byte ('\0').
*/
size_t eh_strlen(const char *s);

/*
Copies at most dest_size bytes of string pointed to by src, including
the terminating null byte ('\0'), to the buffer pointed to by dest.  If
there is no null byte among the first dest_size bytes, the string placed
in dest will not be null-terminated.

The number of bytes written to src (excluding the null terminator) is
added to the value pointed to by the dest_written parameter.

Returns a pointer to  the destination string dest.
*/
char *eh_strncpyl(char *dest, const char *src, size_t dest_size,
		  size_t *dest_written);

#ifdef __cplusplus
}
#endif

#endif /* EH_STRING */
