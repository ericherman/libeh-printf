/* SPDX-License-Identifier: LGPL-2.1-or-later */
/* eh-printf-sys-contxt.h - definine system specific functions for printf */
/* Copyright (C) 2016, 2019 Eric Herman */
/* https://github.com/ericherman/libeh-printf */

#ifndef EH_PRINTF_SYS_CONTEXT
#define EH_PRINTF_SYS_CONTEXT

#ifdef __cplusplus
#define Eh_printf_sys_context_begin_C_functions extern "C" {
#define Eh_printf_sys_context_end_C_functions }
#else
#define Eh_printf_sys_context_begin_C_functions
#define Eh_printf_sys_context_end_C_functions
#endif

#if HAVE_CONFIG_H
#include "config.h"
#endif

#if HAVE_STDDEF_H
#include <stddef.h>
#endif

Eh_printf_sys_context_begin_C_functions
#undef Eh_printf_sys_context_begin_C_functions
/* not all systems have separate OUT and ERR */
extern int EH_PRINTF_SYSOUT_FILENO;
extern int EH_PRINTF_SYSERR_FILENO;

struct eh_printf_context_s {
	int error;
	int fileno;		/* not all systems support files by number */
	void *data;		/* not all systems will need an opaque ptr */
};

void start_sys_printf_context(struct eh_printf_context_s *ctx, int fileno);

int end_sys_printf_context(struct eh_printf_context_s *ctx);

size_t eh_sys_output_char(struct eh_printf_context_s *ctx, char c);

size_t eh_sys_output_str(struct eh_printf_context_s *ctx, const char *str,
			 size_t len);

Eh_printf_sys_context_end_C_functions
#undef Eh_printf_sys_context_end_C_functions
#endif /* EH_PRINTF_SYS_CONTEXT */
