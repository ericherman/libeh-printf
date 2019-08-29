/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* eh-printf-private.h - private headers for eh-printf.c */
/* Copyright (C) 2016, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "efloat.h"

#if HAVE_STDARG_H
#include <stdarg.h>
#endif

/*
 * a byte is at least 8 bits, but *may* be more ...
 * thus use CHAR_BIT from limits.h
 * unless compiled with -DEH_CHAR_BIT=8 or something.
 */
#ifndef EH_CHAR_BIT
#ifdef CHAR_BIT
#define EH_CHAR_BIT CHAR_BIT
#else
#if HAVE_LIMITS_H
#include <limits.h>
#define EH_CHAR_BIT CHAR_BIT
#else
#define EH_CHAR_BIT 8
#endif
#endif
#endif

/* is "unsigned long" 64 bit? */
#if (ULONG_MAX > 4294967295UL)	/* unsigned long is probably 64 bit */
#define EH_LONG_IS_AT_LEAST_64_BIT 1
#else
#define EH_LONG_IS_AT_LEAST_64_BIT 0
#endif

typedef size_t (eh_output_char_func) (void *ctx, char c);
typedef size_t (eh_output_str_func) (void *ctx, const char *str, size_t len);

struct buf_context {
	char *str;
	size_t len;
	size_t used;
};

enum eh_base {
	eh_binary = 2,
	eh_octal = 8,
	eh_decimal = 10,
	eh_hex = 16
};

enum eh_upper {
	eh_lower = 0,
	eh_upper = 1
};

static int eh_vprintf_ctx(eh_output_char_func output_char,
			  eh_output_str_func output_str, void *ctx,
			  const char *format, va_list ap);

static size_t eh_buf_output_char(void *ctx, char c);

static size_t eh_buf_output_str(void *ctx, const char *str, size_t len);

static size_t eh_append(eh_output_char_func output_char,
			eh_output_str_func output_str, void *ctx,
			size_t field_size, const char *str);

static size_t eh_strlen(const char *str);

static size_t eh_int_to_ascii(char *dest, size_t dest_size, enum eh_base base,
			      unsigned char alt_form, unsigned char zero_padded,
			      size_t field_size, int val);

static size_t eh_long_to_ascii(char *dest, size_t dest_size, enum eh_base base,
			       unsigned char alt_form,
			       unsigned char zero_padded, size_t field_size,
			       long val);

static size_t eh_unsigned_int_to_ascii(char *dest, size_t dest_size,
				       enum eh_base base, enum eh_upper upper,
				       unsigned char alt_form,
				       unsigned char zero_padded,
				       size_t field_size, unsigned int val);

static size_t eh_unsigned_long_to_ascii(char *dest, size_t dest_size,
					enum eh_base base, enum eh_upper upper,
					unsigned char alt_form,
					unsigned char zero_padded,
					size_t field_size, unsigned long val);

static size_t eh_unsigned_int_to_ascii_inner(char *dest, size_t dest_size,
					     enum eh_base base,
					     enum eh_upper upper,
					     unsigned char alt_form,
					     unsigned char zero_padded,
					     size_t field_size,
					     unsigned char was_negative,
					     unsigned int v);

static size_t eh_unsigned_long_to_ascii_inner(char *dest, size_t dest_size,
					      enum eh_base base,
					      enum eh_upper upper,
					      unsigned char alt_form,
					      unsigned char zero_padded,
					      size_t field_size,
					      unsigned char was_negative,
					      unsigned long v);

static size_t eh_double_to_ascii(char *buf, size_t len, unsigned char alt_form,
				 unsigned char zero_padded, size_t field_size,
				 size_t past_decimal, double f);
