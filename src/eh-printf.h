/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* eh-printf - A version of sprintf for embedded applications */
/* Copyright (C) 2016, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#ifndef EH_PRINTF
#define EH_PRINTF

#ifdef __cplusplus
#define Eh_printf_begin_C_functions extern "C" {
#define Eh_printf_end_C_functions }
#else
#define Eh_printf_begin_C_functions
#define Eh_printf_end_C_functions
#endif

#include <stddef.h>
#include <stdarg.h>

#if (!defined(EH_PRINTF_SKIP_FPRINTF))
#include <stdio.h>		/* FILE */
#endif

Eh_printf_begin_C_functions
#undef Eh_printf_begin_C_functions
/* functions */
/* Returns the number of characters printed (excluding the null byte). */
int eh_printf(const char *format, ...);

int eh_dprintf(int fd, const char *format, ...);

#if (!defined(EH_PRINTF_SKIP_FPRINTF))
int eh_fprintf(FILE *stream, const char *format, ...);
#endif

/* Returns the number of characters printed (excluding the null byte).
   If the output  was truncated  due  to  this  limit  then the return
   value is the number of characters (excluding the terminating null
   byte) which would have been written  to the final string if enough
   space had been available.  Thus, a return value of size or more means
   that the output  was  truncated. */
int eh_snprintf(char *str, size_t size, const char *format, ...);

int eh_vprintf(const char *format, va_list ap);

int eh_vdprintf(int fd, const char *format, va_list ap);

#if (!defined(EH_PRINTF_SKIP_FPRINTF))
int eh_vfprintf(FILE *stream, const char *format, va_list ap);
#endif

int eh_vsnprintf(char *str, size_t size, const char *format, va_list ap);

Eh_printf_end_C_functions
#undef Eh_printf_end_C_functions
#endif /* EH_PRINTF */
