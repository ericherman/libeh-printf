/*
eh-printf.c - A version of sprintf for embedded applications
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
#include "eh-printf.h"

/*
Returns the number of bytes in the string, excluding the terminating
null byte ('\0').
*/
static size_t eh_strlen(const char *str)
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

/*
Copies at most dest_size bytes of string pointed to by src, including
the terminating null byte ('\0'), to the buffer pointed to by dest.  If
there is no null byte among the first dest_size bytes, the string placed
in dest will not be null-terminated.

The number of bytes written to src (excluding the null terminator) is
added to the value pointed to by the dest_written parameter.

Returns a pointer to  the destination string dest.
*/
static char *eh_strncpyl(char *dest, const char *src, size_t dest_size,
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

enum eh_base {
	eh_binary = 2,
	eh_octal = 8,
	eh_decimal = 10,
	eh_hex = 16
};

#define EH_LONG_BASE2_ASCII_BUF_SIZE ((8 * sizeof(unsigned long int))+1)
static size_t eh_unsigned_long_to_ascii_inner(char *dest, size_t dest_size,
					      enum eh_base base,
					      unsigned char zero_padded,
					      size_t field_size,
					      unsigned char was_negative,
					      unsigned long v)
{
	size_t i, j;
	unsigned long int d, b;
	char reversed_buf[EH_LONG_BASE2_ASCII_BUF_SIZE];

	/* huh? */
	if (dest == NULL || dest_size < 2) {
		if (dest && dest_size) {
			dest[0] = '\0';
		}
		return 0;
	}
	/* bogus input, I guess we fix it? */
	if (field_size >= dest_size) {
		field_size = (dest_size - 1);
	}

	b = ((unsigned long int)base);

	i = 0;
	while (v > 0) {
		d = v % b;
		v = v / b;
		if (d < 10) {
			reversed_buf[i++] = '0' + d;
		} else {
			reversed_buf[i++] = 'A' + (d - 10);
		}
	}

	/* If the field size was not specified (zero), or the value is
	   wider than the specified field width, then the field is
	   expanded to contain the value. */
	if (field_size < i) {
		field_size = i;
	}

	j = 0;
	/* not enough space for data, bail out! */
	if (field_size >= dest_size) {
		/* we don't know what to write, fill with "?" */
		while (j < (dest_size - 1)) {
			dest[j++] = '?';
		}
		dest[j] = '\0';
		return j;
	}

	/* fill padding to right justify */
	if (zero_padded && base == eh_decimal && was_negative) {
		dest[j++] = '-';
	}
	while (j < (field_size - i)) {
		dest[j++] = (zero_padded) ? '0' : ' ';
	}
	if (!zero_padded && base == eh_decimal && was_negative) {
		if (j > 0) {
			dest[j - 1] = '-';
		} else {
			dest[j++] = '-';
		}
	}

	/* walk the reversed_buf backwards */
	while (i) {
		dest[j++] = reversed_buf[--i];
	}

	/* NULL terminate */
	dest[j] = '\0';

	/* return characters written, excluding null character */
	return j;
}

#undef EH_LONG_BASE2_ASCII_BUF_SIZE

static size_t eh_long_to_ascii(char *dest, size_t dest_size, enum eh_base base,
			       unsigned char zero_padded, size_t field_size,
			       long val)
{
	unsigned char was_negative;

	if (val < 0 && base == eh_decimal) {
		was_negative = 1;
		val = -val;
	} else {
		was_negative = 0;
	}

	return eh_unsigned_long_to_ascii_inner(dest, dest_size, base,
					       zero_padded, field_size,
					       was_negative,
					       (unsigned long int)val);
}

static size_t eh_unsigned_long_to_ascii(char *dest, size_t dest_size,
					enum eh_base base,
					unsigned char zero_padded,
					size_t field_size, unsigned long val)
{
	unsigned char was_negative = 0;

	return eh_unsigned_long_to_ascii_inner(dest, dest_size, base,
					       zero_padded, field_size,
					       was_negative,
					       (unsigned long int)val);
}

void eh_append(char *dest, size_t dest_size, size_t field_size, char *str,
	       size_t *used)
{
	size_t i, j, s_len;

	/* huh? */
	if (dest == NULL || dest_size < 2) {
		if (dest && dest_size) {
			dest[0] = '\0';
		}
		return;
	}

	/* bogus input, I guess we fix it? */
	if (field_size >= dest_size) {
		field_size = (dest_size - 1);
	}

	if (!str) {
		str = "(null)";
	}

	s_len = eh_strlen(str);
	if (s_len > field_size) {
		field_size = s_len;
	}

	/* not enough space for data, bail out! */
	if (field_size >= dest_size) {
		/* we don't know what to write, fill with "?" */
		for (i = 0; i < (dest_size - 1); ++i) {
			dest[i++] = '?';
		}
		dest[i] = '\0';
		if (used) {
			*used += i;
		}
		return;
	}

	i = 0;
	if (s_len < field_size) {
		while (i < (field_size - s_len)) {
			dest[i++] = ' ';
		}
	}
	for (j = 0; *(str + j) != '\0'; ++j) {
		dest[i++] = *(str + j);
	}
	dest[i] = '\0';
	if (used) {
		*used += i;
	}
}

int eh_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = eh_vsnprintf(str, size, format, ap);
	va_end(ap);
	return rv;
}

int eh_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	size_t used, fmt_idx, fmt_len;
	char buf[100];
	int special;
	unsigned char zero_padded;
	size_t field_size;

	/* supported types */
	char *s;
	char c;
	int d;
	unsigned int u;
	long l;
	unsigned long int lu;
	/* double f; */

	/* huh? */
	if (str == NULL || size < 1) {
		return 0;
	}

	zero_padded = 0;
	field_size = 0;
	used = 0;
	fmt_idx = 0;
	fmt_len = eh_strlen(format);
	special = 0;

	while (used < size && fmt_idx < fmt_len) {

		if (special) {
			switch (format[fmt_idx]) {
			case '%':
				*(str + used) = '%';
				++used;
				++fmt_idx;
				special = 0;
				break;

			case '0':
				if (field_size == 0) {
					zero_padded = 1;
					++fmt_idx;
					break;
				} else {
					/* fall-through */
				}
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				field_size *= 10;
				field_size += format[fmt_idx] - '0';
				++fmt_idx;
				break;

			case 'l':
				++fmt_idx;
				++special;	/* long long int ? */
				break;

			case 'x':
			case 'X':
				if (special > 1) {
					l = va_arg(ap, long int);
				} else {
					d = va_arg(ap, int);
					l = d;
				}
				eh_long_to_ascii(buf, 100, eh_hex,
						 zero_padded, field_size, l);
				eh_strncpyl((str + used), buf, (size - used),
					    &used);
				++fmt_idx;
				special = 0;
				break;

			case 'u':
				if (special > 1) {
					lu = va_arg(ap, unsigned long int);
				} else {
					u = va_arg(ap, unsigned int);
					lu = u;
				}
				eh_unsigned_long_to_ascii(buf, 100, eh_decimal,
							  zero_padded,
							  field_size, lu);
				eh_strncpyl((str + used), buf, (size - used),
					    &used);
				++fmt_idx;
				special = 0;
				break;

			case 'd':
				if (special > 1) {
					l = va_arg(ap, long int);
				} else {
					d = va_arg(ap, int);
					l = d;
				}
				eh_long_to_ascii(buf, 100, eh_decimal,
						 zero_padded, field_size, l);
				eh_strncpyl((str + used), buf, (size - used),
					    &used);
				++fmt_idx;
				special = 0;
				break;

			case 'c':
				c = (char)va_arg(ap, int);
				*(str + used) = c;
				++used;
				++fmt_idx;
				special = 0;
				break;

			case 's':
				s = (char *)va_arg(ap, char *);
				eh_append((str + used), (size - used),
					  field_size, s, &used);
				++fmt_idx;
				special = 0;
				break;

			default:
				/* unhandled */
				special = 0;
				break;
			}
		} else {
			if (format[fmt_idx] == '%') {
				special = 1;
			} else {
				*(str + used) = format[fmt_idx];
				++used;
			}
			++fmt_idx;
		}
	}

	/* always null terminate */
	if ((used < size) || (used == 0)) {
		*(str + used) = '\0';
	} else {
		*(str + (used - 1)) = '\0';
	}

	return used;
}
