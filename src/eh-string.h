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

#ifdef __cplusplus
}
#endif

#endif /* EH_STRING */
